#include "command/command.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "common/file_helper.h"
#include "ransac/cgal_ransac_wrapper.h"

namespace command {

static void CheckRansacCommandFileName(const std::string& mesh_file,
  const std::string& cluster_file, const std::string& primitive_file) {
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::CheckRansacCommandFileName: wrong mesh file: "
      << mesh_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(cluster_file, ".clu")) {
    std::cerr << common::RedHead()
      << "command::CheckRansacCommandFileName: wrong clu file: "
      << cluster_file << common::RedTail() << std::endl;
    exit(-1);  
  }
  if (!common::HasExtension(primitive_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckRansacCommandFileName: wrong primitive file: "
      << primitive_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void RansacCommand(const double cluster_epsilon, const double density,
  const double epsilon, const bool help, const std::string& mesh_file,
  const std::string& cluster_file, const int min_point,
  const double normal_threshold, const std::string& primitive_file,
  const double probability, const bool verbose) {
  if (help) {
    std::cout
      << "ransac              Call CGAL's efficient RANSAC algorithm."
      << std::endl
      << "  -c <double>       Cluster epsilon value in RANSAC." << std::endl
      << "  -d <double>       Sampling density (number of points per unit area)."
      << std::endl
      << "  -e <double>       Epsilon value in RANSAC." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <OFF file>     Input triangle mesh." << std::endl
      << "  -l <CLU file>     Output clusters." << std::endl
      << "  -m <int>          Min points in RANSAC." << std::endl
      << "  -n <double>       Normal threshold in RANSAC." << std::endl
      << "  -p <PRIM file>    Detected primitives." << std::endl
      << "  -r <double>       Probability in RANSAC." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "This command calls CGAL's efficient-RANSAC method. It" << std::endl
      << "asks for five parameters and returns detected" << std::endl
      << "primitives in an output file. We plan to call this" << std::endl
      << "function multiple times with various parameters to" << std::endl
      << "collect lots of candidates for every face, then run" << std::endl
      << "graph-cut (implemented in a separate command) to pick" << std::endl
      << "a set of good candidates to cover all faces." << std::endl
      << "Meaning of each parameters:" << std::endl
      << "-c: cluster epsilon (0.01). Smaller value leads to over-segmentation."
      << std::endl
      << "-e: epsilon (0.002). Smaller value leads to more reliable results."
      << std::endl
      << "-m: min points (200). Larger number leads to early termination."
      << std::endl
      << "-n: normal threshold (0.9). Smaller value leads to reliable results."
      << std::endl
      << "-r: probability (0.05). Larger value means less reliable but faster."
      << std::endl << std::endl;
    return;
  }

  // Check inputs.
  CheckRansacCommandFileName(mesh_file, cluster_file, primitive_file);
  // Check parameters.
  if (density <= 0.0) {
    std::ostringstream ss;
    ss << "command::RansacCommand: expect to see positive density: " << density;
    common::PrintError(ss.str());
  }
  if (epsilon < 0) {
    std::ostringstream ss;
    ss << "command::RansacCommand: expect to see positive epsilon: " << epsilon;
    common::PrintError(ss.str());
  }
  if (min_point < 0) {
    std::ostringstream ss;
    ss << "command::RansacCommand: expect to see positive number: "
       << min_point;
    common::PrintError(ss.str());
  }
  if (normal_threshold > 1 || normal_threshold <= 0) {
    std::ostringstream ss;
    ss << "command::RansacCommand: expect to see threshold between 0 and 1: "
       << normal_threshold;
    common::PrintError(ss.str());
  }
  if (probability < 0 || probability > 1) {
    std::ostringstream ss;
    ss << "command::RansacCommand: expect to see probability between 0 and 1: "
       << probability;
    common::PrintError(ss.str());
  }

  // Print input argument just for sanity check.
  if (verbose) {
    std::cout << "command::RansacCommand: using the following RANSAC "
      << "parameters:" << std::endl
      << "Cluster epsilon: " << cluster_epsilon << std::endl
      << "Epsilon: " << epsilon << std::endl
      << "Min point: " << min_point << std::endl
      << "Normal threshold: " << normal_threshold << std::endl
      << "Probability: " << probability << std::endl;
  }

  // Read shape.
  mesh::TriMesh shape;
  shape.Initialize(mesh_file);
  ransac::CgalRansacWrapper wrapper(shape);

  // Sample points.
  wrapper.BuildPointSamples(density);
  if (verbose) {
    std::cout << "command::RansacCommand: sample " << wrapper.NumOfSamples()
      << " points." << std::endl;
  }

  // Run RANSAC only once.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives(0);
  std::vector<std::vector<int>> face_to_primitive(0);
  wrapper.RunRansac(probability, min_point, epsilon, cluster_epsilon,
    normal_threshold, primitives, face_to_primitive);
  // Write primitives into the output file.
  common::WritePrimFile(primitives, primitive_file);
  // Construct the clusters. Because we are using RANSAC, these clusters do not
  // necessarily form a partition of all the faces. Some clusters may be empty,
  // and some faces may belong to multiple clusters.
  std::vector<std::vector<int>> clusters(primitives.size(),
    std::vector<int>(0));
  const int face_num = shape.NumOfFaces();
  for (int i = 0; i < face_num; ++i) {
    for (const int idx : face_to_primitive[i]) {
      clusters[idx].push_back(i);
    }
  }
  common::WriteClusterFile(clusters, cluster_file);

  if (verbose) {
    std::cout << "command::RansacCommand: collected " << primitives.size()
      << " primitives." << std::endl;
    for (const auto& primitive : primitives) {
      std::cout << primitive->WriteToString() << std::endl;
    }
    int unclaimed = 0;
    int dup = 0;
    double area = 0.0;
    double unclaimed_area = 0.0;
    double duplicated_area = 0.0;
    for (int i = 0; i < face_num; ++i) {
      area += shape.area(i);
      const auto& pid = face_to_primitive[i];
      if (pid.empty()) {
        ++unclaimed;
        unclaimed_area += shape.area(i);
      }
      if (pid.size() > 1u) {
        ++dup;
        duplicated_area += shape.area(i);
      }
    }
    const double unclaimed_rate = unclaimed_area * 1.0 / area;
    const double dup_rate = duplicated_area * 1.0 / area;
    std::cout << "command::RansacCommand: unclaimed faces: " << unclaimed
      << " (" << unclaimed_rate * 100.0 << "% of the area), duplicated faces: "
      << dup << " (" << dup_rate * 100.0 << "% of the area)." << std::endl;
    // Visualize the results.
    const std::string debug_folder = common::GetParentFolder(cluster_file);
    const std::string seg_file = common::AppendFileToPath(debug_folder,
      "result");
    common::VisualizeMeshSegmentation(shape, clusters, seg_file, true);
  }
}

}
