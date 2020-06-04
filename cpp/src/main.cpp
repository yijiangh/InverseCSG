#include <iostream>
#include <string>
#include <ctime>
#include "command/command.h"
#include "common/arg_parser.h"
#include "primitive/surface_primitive.h"
#include "primitive/plane_surface.h"
#include "primitive/spherical_surface.h"
#include "primitive/cylindrical_surface.h"
#include "primitive/toric_surface.h"
#include "test/test.h"

static void PrintHelpInfo() {
  std::cout << "csg_cpp_command <mode> [<options...>]"
    << std::endl << std::endl;
  std::cout << "Mode options:" << std::endl;
  std::cout
    << "add-separator       Choose minimal set of separators." << std::endl
    << "  -a <PRIM file>    Auxiliary primitive file." << std::endl
    << "  -e <double>       Minimum distance to primitives." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <PRIM file>    Initial surface primitive file." << std::endl
    << "  -n <DATA file>    Negative equivalence classes." << std::endl
    << "  -o <PRIM file>    Output primitive file." << std::endl
    << "  -p <DATA file>    Positive equivalence classes." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "bhc                 Implement the BHC algorithm." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <PRIM file>    All necessary primitives." << std::endl
    << "  -n <DATA file>    All negative equivalence classes." << std::endl
    << "  -o <SCAD file>    Output scad file." << std::endl
    << "  -p <DATA file>    All positive equivalence classes." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "clean-csg           Cleanup csg results by perturbing dimensions to "
    << "remove degenerated faces." << std::endl
    << "  -e <double>       Epsilon value to be added/removed." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <SCAD file>    Input OpenSCAD file." << std::endl
    << "  -o <SCAD file>    Output OpenSCAD file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "csg-flag            Check if points are inside CSG or not." << std::endl
    << "  -d <DATA file>    Input data file." << std::endl
    << "  -e <double>       Minimum distance to the csg shape." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <SCAD file>    Input OpenSCAD file." << std::endl
    << "  -n <DATA file>    Output data file with negative points." << std::endl
    << "  -p <DATA file>    Output data file with positive points." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "csg-mesh-diff       Estimate the volumetric difference." << std::endl
    << "  -d <double>       Grid size." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <SCAD file>    OpenSCAD file." << std::endl
    << "  -m <OFF file>     Mesh file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "equiv-class         Merge points into equivalent classes." << std::endl
    << "  -e <double>       Minimum distance to the primitives." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <DATA file>    Input data file." << std::endl
    << "  -p <PRIM file>    Input primitive file." << std::endl
    << "  -o <DATA file>    Output data file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "equiv-class-flag    Use equivalence classes to classify samples."
    << std::endl
    << "  -d <double>       Minimum distance to the primitives." << std::endl
    << "  -e <DATA file>    Output positive equivalence classes." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <DATA file>    Input points." << std::endl
    << "  -l <LS file>      Input levelset file." << std::endl
    << "  -m <OFF file>     Input mesh file." << std::endl
    << "  -n <DATA file>    Output negative points." << std::endl
    << "  -o <DATA file>    Output positive points." << std::endl
    << "  -p <PRIM file>    Input primitive file." << std::endl
    << "  -q <DATA file>    Output negative equivalence classes." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "genetic             Implement the genetic algorithm." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <OFF file>     Input triangle mesh." << std::endl
    << "  -p <PRIM file>    Input primitive file." << std::endl
    << "  -o <SCAD file>    Output OpenSCAD file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "hausdorff           Compute the Hausdorff distance." << std::endl
    << "  -a <OFF file>     The first input mesh." << std::endl
    << "  -b <OFF file>     The second input mesh." << std::endl
    << "  -d <double>       The surface sampling density." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "legacy-sketch-tree  Generate tree in the old format used by sketch."
    << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <SCAD file>    Input scad file." << std::endl
    << "  -o <TXT file>     Output text file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "level-set           Compute the level-set." << std::endl
    << "  -e                Display the fitting error in color." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <OFF file>     Input triangle mesh." << std::endl
    << "  -d <double>       Size of the grid." << std::endl
    << "  -o <LS file>      Output level-set file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "mesh-flag           Check if points are inside mesh or not."
    << std::endl
    << "  -d <DATA file>    Input data file." << std::endl
    << "  -e <double>       Minimum distance to the mesh." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <OFF file>     Input triangle mesh." << std::endl
    << "  -l <LS file>      Input level-set file." << std::endl
    << "  -n <DATA file>    Output data file with negative points." << std::endl
    << "  -p <DATA file>    Output data file with positive points." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "primitive           Detect all primitives." << std::endl
    << "  -c <CONF file>    Configuration file." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <OFF file>     Input triangle mesh." << std::endl
    << "  -l <CLU file>     Output cluster file." << std::endl
    << "  -m <META file>    Output primitive metadata file." << std::endl
    << "  -o <PRIM file>    Output primitive file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "primitive-local     Detect primitives inside a region." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <META file>    Primitive metadata file." << std::endl
    << "  -o <PRIM file>    Output primitive file." << std::endl
    << "  -p <PRIM file>    Primitive file." << std::endl
    << "  -s <Vector6f>     Region of interest: <xmin xmax ymin ymax"
    << " zmin zmax>." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
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
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "remove-equiv-class  Remove equivalence points." << std::endl
    << "  -e <double>       Minimum distance to primitives." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <DATA file>    Input data file." << std::endl
    << "  -o <DATA file>    Output data file." << std::endl
    << "  -p <PRIM file>    Input primitive file." << std::endl
    << "  -r <DATA file>    Points to remove." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "remove-prim         Remove redundant primitive." << std::endl
    << "  -e <double>       Minimum distance to primitives." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <PRIM file>    Input primitives." << std::endl
    << "  -n <DATA file>    Input negative equivalence classes." << std::endl
    << "  -o <PRIM file>    Output primitives." << std::endl
    << "  -p <DATA file>    Input positive equivalence classes." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "surface-sample      Sample points from primitives and mesh."
    << std::endl
    << "  -b <double>       Maximum sample distance to primitives and mesh."
    << std::endl
    << "  -d <double>       Sampling density (number of points per unit"
    << " volume)." << std::endl
    << "  -e <double>       Minimum sample distance to primitives and mesh."
    << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <OFF file>     Input triangle mesh." << std::endl
    << "  -l <LS file>      Input level-set file." << std::endl
    << "  -o <DATA file>    Output data file." << std::endl
    << "  -p <PRIM file>    Input primitive file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "test                Run test cases." << std::endl
    << "  -a                Run all test cases." << std::endl
    << "  -c <CONF file>    Test configuration file." << std::endl
    << "  -d <directory>    Location of root folder (the one having README.md)."
    << std::endl
    << "  -h                Print help information." << std::endl
    << "  -n <string>       Run one test case with specified name." << std::endl
    << "  -s <string>       Run one example scene with specified name."
    << std::endl << std::endl;
  std::cout
    << "traverse-tree       Post-order traversal in a SCAD file." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <SCAD file>    Input scad file." << std::endl
    << "  -o <Folder>       An output folder to hold all results." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
  std::cout
    << "tree-info           Print tree depth and number of nodes." << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <SCAD file>    Input scad file." << std::endl << std::endl;
  std::cout
    << "volume-sample       Sample points inside the triangle mesh."
    << std::endl
    << "  -d <double>       Sampling density (number of points per unit"
    << " volume)." << std::endl
    << "  -e <double>       Minimum sample distance to primitives and mesh."
    << std::endl
    << "  -h                Print help information." << std::endl
    << "  -i <OFF file>     Input triangle mesh." << std::endl
    << "  -l <LS file>      Input level-set file." << std::endl
    << "  -n <DATA file>    Output negative data file." << std::endl
    << "  -p <DATA file>    Output positive data file." << std::endl
    << "  -r <PRIM file>    Input primitive file." << std::endl
    << "  -v                Verbose mode." << std::endl << std::endl;
}

static void Initialize() {
  // Random seed.
  srand(static_cast<unsigned>(time(0)));

  // Register all surface primitives.
  primitive::PlaneSurface::Register();
  primitive::SphericalSurface::Register();
  primitive::CylindricalSurface::Register();
  primitive::ToricSurface::Register();
}

int main(const int argc, const char* argv[]) {
  // csg_cpp_command does the following things:
  // - Read/write triangle meshes.
  // - Read/write OpenSCAD files (CSG).
  // - Sample points on the boundary of a triangle mesh.
  // - Check a point is inside/outside a triangle mesh/CSG.
  // - Detect primitives by fitting samples into analytical functions.
  // - Sample points in the narrow band of the primitives.
  // - Merge points into equivalent classes.
  if (argc == 1) {
    // Print the help information.
    PrintHelpInfo();
    return 0;
  }

  // Global initialization.
  Initialize();

  const std::string mode(argv[1]);
  try {
    if (mode == "add-separator") {
      common::ArgParser parser;
      parser.AddStringArgument("-a");
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-o");
      parser.AddStringArgument("-p");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::AddSeparatorCommand(parser.GetStringArgument("-a"),
        parser.GetDoubleArgument("-e")(0), parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"), parser.GetStringArgument("-n"),
        parser.GetStringArgument("-o"), parser.GetStringArgument("-p"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "bhc") {
      common::ArgParser parser;
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-o");
      parser.AddStringArgument("-p");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::BhcCommand(parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"), parser.GetStringArgument("-n"),
        parser.GetStringArgument("-o"), parser.GetStringArgument("-p"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "clean-csg") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-o");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::CleanCsgCommand(parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"), parser.GetStringArgument("-i"),
        parser.GetStringArgument("-o"), parser.GetBoolArgument("-v"));
    } else if (mode == "csg-flag") {
      common::ArgParser parser;
      parser.AddStringArgument("-d");
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-p");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::CsgFlagCommand(parser.GetStringArgument("-d"),
        parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"),
        parser.GetStringArgument("-n"),
        parser.GetStringArgument("-p"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "csg-mesh-diff") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-d");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-m");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::CsgMeshDiffCommand(parser.GetDoubleArgument("-d")[0],
        parser.GetBoolArgument("-h"), parser.GetStringArgument("-i"),
        parser.GetStringArgument("-m"), parser.GetBoolArgument("-v"));
    } else if (mode == "equiv-class") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-p");
      parser.AddStringArgument("-o");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::EquivClassCommand(parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"),
        parser.GetStringArgument("-p"),
        parser.GetStringArgument("-o"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "equiv-class-flag") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-d");
      parser.AddStringArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-l");
      parser.AddStringArgument("-m");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-o");
      parser.AddStringArgument("-p");
      parser.AddStringArgument("-q");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::EquivClassFlagCommand(parser.GetDoubleArgument("-d")(0),
        parser.GetStringArgument("-e"), parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"), parser.GetStringArgument("-l"),
        parser.GetStringArgument("-m"), parser.GetStringArgument("-n"),
        parser.GetStringArgument("-o"), parser.GetStringArgument("-p"),
        parser.GetStringArgument("-q"), parser.GetBoolArgument("-v"));
    } else if (mode == "genetic") {
      common::ArgParser parser;
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-p");
      parser.AddStringArgument("-o");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::GeneticCommand(parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"),
        parser.GetStringArgument("-p"),
        parser.GetStringArgument("-o"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "hausdorff") {
      common::ArgParser parser;
      parser.AddStringArgument("-a");
      parser.AddStringArgument("-b");
      parser.AddDoubleArgument("-d");
      parser.AddBoolArgument("-h");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::HausdorffCommand(parser.GetStringArgument("-a"),
        parser.GetStringArgument("-b"),
        parser.GetDoubleArgument("-d")(0),
        parser.GetBoolArgument("-h"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "legacy-sketch-tree") {
      common::ArgParser parser;
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-o");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::LegacySketchTreeCommand(parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"),
        parser.GetStringArgument("-o"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "level-set") {
      common::ArgParser parser;
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddDoubleArgument("-d");
      parser.AddStringArgument("-o");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::LevelSetCommand(parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"),
        parser.GetDoubleArgument("-d")(0),
        parser.GetStringArgument("-o"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "mesh-flag") {
      common::ArgParser parser;
      parser.AddStringArgument("-d");
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-l");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-p");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::MeshFlagCommand(parser.GetStringArgument("-d"),
        parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"),
        parser.GetStringArgument("-l"),
        parser.GetStringArgument("-n"),
        parser.GetStringArgument("-p"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "primitive") {
      common::ArgParser parser;
      parser.AddStringArgument("-c");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-l");
      parser.AddStringArgument("-m");
      parser.AddStringArgument("-o");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::PrimitiveCommand(parser.GetStringArgument("-c"),
        parser.GetBoolArgument("-h"), parser.GetStringArgument("-i"),
        parser.GetStringArgument("-l"), parser.GetStringArgument("-m"),
        parser.GetStringArgument("-o"), parser.GetBoolArgument("-v"));
    } else if (mode == "primitive-local") {
      common::ArgParser parser;
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-o");
      parser.AddStringArgument("-p");
      parser.AddDoubleArgument("-s", Eigen::VectorXd::Zero(6));
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      const Eigen::VectorXd roi_size = parser.GetDoubleArgument("-s");
      const Eigen::Vector3d pmin(roi_size(0), roi_size(2), roi_size(4));
      const Eigen::Vector3d pmax(roi_size(1), roi_size(3), roi_size(5));
      command::PrimitiveLocalCommand(parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"), parser.GetStringArgument("-o"),
        parser.GetStringArgument("-p"), pmin, pmax,
        parser.GetBoolArgument("-v"));
    } else if (mode == "ransac") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-c", 1, 0.01);
      parser.AddDoubleArgument("-d");
      parser.AddDoubleArgument("-e", 1, 0.002);
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-l");
      parser.AddIntArgument("-m", 200);
      parser.AddDoubleArgument("-n", 1, 0.9);
      parser.AddStringArgument("-p");
      parser.AddDoubleArgument("-r", 1, 0.05);
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::RansacCommand(parser.GetDoubleArgument("-c")(0),
        parser.GetDoubleArgument("-d")(0),
        parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"),
        parser.GetStringArgument("-l"),
        parser.GetIntArgument("-m"),
        parser.GetDoubleArgument("-n")(0),
        parser.GetStringArgument("-p"),
        parser.GetDoubleArgument("-r")(0),
        parser.GetBoolArgument("-v"));
    } else if (mode == "remove-equiv-class") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-o");
      parser.AddStringArgument("-p");
      parser.AddStringArgument("-r");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::RemoveEquivClassCommand(parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"), parser.GetStringArgument("-i"),
        parser.GetStringArgument("-o"), parser.GetStringArgument("-p"),
        parser.GetStringArgument("-r"), parser.GetBoolArgument("-v"));
    } else if (mode == "remove-prim") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-o");
      parser.AddStringArgument("-p");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::RemovePrimCommand(parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"), parser.GetStringArgument("-i"),
        parser.GetStringArgument("-n"), parser.GetStringArgument("-o"),
        parser.GetStringArgument("-p"), parser.GetBoolArgument("-v"));
    } else if (mode == "surface-sample") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-b");
      parser.AddDoubleArgument("-d");
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-l");
      parser.AddStringArgument("-o");
      parser.AddStringArgument("-p");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::SurfaceSampleCommand(parser.GetDoubleArgument("-b")(0),
        parser.GetDoubleArgument("-d")(0), parser.GetDoubleArgument("-e")(0),
        parser.GetBoolArgument("-h"), parser.GetStringArgument("-i"),
        parser.GetStringArgument("-l"), parser.GetStringArgument("-o"),
        parser.GetStringArgument("-p"), parser.GetBoolArgument("-v"));
    } else if (mode == "test") {
      common::ArgParser parser;
      parser.AddBoolArgument("-a");
      parser.AddStringArgument("-c");
      parser.AddStringArgument("-d");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-s");
      parser.Parse(argc, argv);
      test::TestCommand(parser.GetBoolArgument("-a"),
        parser.GetStringArgument("-c"), parser.GetStringArgument("-d"),
        parser.GetBoolArgument("-h"), parser.GetStringArgument("-n"),
        parser.GetStringArgument("-s"));
    } else if (mode == "traverse-tree") {
      common::ArgParser parser;
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-o");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::TraverseTreeCommand(parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"), parser.GetStringArgument("-o"),
        parser.GetBoolArgument("-v"));
    } else if (mode == "tree-info") {
      common::ArgParser parser;
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.Parse(argc, argv);
      command::TreeInfoCommand(parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"));
    } else if (mode == "volume-sample") {
      common::ArgParser parser;
      parser.AddDoubleArgument("-d");
      parser.AddDoubleArgument("-e");
      parser.AddBoolArgument("-h");
      parser.AddStringArgument("-i");
      parser.AddStringArgument("-l");
      parser.AddStringArgument("-n");
      parser.AddStringArgument("-p");
      parser.AddStringArgument("-r");
      parser.AddBoolArgument("-v");
      parser.Parse(argc, argv);
      command::VolumeSampleCommand(parser.GetDoubleArgument("-d")(0),
        parser.GetDoubleArgument("-e")(0), parser.GetBoolArgument("-h"),
        parser.GetStringArgument("-i"), parser.GetStringArgument("-l"),
        parser.GetStringArgument("-n"), parser.GetStringArgument("-p"),
        parser.GetStringArgument("-r"), parser.GetBoolArgument("-v"));
    } else {
      std::cerr << "main: unknown mode: " << mode << std::endl;
      exit(-1);
    }
  } catch (int exit_code) {
    exit(exit_code);
  }
  return 0;
}
