import argparse
import os
import sys

import helper
import sketch_pipeline

# Parse input arguments.
parser = argparse.ArgumentParser()
parser.add_argument('--builddir',
                    help='same as the build folder used in install.py',
                    default='../build/')
parser.add_argument('--countersample', help='number of counter samples at '
                    'each iteration. Used by sketch only', default=100)
parser.add_argument('--eps', help='minimum distance to mesh', default='0.01')
parser.add_argument('--initsample', help='number of initial samples sent to' \
                    'sketch', default=1000)
parser.add_argument('--max_iter', help='max number of iterations used by ' \
                    'sketch to solve each part', default=10)
parser.add_argument('--mesh', help='location of the .off file',
                    default='example/one_cube/csg.off')
parser.add_argument('--method', help='choose "sketch" or "genetic"',
                    default='sketch')
parser.add_argument('--outdir', help='a folder to store all results',
                    default='../one_cube/')
parser.add_argument('--surfacedensity', help='number of samples in unit ' \
                    'volume in the surface shell', default=10000)
parser.add_argument('--seg', help='number of segmentations', default=2)
parser.add_argument('--timeout', help='max allowable time in seconds for '\
                    'each sketch call.', default=600)
parser.add_argument('--volumedensity', help='number of samples in unit ' \
                    'volume, used to segment the mesh.', default=1000)
args = parser.parse_args()

# Load environment variables.
env_file = os.path.join(os.path.realpath(args.builddir), 'ENVIRONMENT')
for line in open(env_file):
  if '#' not in line:
    key, value = line.strip().split()
    os.environ[key[:-1]] = value.strip()

if __name__ == '__main__':
  if args.method == 'sketch':
    sketch_pipeline.SetupSketchPipeline(args)
    sketch_pipeline.RunSketchPipeline()
  elif args.method == 'genetic':
    # import genetic_algorithm_pipeline
    # genetic_algorithm_pipeline.SetupGeneticAlgorithmPipeline(args)
    # genetic_algorithm_pipeline.RunGeneticAlgorithmPipeline()
    raise NotImplementedError('genetic_algorithm_pipeline not implemented!')
  else:
    helper.PrintWithRedColor('Invalid method: %s' % args.method)
    sys.exit(-1)
