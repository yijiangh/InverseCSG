import numpy as np
import os
import shutil
import subprocess
import sys
import multiprocessing
import time 
import shlex
import threading
import math

import surface_primitive_to_sketch
import helper
import point_cloud_seg

################################################################################
# Local variables.
################################################################################
# Input arguments.
num_counter_samples = 0
eps = 0
max_iter = 0
num_init_samples = 0
mesh_file_loc = ''
surface_density = 0
seg_num = 0
timeout = 0
volume_density = 0
# This number is numChildren * 2 ^ (MAX_DEPTH - 1), where numChildren and
# MAX_DEPTH are defined in basic_sketch_solver_file.
max_prim_num = 16
# Folders used by sketch pipeline.
output_dir = ''           # Parent of the following folders.
sketch_output_dir = ''    # Save sketch logs.
point_output_dir = ''     # Save point samples, detected primitives, etc.
csg_output_dir = ''       # Save output csg results.
sketch_harness_dir = ''   # Not sure what exactly this folder is.
basic_sketch_solver_file = 'csg_discrete_min.sk'

################################################################################
# Preparation.
################################################################################
def SetupSketchPipeline(args):
  global num_counter_samples
  global eps
  global num_init_samples
  global max_iter
  global mesh_file_loc
  global surface_density
  global seg_num
  global timeout
  global volume_density

  global output_dir
  global sketch_output_dir
  global point_output_dir
  global csg_output_dir
  global sketch_harness_dir

  build_dir = os.path.realpath(args.builddir)
  num_counter_samples = int(args.countersample)
  eps = float(args.eps)
  num_init_samples = int(args.initsample)
  max_iter = int(args.max_iter)
  mesh_file_loc = os.path.realpath(args.mesh)
  method = args.method
  output_dir = os.path.realpath(args.outdir)
  surface_density = float(args.surfacedensity)
  seg_num = int(args.seg)
  timeout = int(args.timeout)
  volume_density = float(args.volumedensity)

  # Check arguments.
  if not os.path.exists(build_dir):
    helper.PrintWithRedColor('Build dir does not exist.')
    sys.exit(-1)
  if num_counter_samples <= 0:
    print('Warning: countersample too small. Using 100 instead.')
    num_counter_samples = 100
  if eps < 1e-3:
    print('Warning: eps too small. Using 1e-3 instead.')
    eps = 1e-3
  if num_init_samples <= 0:
    print('Warning: initsample too small. Using 1000 instead.')
    num_init_samples = 1000
  if max_iter <= 0:
    print('Warning: invalid max iter. Use 10 instead.')
    max_iter = 10
  if not os.path.isfile(mesh_file_loc):
    helper.PrintWithRedColor('Mesh file does not exist.')
    sys.exit(-1)
  if method != 'sketch':
    helper.PrintWithRedColor('Method should be sketch.')
    sys.exit(-1)
  if not os.path.exists(output_dir):
    os.makedirs(output_dir)
  if surface_density <= 0:
    print('Warning: invalid surface density. Use 10000 instead.')
    sample_density = 10000
  if seg_num <= 1:
    print('Warning: invalid seg num. Use 2 instead.')
    seg_num = 2
  if timeout <= 0:
    print('Warning: invalid timeout. Use 600 instead.')
    timeout = 600
  if volume_density <= 0:
    print('Warning: invalid volume density. Use 1000 instead.')
    volume_density = 1000
  helper.PrintWithGreenColor('All arguments seem reasonable.')

  # Set up folders.
  sketch_output_dir = os.path.join(output_dir, 'sketch_output')
  if not os.path.exists(sketch_output_dir):
    os.makedirs(sketch_output_dir)
  point_output_dir = os.path.join(output_dir, 'points')
  if not os.path.exists(point_output_dir):
    os.makedirs(point_output_dir)
  csg_output_dir = os.path.join(output_dir, 'csg')
  if not os.path.exists(csg_output_dir):
    os.makedirs(csg_output_dir)
  sketch_harness_dir = os.path.join(output_dir, 'sketches')
  if not os.path.exists(sketch_harness_dir):
    os.makedirs(sketch_harness_dir)

################################################################################
# Sketch pipeline.
################################################################################
# Randomly choose sample_num points and split the input into selected and
# unselected sets.
def PickRandomPoints(points, sample_num):
  # Early return if it is empty.
  if points.size == 0:
    return points, points

  idx = np.random.choice(points.shape[0], \
                         min(points.shape[0], sample_num), replace=False)
  mask = np.zeros(points.shape[0], dtype=bool)
  mask[idx] = True
  return points[mask, :], points[~mask, :] 

# Returns unsatisfied positive and negative points.
def CheckPointConstraints(csg_file, pos_points, neg_points):
  # Save positive and negative points into temporary files.
  tmp_pos_file = os.path.join(csg_output_dir, '.pos.data')
  tmp_neg_file = os.path.join(csg_output_dir, '.neg.data')
  tmp_point_file = os.path.join(csg_output_dir, '.point.data')
  # Check positive points first.
  helper.SaveDataFile(tmp_point_file, pos_points)
  helper.Run('%s csg-flag -d %s -e %f -i %s -n %s -p %s' % \
             (os.environ['CSG_CPP_EXE'], tmp_point_file, 0, csg_file, \
              tmp_neg_file, tmp_pos_file))
  unsatisfied_pos = helper.LoadDataFile(tmp_neg_file)
  # Check if some points are missing.
  satisfied_pos = helper.LoadDataFile(tmp_pos_file)
  if satisfied_pos.shape[0] + unsatisfied_pos.shape[0] != pos_points.shape[0]:
    helper.PrintWithRedColor('Error: some pos constraints are ignored.')
  # Then check negative points.
  helper.SaveDataFile(tmp_point_file, neg_points)
  helper.Run('%s csg-flag -d %s -e %f -i %s -n %s -p %s' % \
             (os.environ['CSG_CPP_EXE'], tmp_point_file, 0, csg_file, \
              tmp_neg_file, tmp_pos_file))
  unsatisfied_neg = helper.LoadDataFile(tmp_pos_file)
  # Check if some points are missing.
  satisfied_neg = helper.LoadDataFile(tmp_neg_file)
  if satisfied_neg.shape[0] + unsatisfied_neg.shape[0] != neg_points.shape[0]:
    helper.PrintWithRedColor('Error: some neg constraints are ignored.')
  os.remove(tmp_pos_file)
  os.remove(tmp_neg_file)
  os.remove(tmp_point_file)
  return unsatisfied_pos, unsatisfied_neg

def CreateSketch(sketch_harness_file, sketch_solver_file, data_file, \
  idx_file, primitive_file):
  # Now many bits do we need?
  point_num = sum(1 for line in open(idx_file))
  bits = math.ceil(math.log2(point_num)) + 1
  helper.PrintWithGreenColor('Using %d bits to encode the constraints.' % bits)
  # Generate the first line in the sketch_solver_file.
  first_line = 'pragma options "--fe-fpencoding TO_BACKEND ' \
               '--bnd-unroll-amnt 32 --bnd-inbits %d ' \
               '--slv-lightverif";\n' % bits
  f = open(sketch_solver_file, 'w')
  f.write(first_line)
  for line in open(os.path.join(os.environ['CSG_ROOT'], 'sketch', \
    basic_sketch_solver_file)):
    f.write(line)
  f.close()

  f = open(sketch_harness_file, 'w')
  content = '#include "%s"\n' \
            '#include "%s"\n' \
            '\n' \
            '#include "%s"\n' \
            '\n' \
            '@FromFile("%s")\n' \
            'harness void main(int id) {\n' \
            '  check(id);\n' \
            '}\n' % (data_file, primitive_file, \
            os.path.basename(sketch_solver_file), idx_file)
  f.write(content)
  f.close()

def GetSketch(sketch_harness_file, sketch_output_file, timeout):
  sketch_lib_loc = os.path.join(os.environ['CSG_SKETCH_FRONTEND'], \
    'src/sketchlib/')
  cegis_loc = os.path.join(os.environ['CSG_SKETCH_BACKEND'], \
    'src/SketchSolver/cegis')
  timeout_min = float(timeout) / 60.0
  cmd = 'bash %s -V 10 --fe-inc %s ' \
    '--fe-kill-asserts --fe-output-test --fe-output-dir %s ' \
    '--fe-cegis-path %s %s --fe-timeout %f' % \
    (os.environ['CSG_SKETCH'], \
     sketch_lib_loc, sketch_output_dir + '/', cegis_loc, sketch_harness_file, \
     timeout_min)
  helper.PrintWithGreenColor(cmd)
  output = open(sketch_output_file, 'w')
  return_code = subprocess.call(cmd, stderr = subprocess.STDOUT, \
    stdout = output, shell = True)
  output.close()
  # After testing we figured if timeout the return code is 1 and if it ends
  # normally the return code is 0.
  return return_code == 0

def GetSketchCompile(sketch_harness_file):
  sketch_name = os.path.basename(sketch_harness_file)
  # Remove .sk extension.
  sketch_name = os.path.splitext(sketch_name)[0]
  sketch_exe = os.path.join(sketch_output_dir, sketch_name)
  sketch_cpp = os.path.join(sketch_output_dir, sketch_name + '.cpp')
  sketch_test_cpp = os.path.join(sketch_output_dir, sketch_name + '_test.cpp')
  # Compile.
  sketch_runtime_dir = os.path.join(os.environ['CSG_SKETCH_FRONTEND'], \
                                   'src/runtime/include')
  helper.Run('g++ -w -I %s -o %s %s %s' % \
    (sketch_runtime_dir, sketch_exe, sketch_cpp, sketch_test_cpp))
  # Execute and get the solution.
  solution = subprocess.check_output('%s -n 1' % sketch_exe, \
    stderr=subprocess.STDOUT, shell=True).decode('utf-8')
  lines = solution.splitlines()
  solution = []
  for l in lines:
    solution.append(l.strip())
    if '// End.' in l: break
  return '\n'.join(solution)

# Example: EnlargeBoundingBox(box, 1.1) will return a box that is 110% of the
# old box.
def EnlargeBoundingBox(box, ratio):
  xmin, xmax, ymin, ymax, zmin, zmax = box
  dx = (xmax - xmin) * (ratio - 1.0) * 0.5
  dy = (ymax - ymin) * (ratio - 1.0) * 0.5
  dz = (zmax - zmin) * (ratio - 1.0) * 0.5
  xmin -= dx
  xmax += dx
  ymin -= dy
  ymax += dy
  zmin -= dz
  zmax += dz
  return (xmin, xmax, ymin, ymax, zmin, zmax)

# Returns true if box2 \subset box1.
def Enclose(box1, box2):
  xmin1, xmax1, ymin1, ymax1, zmin1, zmax1 = box1
  xmin2, xmax2, ymin2, ymax2, zmin2, zmax2 = box2
  return xmin1 <= xmin2 and xmax1 >= xmax2 and \
    ymin1 <= ymin2 and ymax1 >= ymax2 and \
    zmin1 <= zmin2 and zmax1 >= zmax2

def Preprocessing():
  mesh_info = {}
  # Bounding box of the mesh.
  mesh_bounding_box = helper.GetOffMeshBoundingBox(mesh_file_loc)
  print('Bounding box of the mesh: ' + str(mesh_bounding_box))
  # Enlarge the bounding box a bit.
  box_min = np.array(mesh_bounding_box[::2])
  box_max = np.array(mesh_bounding_box[1::2])
  box_diag = box_max - box_min
  box_min -= box_diag * 0.1
  box_max += box_diag * 0.1
  enlarged_bounding_box = (box_min[0], box_max[0], box_min[1], box_max[1], \
                           box_min[2], box_max[2])
  mesh_info['bounding_box'] = enlarged_bounding_box
  mesh_info['max_offsets'] = max([abs(x) for x in enlarged_bounding_box]) * 3.0

  # Compute the level-set.
  cpp_exe = os.environ['CSG_CPP_EXE']
  level_set_file = os.path.join(point_output_dir, 'levelset.ls')
  print('Computing the level set...')
  # Enlarge eps a bit to avoid numerical issues.
  bigger_eps = eps * 1.1
  helper.Run('%s level-set -i %s -d %f -o %s' % (cpp_exe, mesh_file_loc, \
                                                 bigger_eps, level_set_file))
  mesh_info['level_set_file'] = level_set_file

  # Get surface primitives.
  # init_prim_file includes all detected primitives and auxiliary planes.
  init_prim_file = os.path.join(point_output_dir, 'init_primitives.prim')
  # cluster_file and ransac_config_file are used by RANSAC.
  cluster_file = os.path.join(point_output_dir, 'primitives.clu')
  ransac_config_file = os.path.join(os.path.dirname( \
    os.path.realpath(mesh_file_loc)), 'ransac.conf')
  dummy_meta_file = os.path.join(point_output_dir, '.tmp.meta')
  print('Getting all primitives...')
  helper.Run('%s primitive -i %s -o %s -c %s -l %s -m %s -v' % (cpp_exe, \
    mesh_file_loc, init_prim_file, ransac_config_file, cluster_file, \
    dummy_meta_file))
  # Get auxiliary primitives.
  aux_prim_file = os.path.join(point_output_dir, 'aux_primitives.prim')
  init_and_aux_prim_file = os.path.join(point_output_dir, \
    'init_and_aux_primitives.prim')
  surface_primitive_to_sketch.AddAuxiliaryPrimitives( \
    init_prim_file, aux_prim_file, init_and_aux_prim_file)
  os.remove(dummy_meta_file)

  # Sample points.
  surface_sample_file = os.path.join(point_output_dir, 'surface_sample.data')
  print('Surface sampling...')
  helper.Run('%s surface-sample -b %f -d %f -e %f -i %s -l %s -o %s -p %s -v' \
             % (cpp_exe, 10 * bigger_eps, surface_density, bigger_eps, \
                mesh_file_loc, level_set_file, surface_sample_file, \
                init_and_aux_prim_file))
  init_vol_pos_file = os.path.join(point_output_dir, 'init_vol_pos.data')
  init_vol_neg_file = os.path.join(point_output_dir, 'init_vol_neg.data')
  print('Volume sampling...')
  helper.Run('%s volume-sample -d %f -e %f -i %s -l %s -n %s -p %s -r %s -v' % \
             (cpp_exe, volume_density, bigger_eps, mesh_file_loc, \
              level_set_file, init_vol_neg_file, init_vol_pos_file, \
              init_and_aux_prim_file))
  surface_sample = helper.LoadDataFile(surface_sample_file)
  pos_sample = helper.LoadDataFile(init_vol_pos_file)
  neg_sample = helper.LoadDataFile(init_vol_neg_file)
  all_samples = np.vstack((surface_sample, pos_sample, neg_sample))
  tmp_sample_file = os.path.join(point_output_dir, '.tmp.data')
  helper.SaveDataFile(tmp_sample_file, all_samples)
  equiv_pos_file = os.path.join(point_output_dir, 'equiv_pos.data')
  equiv_neg_file = os.path.join(point_output_dir, 'equiv_neg.data')
  all_pos_file = os.path.join(point_output_dir, 'all_pos.data')
  all_neg_file = os.path.join(point_output_dir, 'all_neg.data')
  print('Calling equiv-class-flag...')
  helper.Run('%s equiv-class-flag -d %f -e %s -i %s -l %s -m %s -n %s -o %s ' \
             '-p %s -q %s -v' % (cpp_exe, bigger_eps, equiv_pos_file, \
             tmp_sample_file, level_set_file, mesh_file_loc, all_neg_file, \
             all_pos_file, init_and_aux_prim_file, equiv_neg_file))
  os.remove(tmp_sample_file)

  # The problem is resolved as long as all points in equiv_pos_file and
  # equiv_neg_file are satisifed using detected primitives.
  mesh_info['pos_file'] = equiv_pos_file
  mesh_info['neg_file'] = equiv_neg_file
  # Now we can filter redundant primitives.
  final_prim_file = os.path.join(point_output_dir, 'final_primitives.prim')
  helper.Run('%s add-separator -a %s -e %f -i %s -o %s -n %s -p %s -v' % \
    (cpp_exe, aux_prim_file, eps, init_prim_file, final_prim_file, \
     equiv_neg_file, equiv_pos_file))
  # Do it one more time.
  helper.Run('%s remove-prim -e %f -i %s -o %s -n %s -p %s -v' % (cpp_exe, \
    eps, final_prim_file, final_prim_file, equiv_neg_file, equiv_pos_file))
  # Add a giant bounding sphere to allow for negation.
  surface_primitive_to_sketch.AddBoundingSphere(final_prim_file, \
    final_prim_file, mesh_info['max_offsets'] + 10 * eps)
  helper.Run('%s equiv-class -e %f -i %s -p %s -o %s -v' % (cpp_exe, eps, \
    equiv_pos_file, final_prim_file, equiv_pos_file))
  helper.Run('%s equiv-class -e %f -i %s -p %s -o %s -v' % (cpp_exe, eps, \
    equiv_neg_file, final_prim_file, equiv_neg_file))
  mesh_info['primitive_file'] = final_prim_file

  # Clean up volumetric samples. 
  print('Filtering volumetric samples (%d positive, %d negative before).' % \
    (pos_sample.shape[0], neg_sample.shape[0]))
  final_vol_pos_file = os.path.join(point_output_dir, 'final_vol_pos.data')
  final_vol_neg_file = os.path.join(point_output_dir, 'final_vol_neg.data')
  helper.IntersectPointSetFiles(all_neg_file, init_vol_neg_file, \
    final_vol_neg_file)
  helper.IntersectPointSetFiles(all_pos_file, init_vol_pos_file, \
    final_vol_pos_file)
  print('Filtering volumtric samples (%d positive, %d negative after).' % \
    (helper.LoadDataFile(final_vol_pos_file).shape[0], \
     helper.LoadDataFile(final_vol_neg_file).shape[0]))
  final_vol_pos_points = helper.LoadDataFile(final_vol_pos_file) 
  equiv_pos_points = helper.LoadDataFile(equiv_pos_file)
  diff_points = helper.SubtractPointSets(equiv_pos_points, final_vol_pos_points)
  if diff_points.size > 0:
    final_vol_pos_points = np.vstack((final_vol_pos_points, diff_points))
  helper.SaveDataFile(final_vol_pos_file, final_vol_pos_points)
  mesh_info['vol_pos_file'] = final_vol_pos_file
  mesh_info['vol_neg_file'] = final_vol_neg_file
  print('Preprocessing done.')
  return mesh_info

# This function solves one part by simulating an outer cegis loop.
def SolveOnePartWithOuterLoop(idx, all_pos_constraints, all_neg_constraints, \
  primitive_roi, mesh_info):
  helper.PrintWithGreenColor('Part %d (%d pos, %d neg in total)' % \
    (idx, all_pos_constraints.shape[0], all_neg_constraints.shape[0]))
  # Call this function to solve all_pos_constraints and all_neg_constraints using
  # primitives inside primitive_roi.
  # Returns a string that describes the csg tree, and done to indicate whether
  # the problem is solved.
  # Call Sketch to satisfy pos_constraints and neg_constraints.
  iter_num = 0
  satisfied_pos = np.zeros((0, 3))
  satisfied_neg = np.zeros((0, 3))
  unsatisfied_pos = all_pos_constraints
  unsatisfied_neg = all_neg_constraints
  while True:
    xmin, xmax, ymin, ymax, zmin, zmax = primitive_roi
    helper.PrintWithGreenColor('Part %d, iter %d, roi (%f, %f, %f, %f, %f, %f)' \
      % (idx, iter_num, xmin, xmax, ymin, ymax, zmin, zmax))
    total_sample = num_init_samples if iter_num == 0 else num_counter_samples
    print('Sampling %d constraints.' % total_sample)
    selected_pos, unsatisfied_pos = PickRandomPoints(unsatisfied_pos, \
      total_sample // 2)
    selected_neg, unsatisfied_neg = PickRandomPoints(unsatisfied_neg, \
      total_sample - selected_pos.shape[0])
    pos_constraints = np.vstack((satisfied_pos, selected_pos))
    neg_constraints = np.vstack((satisfied_neg, selected_neg))
    print('Constraints: %d positive, %d negative.' % \
      (pos_constraints.shape[0], neg_constraints.shape[0]))
    # Save them for debugging purposes. They are duplicated in data.sk.
    pos_constraints_file = os.path.join(point_output_dir, \
      'pos_%d_%d.data' % (idx, iter_num))
    helper.SaveDataFile(pos_constraints_file, pos_constraints)
    neg_constraints_file = os.path.join(point_output_dir, \
      'neg_%d_%d.data' % (idx, iter_num))
    helper.SaveDataFile(neg_constraints_file, neg_constraints)

    # Prepare the data file.
    sketch_data_file = os.path.join(sketch_harness_dir, 'data_%d_%d.sk' \
      % (idx, iter_num))
    sketch_idx_file = os.path.join(sketch_harness_dir, 'idx_%d_%d.sk' \
      % (idx, iter_num))
    helper.SavePointToSketch(sketch_data_file, sketch_idx_file, \
      pos_constraints, neg_constraints)

    # Prepare the primitive file.
    prim_file = os.path.join(point_output_dir, \
      'surface_primitives_%d_%d.prim' % (idx, iter_num))
    unsat_code = 1
    def UnsatHandler(command, exit_code):
      if exit_code != unsat_code:
        helper.DefaultExceptionHandle(command, exit_code)
      else:
        helper.PrintWithGreenColor('UNSAT detected.')

    while True:
      xmin, xmax, ymin, ymax, zmin, zmax = primitive_roi
      helper.Run('%s primitive-local -p %s -o %s -i %s -s %f %f %f %f %f %f' % ( \
        os.environ['CSG_CPP_EXE'], mesh_info['primitive_file'], prim_file, \
        '.dummy.meta', xmin, xmax, ymin, ymax, zmin, zmax))
      # See if the problem is SAT.
      code = helper.Run('%s remove-prim -e %f -i %s -o %s -n %s -p %s -v' % ( \
        os.environ['CSG_CPP_EXE'], eps, prim_file, prim_file, \
        neg_constraints_file, pos_constraints_file), UnsatHandler)
      if code == 0:
        break
      elif code == unsat_code:
        # Try to enlarge the roi.
        if Enclose(primitive_roi, mesh_info['bounding_box']):
          helper.PrintWithRedColor('Roi is already larger than the bounding ' \
            'box but the problem is still UNSAT. Should never happen.')
          sys.exit(-1)
        helper.PrintWithGreenColor('Enlarge the primitive roi and retry...')
        primitive_roi = EnlargeBoundingBox(primitive_roi, 1.1)
      else:
        # Should never happen.
        helper.PrintWithRedColor('See exit code other than 1. ' \
          'Should never happen.')
        sys.exit(-1)

    # Now the surface primitives are stored in prim_file and all of them are
    # necessary. We can count the number of solid primitives and terminate it
    # early if we are sure the solution is too big for sketch to solve. 
    estimated_prim_num = \
      surface_primitive_to_sketch.CountMinimumNumberOfSolidPrimitives(prim_file)
    if estimated_prim_num > max_prim_num:
      # Call segmentation.
      helper.PrintWithRedColor('Problem seems to require a deeper CSG tree. ' \
                               'Call segmentation.')
      return '', False

    prim_sketch_file = os.path.join(sketch_harness_dir, \
      'primitives_%d_%d.sk' % (idx, iter_num))
    surface_primitive_to_sketch.WriteSurfacePrimitivesToSolidSketch( \
      prim_file, prim_sketch_file, mesh_info['max_offsets'] + 10 * eps)
    sketch_harness_file_name = '%s_%d_%d' % \
      (output_dir.split('/')[-1], idx, iter_num)
    sketch_harness_file = os.path.join(sketch_harness_dir, \
      sketch_harness_file_name) + '.sk'
    sketch_solver_file = os.path.join(sketch_harness_dir, \
      'csg_solver_%d_%d.sk' % (idx, iter_num))
    # Sketch harness file.
    CreateSketch(sketch_harness_file, sketch_solver_file, \
      os.path.basename(sketch_data_file), sketch_idx_file, \
      os.path.basename(prim_sketch_file))
    # Run Sketch and get its log.
    sketch_output_file = os.path.join(sketch_output_dir, \
      sketch_harness_file_name + '.log')
    sketch_done = GetSketch(sketch_harness_file, sketch_output_file, \
      timeout)
    # Check if it succeeded.
    if not sketch_done or '[SKETCH] DONE' not in open(sketch_output_file).read():
      helper.PrintWithRedColor('Problem is too hard. Need segmentation.')
      return '', False
    helper.PrintWithGreenColor('Sketch succeeded.')
    satisfied_pos = pos_constraints
    satisfied_neg = neg_constraints
    # Display the solution.
    sketch_solution = GetSketchCompile(sketch_harness_file)
    # Save the results into a scad file.
    csg_file = os.path.join(csg_output_dir, 'csg_%d_%d.scad' % (idx, iter_num))
    f = open(csg_file, 'w')
    f.write(sketch_solution)
    f.close()
    # Check if all point constraints can be satisfied.
    unsatisfied_pos, unsatisfied_neg = CheckPointConstraints(csg_file, \
      all_pos_constraints, all_neg_constraints)
    helper.PrintWithGreenColor('%d positive and %d negative constraints are ' \
      'unsatisfied.' % (unsatisfied_pos.shape[0], unsatisfied_neg.shape[0]))
    if unsatisfied_pos.size + unsatisfied_neg.size == 0:
      # Done.
      return sketch_solution, True
    # End of this iteration.
    iter_num += 1

# This function sends all positive and negative constraints to sketch at once.
def SolveOnePart(idx, all_pos_constraints, all_neg_constraints, primitive_roi, \
  mesh_info):
  # Call this function to solve all_pos_constraints and all_neg_constraints
  # using primitives inside primitive_roi.
  # Returns a string that describes the csg tree, and done to indicate whether
  # the problem is solved.
  # Call Sketch to satisfy pos_constraints and neg_constraints.
  xmin, xmax, ymin, ymax, zmin, zmax = primitive_roi
  helper.PrintWithGreenColor('Part %d, roi (%f, %f, %f, %f, %f, %f)' \
    % (idx, xmin, xmax, ymin, ymax, zmin, zmax))
  print('Constraints: %d positive, %d negative.' % \
    (all_pos_constraints.shape[0], all_neg_constraints.shape[0]))
  # Save them for debugging purposes. They are duplicated in data.sk.
  pos_constraints_file = os.path.join(point_output_dir, 'pos_%d.data' % idx)
  helper.SaveDataFile(pos_constraints_file, all_pos_constraints)
  neg_constraints_file = os.path.join(point_output_dir, 'neg_%d.data' % idx)
  helper.SaveDataFile(neg_constraints_file, all_neg_constraints)

  # Prepare the data file.
  sketch_data_file = os.path.join(sketch_harness_dir, 'data_%d.sk' % idx)
  sketch_idx_file = os.path.join(sketch_harness_dir, 'idx_%d.sk' % idx)
  helper.SavePointToSketch(sketch_data_file, sketch_idx_file, \
    all_pos_constraints, all_neg_constraints)

  # Prepare the primitive file.
  prim_file = os.path.join(point_output_dir, 'surface_primitives_%d.prim' % idx)
  unsat_code = 1
  def UnsatHandler(command, exit_code):
    if exit_code != unsat_code:
      helper.DefaultExceptionHandle(command, exit_code)
    else:
      helper.PrintWithGreenColor('UNSAT detected.')
  while True:
    xmin, xmax, ymin, ymax, zmin, zmax = primitive_roi
    helper.Run('%s primitive-local -p %s -o %s -i %s -s %f %f %f %f %f %f' % ( \
      os.environ['CSG_CPP_EXE'], mesh_info['primitive_file'], prim_file, \
      '.dummy.meta', xmin, xmax, ymin, ymax, zmin, zmax))
    # See if the problem is SAT.
    code = helper.Run('%s remove-prim -e %f -i %s -o %s -n %s -p %s -v' % ( \
      os.environ['CSG_CPP_EXE'], eps, prim_file, prim_file, \
      neg_constraints_file, pos_constraints_file), UnsatHandler)
    if code == 0:
      break
    elif code == unsat_code:
      # Try to enlarge the roi.
      if Enclose(primitive_roi, mesh_info['bounding_box']):
        helper.PrintWithRedColor('Roi is already larger than the bounding ' \
          'box but the problem is still UNSAT. Should never happen.')
        sys.exit(-1)
      helper.PrintWithGreenColor('Enlarge the primitive roi and retry...')
      primitive_roi = EnlargeBoundingBox(primitive_roi, 1.1)
    else:
      # Should never happen.
      helper.PrintWithRedColor('See exit code other than 1. ' \
        'Should never happen.')
      sys.exit(-1)

  # Now the surface primitives are stored in prim_file and all of them are
  # necessary. We can count the number of solid primitives and terminate it
  # early if we are sure the solution is too big for sketch to solve. 
  estimated_prim_num = \
    surface_primitive_to_sketch.CountMinimumNumberOfSolidPrimitives(prim_file)
  if estimated_prim_num > max_prim_num:
    # Call segmentation.
    helper.PrintWithRedColor('Problem seems to require a deeper CSG tree. ' \
                             'Call segmentation.')
    return '', False

  prim_sketch_file = os.path.join(sketch_harness_dir, \
    'primitives_%d.sk' % idx)
  surface_primitive_to_sketch.WriteSurfacePrimitivesToSolidSketch( \
    prim_file, prim_sketch_file, mesh_info['max_offsets'] + 10 * eps)
  sketch_harness_file_name = '%s_%d' % (output_dir.split('/')[-1], idx)
  sketch_harness_file = os.path.join(sketch_harness_dir, \
    sketch_harness_file_name) + '.sk'
  sketch_solver_file = os.path.join(sketch_harness_dir, \
    'csg_solver_%d.sk' % idx)
  # Sketch harness file.
  CreateSketch(sketch_harness_file, sketch_solver_file, \
    os.path.basename(sketch_data_file), sketch_idx_file, \
    os.path.basename(prim_sketch_file))
  # Run Sketch and get its log.
  sketch_output_file = os.path.join(sketch_output_dir, \
    sketch_harness_file_name + '.log')
  sketch_done = GetSketch(sketch_harness_file, sketch_output_file, \
    timeout)
  # Check if it succeeded.
  if not sketch_done or '[SKETCH] DONE' not in open(sketch_output_file).read():
    helper.PrintWithRedColor('Problem is too hard. Need segmentation.')
    return '', False
  helper.PrintWithGreenColor('Sketch succeeded.')
  # Display the solution.
  sketch_solution = GetSketchCompile(sketch_harness_file)
  # Save the results into a scad file.
  csg_file = os.path.join(csg_output_dir, 'csg_%d.scad' % idx)
  f = open(csg_file, 'w')
  f.write(sketch_solution)
  f.close()
  # As a sanity check.
  unsatisfied_pos, unsatisfied_neg = CheckPointConstraints(csg_file, \
    all_pos_constraints, all_neg_constraints)
  if unsatisfied_pos.size + unsatisfied_neg.size > 0:
    helper.PrintWithRedColor('Still see unsatisfied constraints. ' \
      'Should never happen.')
    sys.exit(-1)
  # Done.
  return sketch_solution, True

def RunSketchPipeline():
  mesh_info = Preprocessing()
  all_pos_points = helper.LoadDataFile(mesh_info['pos_file'])
  vol_pos_points = helper.LoadDataFile(mesh_info['vol_pos_file'])
  all_neg_points = helper.LoadDataFile(mesh_info['neg_file'])
  satisfied_pos = np.zeros((0, 3))

  # Major loop starts here.
  part_file = os.path.join(point_output_dir, 'part_0.data')
  shutil.copy(mesh_info['vol_pos_file'], part_file)
  todo = [part_file] 
  solutions = []
  while len(todo) > 0:
    # Pop the first element.
    part_file = todo[0]
    # Extract idx from the file name part_XX.data.
    idx = int(part_file[part_file.rfind('_') + 1 : -len('.data')])
    volumes = helper.LoadDataFile(part_file)
    todo = todo[1:]
    print('Attempt to solve part %d...' % idx)

    # Compute the bounding box of volume. Intentionally enlarge it a bit.
    box_min = volumes.min(axis=0) - 0.01
    box_max = volumes.max(axis=0) + 0.01
    prim_roi = EnlargeBoundingBox((box_min[0], box_max[0], box_min[1], \
      box_max[1], box_min[2], box_max[2]), 1.1)

    # Merge volumes to get positive constraints.
    cpp_exe = os.environ['CSG_CPP_EXE']
    new_pos_file = os.path.join(point_output_dir, 'pos_%d.data' % idx)
    helper.Run('%s equiv-class -e %f -i %s -p %s -o %s' % (cpp_exe, eps, \
      part_file, mesh_info['primitive_file'], new_pos_file)) 
    
    # Subtract satisfied_pos from pos_idx.data.
    tmp_data_file = os.path.join(point_output_dir, '.tmp_%d.data' % idx)
    helper.SaveDataFile(tmp_data_file, satisfied_pos)
    helper.Run('%s remove-equiv-class -e %f -i %s -o %s -p %s -r %s' % (\
      cpp_exe, eps, new_pos_file, new_pos_file, \
      mesh_info['primitive_file'], tmp_data_file))
    os.remove(tmp_data_file)

    pos_points = helper.LoadDataFile(new_pos_file)
    if pos_points.size == 0:
      helper.PrintWithGreenColor('Part %d has been resolved.' % idx)
      continue
    solution, done = SolveOnePartWithOuterLoop(idx, pos_points, \
      all_neg_points, prim_roi, mesh_info)
    if done:
      helper.PrintWithGreenColor('Part %d is done.' % idx)
      # Generate current solution.
      solutions.append(solution)
      csg_file = os.path.join(csg_output_dir, 'solution_%d.scad' % idx)
      f = open(csg_file, 'w')
      # Enclose this solution with the bounding box.
      x_min, x_max, y_min, y_max, z_min, z_max = mesh_info['bounding_box']
      f.write('intersection() {\n')
      f.write('translate([%f, %f, %f])\n' % (x_min, y_min, z_min))
      f.write('cube(size = [%f, %f, %f], center = false);\n' % \
        (x_max - x_min, y_max - y_min, z_max - z_min))
      f.write('union() {\n')
      for s in solutions:
        f.write(s)
        f.write('\n')
      f.write('}\n')
      f.write('}\n')
      f.close()
      # Check if all point constraints can be satisfied.
      tmp_pos_file = os.path.join(csg_output_dir, '.pos.data')
      tmp_neg_file = os.path.join(csg_output_dir, '.neg.data')
      helper.Run('%s csg-flag -d %s -e %f -i %s -n %s -p %s' % \
                 (cpp_exe, mesh_info['pos_file'], eps, csg_file, \
                  tmp_neg_file, tmp_pos_file))
      satisfied_pos = helper.LoadDataFile(tmp_pos_file)
      unsatisfied_pos = helper.LoadDataFile(tmp_neg_file)
      os.remove(tmp_pos_file)
      os.remove(tmp_neg_file)
      if unsatisfied_pos.size == 0:
        # We have found the solution.
        helper.PrintWithGreenColor('All constraints were satisfied. Result is ' \
          'in %s.' % csg_file)
        return
    else:
      # Segment the volume.
      point_cloud_seg.SegmentPointCloud(part_file, seg_num, \
        part_file[:-len('.data')])
      # Get the last idx.
      last_part_file = todo[-1] if len(todo) > 0 else part_file
      last_idx = int(last_part_file[last_part_file.rfind('_') + 1 \
        : -len('.data')]) 
      new_idx = last_idx + 1
      for i in range(seg_num):
        new_part_file = \
          part_file[:part_file.rfind('_') + 1] + str(new_idx + i) + '.data'
        shutil.copyfile(part_file[:-len('.data')] + '_' + str(i) + '.data' , \
          new_part_file)
        todo.append(new_part_file)

if __name__ == '__main__':
  pass
