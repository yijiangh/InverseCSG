import numpy as np
import os
import struct
import sys
import bisect
import random
import time

################################################################################
# Command lines.
################################################################################
def PrintWithGreenColor(message):
  print('\x1b[6;30;42m' + message + '\x1b[0m')

def PrintWithRedColor(message):
  print('\x1b[6;30;41m' + message + '\x1b[0m')

def DefaultExceptionHandle(command, exit_code):
  PrintWithRedColor('Failed: %s' % command)
  PrintWithRedColor('Exit code: %d' % exit_code)
  sys.exit(exit_code)

def Run(command, exception_handle=DefaultExceptionHandle):
  print('Running the following command:')
  PrintWithGreenColor(command)
  time_start = time.time()
  ret_val = os.system(command)
  time_intvl = time.time() - time_start
  print('Command finished in %f seconds.' % time_intvl)
  exit_code = ret_val >> 8
  if exit_code != 0 and exception_handle is not None:
    exception_handle(command, exit_code)
  return exit_code

################################################################################
# Triangle meshes.
################################################################################
def LoadOffMesh(off_file_name):
  with open(off_file_name) as f:
    content = f.readlines()
  # Strip all lines. Ignore blank lines and comments.
  content = [l.strip() for l in content if l.strip() and '#' not in l]
  # First line should be 'OFF'.
  if content[0] != 'OFF':
    PrintWithRedColor('Incorrect OFF file format. Please fix.')
    sys.exit(-1)
  # Second line should be three numbers.
  numbers = [int(n) for n in content[1].split()]
  if len(numbers) != 3:
    PrintWithRedColor('Incorrect OFF file format. Please fix.')
    sys.exit(-1)
  vertex_number, face_number = numbers[:2]
  if vertex_number <= 0 or face_number <= 0:
    PrintWithRedColor('Empty OFF file.')
    sys.exit(-1)
  # Get all vertices.
  all_vertices = np.zeros((vertex_number, 3))
  all_faces = np.zeros((face_number, 3), dtype=int)
  for i in range(2, 2 + vertex_number):
    all_vertices[i - 2, :] = [float(n) for n in content[i].split()]
  for i in range(2 + vertex_number, 2 + vertex_number + face_number):
    all_faces[i - 2 - vertex_number, :] = \
      [int(n) for n in content[i].split()[1:4]]
  return all_vertices, all_faces

def SaveOffMesh(off_file_name, V, F):
  f = open(off_file_name, 'w')
  f.write('OFF\n')
  vertex_num = V.shape[0]
  face_num = F.shape[0]
  f.write('%d %d 0\n' % (vertex_num, face_num))
  for i in range(vertex_num):
    f.write('%f %f %f\n' % (V[i, 0], V[i, 1], V[i, 2]))
  for i in range(face_num):
    f.write('3 %d %d %d\n' % (F[i, 0], F[i, 1], F[i, 2])) 
  f.close()

def GetOffMeshBoundingBox(off_file_name):
  v, _ = LoadOffMesh(off_file_name)
  box_min = v.min(axis=0)
  box_max = v.max(axis=0)
  box = (box_min[0], box_max[0], box_min[1], box_max[1], box_min[2], box_max[2])
  return box

################################################################################
# Binary file to numpy matrix.
################################################################################
def LoadDataFile(data_file):
  # The first 4 bytes are an int variable indicating the number of points, then
  # followed by all the floating point numbers. See more details in
  # cpp/src/common/file_helper.cpp: ReadDataFile.
  with open(data_file, 'rb') as f:
    content = f.read()
  number = struct.unpack('=i', content[:4])[0]
  data = struct.unpack('=' + 'd' * number * 3, content[4:])
  data = np.array(data, dtype=np.float64)
  data = np.reshape(data, (number, 3), 'C')
  return data 

def SaveDataFile(data_file, points):
  # Corner case:
  if points.size == 0:
    number = int(0)
    all_bytes = number.to_bytes(4, sys.byteorder, signed=True)
    f = open(data_file, 'w+b')
    content = b''.join([all_bytes])
    f.write(content)
    f.close()
    return

  # Check inputs.
  if points.shape[1] != 3:
    PrintWithRedColor('SaveDataFile: incorrect input')
    sys.exit(-1)
  number = int(points.shape[0])
  number_bytes = number.to_bytes(4, sys.byteorder, signed=True)
  data_bytes = points.astype(np.float64, 'C').tobytes('C')
  f = open(data_file, 'w+b')
  content = b''.join([number_bytes, data_bytes])
  f.write(content)
  f.close()

################################################################################
# Convert points to sketch files.
################################################################################
def SavePointToSketch(data_file, idx_file, pos_points, neg_points):
  # Check inputs.
  if pos_points.shape[1] != 3 or neg_points.shape[1] != 3:
    PrintWithRedColor('PointToSketch: incorrect input.')
    sys.exit(-1)
  f = open(data_file, 'w')
  num_pos = pos_points.shape[0]
  num_neg = neg_points.shape[0]
  if num_pos + num_neg <= 0:
    PrintWithRedColor('PointToSketch: empty points.')
    sys.exit(-1)
  f.write('int NUM_DATA = %d;\n' % (num_pos + num_neg))
  points = np.vstack((pos_points, neg_points))
  all_x = ', '.join([str(float(x)) for x in points[:, 0]])
  f.write('float[NUM_DATA] xs = {%s};\n' % all_x) 
  all_y = ', '.join([str(float(y)) for y in points[:, 1]])
  f.write('float[NUM_DATA] ys = {%s};\n' % all_y) 
  all_z = ', '.join([str(float(z)) for z in points[:, 2]])
  f.write('float[NUM_DATA] zs = {%s};\n' % all_z) 
  all_labels = ', '.join(['1'] * num_pos + ['0'] * num_neg)
  f.write('bit[NUM_DATA] labels = {%s};\n' % all_labels)
  f.close()

  # Write idx file.
  f = open(idx_file, 'w')
  all_idx = []
  for i in range(num_pos + num_neg):
    all_idx.append(i)
  random.shuffle(all_idx)
  for i in all_idx:
    f.write('%d\n' % i)
  f.close()

################################################################################
# Point set operations.
################################################################################
def IntersectPointSets(A, B):
  # Both A and B are numpy matrices.
  # Returns another numpy matrix that is the intersection of A and B.
  list_a = A.tolist()
  list_b = B.tolist()
  if len(list_a) < len(list_b):
    list_a, list_b = list_b, list_a
  # Now len(list_a) >= len(list_b).
  list_a = sorted(list_a)
  list_c = []
  for p in list_b:
    # Check if p is in list_a.
    loc = bisect.bisect_left(list_a, p)
    # list_a[:loc] < p and list_a[loc:] >= p.
    if loc < 0 or loc >= len(list_a):
      continue
    q = list_a[loc]
    if p[0] == q[0] and p[1] == q[1] and p[2] == q[2]:
      list_c.append(p)
  return np.asarray(list_c, dtype=np.float64)

def IntersectPointSetFiles(A_file, B_file, C_file):
  A = LoadDataFile(A_file)
  B = LoadDataFile(B_file)
  C = IntersectPointSets(A, B)
  SaveDataFile(C_file, C)

def SubtractPointSets(A, B):
  # Return points in A - B.
  list_a = A.tolist()
  list_b = sorted(B.tolist())
  list_c = []
  for p in list_a:
    # Check if p is in list_b.
    loc = bisect.bisect_left(list_b, p)
    # list_b[:loc] < p and list_b[loc:] >= p.
    if loc < 0 or loc >= len(list_b) or list_b[loc][0] != p[0] or \
      list_b[loc][1] != p[1] or list_b[loc][2] != p[2]:
      list_c.append(p)
  C = np.asarray(list_c, dtype=np.float64)
  return C
