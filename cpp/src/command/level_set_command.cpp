#include "command/command.h"
#include <iostream>
#include <fstream>
#include <string>
#include "common/file_helper.h"
#include "mesh/level_set_helper.h"

namespace command {

static void CheckLevelSetCommandFileName(const std::string& mesh_file,
  const std::string& level_set_file) {
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::CheckLevelSetCommandFileName: wrong mesh file: "
      << mesh_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(level_set_file, ".ls")) {
    std::cerr << common::RedHead()
      <<  "command::CheckLevelSetCommandFileName: wrong level-set file:"
      " " << level_set_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void LevelSetCommand(const bool help, const std::string& mesh_file,
  const double grid_size, const std::string& level_set_file,
  const bool verbose) {
  if (help) {
    std::cout
      << "level-set           Compute the level-set." << std::endl
      << "  -e                Display the fitting error in color." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <OFF file>     Input triangle mesh." << std::endl
      << "  -d <double>       Size of the grid." << std::endl
      << "  -o <LS file>      Output level-set file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given a triangle mesh, compute its level-set. We only" << std::endl
      << "compute grids that are close to the mesh surface. The" << std::endl
      << "level set is mostly used for rejecting points whose" << std::endl
      << "distance to the mesh is <= grid_size." << std::endl << std::endl
      << "In our current implementation, there might be a few" << std::endl
      << "points whose distance is > grid_size but are still" << std::endl
      << "rejected. This ensures correctness of our algorithm but" << std::endl
      << "is just slightly inefficient." << std::endl << std::endl;
    return;
  }

  CheckLevelSetCommandFileName(mesh_file, level_set_file);
  if (grid_size <= 0.0) {
    std::cerr << common::RedHead()
      <<"command::LevelSetCommand: nonpositive grid_size: "
      << grid_size << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read mesh.
  mesh::TriMesh shape;
  shape.Initialize(mesh_file);
  // Build level-set.
  mesh::LevelSetHelper level_set(shape, grid_size);
  // Write it to file.
  common::WriteLevelSetFile(level_set, level_set_file);
}

}
