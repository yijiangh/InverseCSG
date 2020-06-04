import argparse
import os
import sys

# Usage: python3 test.py --builddir <build_folder> --dataset <synthetic/cad>
parser = argparse.ArgumentParser()
parser.add_argument('--builddir',
  help='same as the build folder used in install.py', default='../build/')
parser.add_argument('--dataset',
  help='choose either "synthetic" or "cad"', default='cad')
args = parser.parse_args()

build_folder = args.builddir
dataset = args.dataset
cpp_folder = os.path.dirname(os.path.realpath(sys.argv[0]))
root_folder = os.path.dirname(cpp_folder)
example_folder = os.path.join(root_folder, 'example')
cpp_exe = os.path.join(build_folder, 'cpp', 'csg_cpp_command')

# Here is a list of all test cases.
test_cases = ['ComputeLevelSet', \
  'GenerateRandomInts', \
  'GradNormVector', \
  'InitializeSurfaceParameters', \
  'Integral', \
  'Intersect', \
  # IsInside needs the groundtruth csg, so we skip this test.
  #'IsInside', \
  'LinearLeastSquarePlaneFit', \
  'L2Matrix', \
  'L21Matrix' \
]
# Get all examples and sort them.
examples = sorted(os.listdir(example_folder))
bad_examples = []
for example in examples:
  example_type = 'cad' if example.isdigit() else 'synthetic'
  if example_type != dataset:
    continue
  print('Testing example ' + example)
  for case in test_cases:
    conf_file = os.path.join(root_folder, 'cpp/test_config/', case + '.conf')
    return_bit = os.system('%s test -n %s -d %s -s %s -c %s' %
                           (cpp_exe, case, root_folder, example, conf_file))
    exit_code = return_bit >> 8
    if exit_code != 0:
      bad_examples.append(example)
      break
  # Print the bad examples so far.
  print('Bad examples so far:')
  print(bad_examples)
