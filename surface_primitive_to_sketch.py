import math
import numpy as np
import os
import random
import shutil
import sys
import collections

import helper
import transforms

################################################################################
# Put new primitive types here.
################################################################################
# Sphere(x, y, z): |(x, y, z) - center| = radius.
Sphere = collections.namedtuple('Sphere', 'center radius')
# Plane(x, y, z): (x, y, z).dot(norm) = offset.
Plane = collections.namedtuple('Plane', 'norm offset')
# Cylinder(x, y, z): dist((x, y, z), Line(norm + t * center)) = radius.
Cylinder = collections.namedtuple('Cylinder', 'center norm radius')
# Torus: center, axis, major_radius, minor_radius.
Torus = collections.namedtuple('Torus', 'center axis major_radius minor_radius')

# Some helpful data structures.
Point3d = collections.namedtuple('Point3d', 'x y z')
Vector3d = collections.namedtuple('Vector3d', 'x y z')
EulerAngle = collections.namedtuple('EulerAngle', 'roll pitch yaw')
Coordinates = collections.namedtuple('Coordinates', 'x y z')
# RotationsAndOffsets stores a list of auxiliary planes. coord defines three
# orthonormal directions and x, y, z are lists of planes defined as below:
# nx, ny, nz = coord
# for d in x:
#   Plane(nx, d): nx.dot(x) = d
# for d in y:
#   Plane(ny, d): ny.dot(y) = d
# for d in z:
#   Plane(nz, d): nz.dot(z) = d
RotationsAndOffsets = collections.namedtuple('RotationsAndOffsets', \
  'coord x y z')
# For each cylinder we create a CylinderHints:
# - coord is at the origin and its x axis is parallel to cylinder's axis.
# - radius is just the radius.
# - (0, y, z) in coord space will be a point on the axis of the cylinder, and
#   therefore the cylinder can be reconstructed by extending (0, y, z) along
#   (1, 0, 0) in coord.
# - offsets collects offsets from all planes and all sphere centers.
CylinderHints = collections.namedtuple('CylinderHints', \
  'coord radius y z offsets')

################################################################################
# Helpful functions.
################################################################################
def SameVal(v1, v2, eps):
  return abs(v1 - v2) < eps

def SameOffset(p1, p2, eps):
  return p1.axis == p2.axis and SameVal(p1.amount - p2.amount, eps)

def SameVector3d(v1, v2, eps):
  return np.max(np.abs(np.array(v1) - np.array(v2))) < eps

def SameCoordinates(c1, c2, eps):
  c1x, c1y, c1z = c1
  c2x, c2y, c2z = c2
  return SameVector3d(c1x, c2x, eps) and \
    SameVector3d(c1y, c2y, eps) and \
    SameVector3d(c1z, c2z, eps)

# Both shape and shapes have the same primitive type.
def IsNew(shape, shapes, is_same, eps):
  return True not in [is_same(shape, shape1, eps) for shape1 in shapes]

def PrettyPrintList(l):
  for i in l:
    print(i)

################################################################################
# Primitives. If new primitive types are added, you need to add new
# Same[new type], Normalize[new type], and Make[new type] functions.
################################################################################
def SameSphere(s1, s2, eps):
  return np.max(np.abs(s1.center - s2.center)) < eps and \
         SameVal(s1.radius, s2.radius, eps)

def MakeSphere(params):
  cx, cy, cz, r = params
  return Sphere(Point3d(cx, cy, cz), r)

def SamePlane(p1, p2, eps):
  n1, d1 = NormalizePlane(p1)
  n2, d2 = NormalizePlane(p2)
  n1 = np.array(n1)
  n2 = np.array(n2)
  return np.max(np.abs(n1 - n2)) < eps and SameVal(d1, d2, eps)

# Make sure for any p there is a unique representation.
def NormalizePlane(p):
  n, d = p
  n = np.array(n)
  n_len = np.linalg.norm(n)
  n = n / n_len
  d = d / n_len
  # Flip if necessary.
  if n[0] < 0 or \
    (n[0] == 0 and n[1] < 0) or \
    (n[0] == 0 and n[1] == 0 and n[2] < 0):
    n = -n
    d = -d
  return Plane(Vector3d(*n), d)

def MakePlane(params):
  nx, ny, nz, d = params
  # Flip the sign of d because we assume in the text file that the plane
  # equation is ax + by + cz + d = 0.
  return NormalizePlane(Plane(Vector3d(nx, ny, nz), -d))

def SameCylinder(c1, c2, eps):
  o1, n1, r1 = NormalizeCylinder(c1)
  o2, n2, r2 = NormalizeCylinder(c2)
  return np.max(np.abs(o1 - o2)) < eps and np.max(np.abs(n1 - n2)) < eps and \
    SameVal(r1, r2, eps)

def NormalizeCylinder(c):
  o, n, r = c
  # Normalize axis.
  n = np.array(n)
  n = n / np.linalg.norm(n)
  if n[0] < 0 or \
    (n[0] == 0 and n[1] < 0) or \
    (n[0] == 0 and n[1] == 0 and n[2] < 0):
    n = -n
  # Move o along n so that it is closest to the origin.
  # <o + t * n, n> = 0.
  # <o, n> + t = 0.
  # t = -<o, n>
  o = np.array(o)
  o = o - np.dot(o, n) * n
  return Cylinder(Point3d(*o), Vector3d(*n), r)

def MakeCylinder(params):
  cx, cy, cz, nx, ny, nz, r = params
  center = Point3d(cx, cy, cz)
  normal = Vector3d(nx, ny, nz)
  return NormalizeCylinder(Cylinder(center, normal, r))

def SameTorus(t1, t2, eps):
  c1, a1, R1, r1 = NormalizeTorus(t1)
  c2, a2, R2, r2 = NormalizeTorus(t2)
  return np.max(np.abs(c1 - c2)) < eps and np.max(np.abs(a1 - a2)) < eps and \
    SameVal(R1 - R2, eps) and SameVal(r1 - r2, eps)

def NormalizeTorus(t):
  c, a, R, r = t
  # Normalize axis.
  a = np.array(a)
  a = a / np.linalg.norm(a)
  if a[0] < 0 or \
    (a[0] == 0 and a[1] < 0) or \
    (a[0] == 0 and a[1] == 0 and a[2] < 0):
    a = -a
  return Torus(Point3d(*c), Vector3d(*a), R, r)

def MakeTorus(params):
  cx, cy, cz, nx, ny, nz, R, r = params
  center = Point3d(cx, cy, cz)
  normal = Vector3d(nx, ny, nz)
  return NormalizeTorus(Torus(center, normal, R, r))

# TODO: add more primitive types like ellipsoids, etc.
 
################################################################################
# Functions for auxiliary primitives (planes). 
################################################################################
def IsOrthogonormal(coords, eps):
  na, nb, nc = coords
  return abs(np.linalg.norm(na) - 1.0) < eps and \
    abs(np.linalg.norm(nb) - 1.0) < eps and \
    abs(np.linalg.norm(nc) - 1.0) < eps and \
    abs(np.dot(na, nb)) < eps and \
    abs(np.dot(nb, nc)) < eps and \
    abs(np.dot(nc, na)) < eps

# For each sphere, add three planes at its center. 
def GetSpheresOffsets(spheres, eps):
  ret = []
  for s in spheres:
    x_off = Offset('x', s.center.x)
    y_off = Offset('y', s.center.y)
    z_off = Offset('z', s.center.z)
    if IsNew(x_offset, ret, SameOffset, eps): ret.append(x_off)
    if IsNew(y_offset, ret, SameOffset, eps): ret.append(y_off)
    if IsNew(z_offset, ret, SameOffset, eps): ret.append(z_off)
  return ret

# Given any three orthonormal directions, return a unique representation that
# guarantees to be right-hand. Two coordinates are considered to be the same if
# their axes are parallel to each other, and should be mapped to the same coord.
def NormalizeCoordinates(coord):
  nx, ny, nz = coord
  sign_x = sign_y = sign_z = 1
  if nx.x < 0 or (nx.x == 0 and nx.y < 0) or \
    (nx.x == 0 and nx.y == 0 and nx.z < 0):
    sign_x = -1
  if ny.x < 0 or (ny.x == 0 and ny.y < 0) or \
    (ny.x == 0 and ny.y == 0 and ny.z < 0):
    sign_y = -1
  if nz.x < 0 or (nz.x == 0 and nz.y < 0) or \
    (nz.x == 0 and nz.y == 0 and nz.z < 0):
    sign_z = -1
  nx = (np.array(nx) * sign_x).tolist()
  ny = (np.array(ny) * sign_y).tolist() 
  nz = (np.array(nz) * sign_z).tolist()
  [nz, ny, nx] = sorted([nx, ny, nz])
  # Check if it is right-hand.
  if np.dot(np.cross(nx, ny), nz) < 0:
    nz = (-np.array(nz)).tolist()
  return Coordinates(Vector3d(*nx), Vector3d(*ny), Vector3d(*nz))

# Remove normals that have been used by coords from all_norms.
def RemoveUsedNorms(all_norms, coords):
  def Present(norm, coord):
    a, b, c = coord
    eps = 1e-2
    norm = np.array(norm)
    return SameVector3d(norm, a, eps) or SameVector3d(-norm, a, eps) or \
      SameVector3d(norm, b, eps) or SameVector3d(-norm, b, eps) or \
      SameVector3d(norm, c, eps) or SameVector3d(-norm, c, eps)
  ret = []
  for norm in all_norms:
    if True not in [Present(norm, c) for c in coords]:
      ret.append(norm)
  return ret

def ComputeOrthonormalAxis(planes):
  all_norms = []
  for p in planes:
    new_norm = p.norm
    new_norm_neg = Vector3d(-new_norm.x, -new_norm.y, -new_norm.z)
    if IsNew(new_norm, all_norms, SameVector3d, 1e-2) and \
      IsNew(new_norm_neg, all_norms, SameVector3d, 1e-2):
      all_norms.append(new_norm)
  print('Normals from all plans (%d): ' % len(all_norms))
  PrettyPrintList(all_norms)

  # For each pair of orthogonal normals, hallucinate a third norm.
  coord_sets = set()
  for norm1 in all_norms:
    for norm2 in all_norms:
      # Skip if norm1 are norm2 are not orthogonal.
      if not SameVal(np.dot(norm1, norm2), 0, 1e-2): continue
      norm3 = np.cross(norm1, norm2)
      for norm in all_norms:
        if SameVector3d(norm3, norm, 1e-2) or SameVector3d(-norm3, norm, 1e-2):
          norm3 = norm
          break
      # Now (norm1, norm2, norm3) are orthonormal.
      new_coord = NormalizeCoordinates(Coordinates(norm1, norm2, \
        Vector3d(*norm3)))
      if IsNew(new_coord, coord_sets, SameCoordinates, 1e-2):
        coord_sets.add(new_coord)
  # See if any normals are unused.
  left_over_norms = RemoveUsedNorms(all_norms, coord_sets)
  print('Left over norms (%d): ' % len(left_over_norms))
  PrettyPrintList(left_over_norms)
  # Hallucinate two normals for each of them.
  for norm1 in left_over_norms:
    if abs(norm1.x) + abs(norm1.y) < 1e-2:
      norm2 = Vector3d(0, 1, 0)
    else:
      norm2_len = np.linalg.norm([norm1.x, norm1.y])
      norm2 = Vector3d(norm1.y / norm2_len, -norm1.x / norm2_len, 0)
    norm3 = Vector3d(*np.cross(norm1, norm2))
    new_coord = NormalizeCoordinates(Coordinates(norm1, norm2, norm3))
    if IsNew(new_coord, coord_sets, SameCoordinates, 1e-2):
      coord_sets.add(new_coord)
  return coord_sets

def CollectOffsetsAlongNormal(planes, norm):
  offsets = []
  # For each d in offsets, it represents a plane norm.dot(x) = d.
  eps = 1e-2
  for p in planes:
    n, d = p
    n = np.array(n)
    if SameVector3d(n, norm, eps):
      if IsNew(d, offsets, SameVal, eps): offsets.append(d) 
    elif SameVector3d(-n, norm, eps):
      if IsNew(-d, offsets, SameVal, eps): offsets.append(-d)
  return offsets

# Aggregates the centers of all sphere and rotates the centers to the new
# coordinate system.
def GetSphereOffsetsAlongCoords(spheres, coord):
  offsets_x = []
  offsets_y = []
  offsets_z = []
  R = np.zeros((3, 3))
  R[:, 0], R[:, 1], R[:, 2] = coord
  # Now R * x maps x from the coordinates to the world space.
  for s in spheres:
    center, _ = s
    x, y, z = np.dot(center, R)
    # x, y, z are the position of the center but in the coordinates.
    if IsNew(x, offsets_x, SameVal, 1e-2): offsets_x.append(x)
    if IsNew(y, offsets_y, SameVal, 1e-2): offsets_y.append(y)
    if IsNew(z, offsets_z, SameVal, 1e-2): offsets_z.append(z)
  return offsets_x, offsets_y, offsets_z

def GetCylinderOffsetsAlongCoords(cylinders, coord):
  offsets_x = []
  offsets_y = []
  offsets_z = []
  R = np.zeros((3, 3))
  R[:, 0], R[:, 1], R[:, 2] = coord
  for c in cylinders:
    center, _, _ = c
    x, y, z = np.dot(center, R)
    if IsNew(x, offsets_x, SameVal, 1e-2): offsets_x.append(x)
    if IsNew(y, offsets_y, SameVal, 1e-2): offsets_y.append(y)
    if IsNew(z, offsets_z, SameVal, 1e-2): offsets_z.append(z)
  return offsets_x, offsets_y, offsets_z

################################################################################
# Euler angles and rotations.
################################################################################
# Find (0, pitch, yaw) such that rotating x-axis will result in norm.
def NormToRotationAngles(norm):
  # norm.x = cos(yaw) * cos(pitch),
  # norm.y = sin(yaw) * cos(pitch),
  # norm.z = -sin(pitch)
  sin_pitch = -norm.z
  pitch = math.asin(sin_pitch)
  cos_pitch = math.cos(pitch)
  if SameVal(cos_pitch, 0, 1e-2):
    return EulerAngle(0, pitch, 0)
  cos_yaw = norm.x / cos_pitch
  sin_yaw = norm.y / cos_pitch
  yaw = math.atan2(sin_yaw, cos_yaw)
  return EulerAngle(0, pitch, yaw)

# First rotate along (1, 0, 0) by roll, then along (0, 1, 0) by pitch, then
# along (0, 0, 1) by yaw. This is the one used in Jeevana's old code.
# It is the same as first rotating along (0, 0, 1) by yaw, then along the new y
# axis by pitch, then along the new x axis by roll, which is the convention used
# in both the CPP code and OpenSCAD.
# In transforms.py, this is represented as 'sxyz'.
def EulerAnglesToMatrix(euler_angles):
  roll, pitch, yaw = euler_angles
  return transforms.euler_matrix(roll, pitch, yaw, 'sxyz')[:3, :3]

# R has to be orthonormal and right-hand.
def CoordToEulerAngle(coords):
  nx, ny, nz = coords
  R = np.array([[nx.x, ny.x, nz.x, 0], \
                [nx.y, ny.y, nz.y, 0], \
                [nx.z, ny.z, nz.z, 0], \
                [0, 0, 0, 1]])
  roll, pitch, yaw = transforms.euler_from_matrix(R, 'sxyz')
  return EulerAngle(roll, pitch, yaw)

################################################################################
# Detect primitives.
################################################################################
def ReadPrimitiveFile(primitive_file):
  spheres = []
  planes = []
  cylinders = []
  tori = []
  for line in open(primitive_file).readlines():
    info = line.strip().split()
    name = info[0]
    params = [float(x) for x in info[1:]]
    if name == 'sphere':
      spheres.append(MakeSphere(params))
    elif name == 'plane':
      planes.append(MakePlane(params))
    elif name == 'cylinder':
      cylinders.append(MakeCylinder(params))
    elif name == 'torus':
      tori.append(MakeTorus(params))
    else:
      helper.PrintWithRedColor('Unsupported primitive type: %s' % name)
      sys.exit(-1)
  print('surface_primitive_to_sketch::ReadPrimitiveFile.')
  print('Spheres (%d): ' % len(spheres))
  PrettyPrintList(spheres)
  print('Planes (%d): ' % len(planes))
  PrettyPrintList(planes)
  print('Cylinders (%d): ' % len(cylinders))
  PrettyPrintList(cylinders)
  print('Tori (%d): ' % len(tori))
  PrettyPrintList(tori)
  return spheres, planes, cylinders, tori

def WritePrimitiveFile(primitive_file, spheres, planes, cylinders, tori):
  print('Write primitives to %s' % primitive_file)
  f = open(primitive_file, 'w')
  for p in planes:
    f.write('plane %f %f %f %f\n' % (p.norm.x, p.norm.y, p.norm.z, -p.offset))
  for s in spheres:
    f.write('sphere %f %f %f %f\n' % \
      (s.center.x, s.center.y, s.center.z, s.radius))
  for c in cylinders:
    center, norm, radius = c
    f.write('cylinder %f %f %f %f %f %f %f\n' % \
      (center.x, center.y, center.z, norm.x, norm.y, norm.z, radius))
  for t in tori:
    center, norm, major_radius, minor_radius = t
    f.write('torus %f %f %f %f %f %f %f %f\n' % \
      (center.x, center.y, center.z, norm.x, norm.y, norm.z, major_radius, minor_radius))
  f.close()

def AddAuxiliaryPrimitives(input_prim_file, aux_prim_file, output_prim_file):
  spheres, planes, cylinders, tori = ReadPrimitiveFile(input_prim_file)
  aux_planes = GenerateAuxiliaryPlanes(spheres, planes, cylinders, tori)
  WritePrimitiveFile(aux_prim_file, [], aux_planes, [], tori)
  WritePrimitiveFile(output_prim_file, spheres, planes, cylinders, tori)

def AddBoundingSphere(input_prim_file, output_prim_file, max_offsets):
  spheres, planes, cylinders, tori = ReadPrimitiveFile(input_prim_file)
  spheres.append(MakeSphere([0.0, 0.0, 0.0, max_offsets]))
  WritePrimitiveFile(output_prim_file, spheres, planes, cylinders, tori)

def WritePrimitivesToSketch(input_prim_file, output_sketch_file):
  spheres, planes, cylinders = ReadPrimitiveFile(input_prim_file)
  # Encode spheres.
  write_str = ''
  def GenerateInnerSphere(idx, sphere):
    center, radius = sphere
    x, y, z = center
    sphere_line = 'bit sphere%d(Vector p) {\n' \
                  '  return renderSphere(p, %f, %f, %f, %f);\n' \
                  '}\n' % (idx, x, y, z, radius)
    flag = '' if len(spheres) == 1 else 'else' \
              if idx == len(spheres) - 1 else 'if (??) '
    inner_line = '%s {\n' \
                 '  return sphere%d(p);\n' \
                 '}\n' % (flag, idx)
    return sphere_line, inner_line
    
  content = ''
  for idx, sphere in enumerate(spheres):
    sphere_line, inner_line = GenerateInnerSphere(idx, sphere)
    write_str += sphere_line
    content += inner_line
  if not spheres:
    content += 'assert false;\n' \
               'return false;'
  write_str += 'generator bit getSphere(Vector p) {\n' \
               '%s\n' \
               '}\n' \
               '\n' % content

  # Encode planes.
  def GenerateInnerPlane(idx, plane):
    # norm.dot(p) = offset.
    norm, offset = plane
    x, y, z = norm
    euler_angle = NormToRotationAngles(norm)
    # In sketch I assume roll, pitch, yaw rotates [0, 0, 1] to norm so I need to
    # shift pitch by 90 degrees.
    roll, pitch, yaw = euler_angle 
    assert(roll == 0.0)
    pitch += np.pi / 2.0 
    plane_line = 'bit plane%d(Vector p) {\n' \
                 '  return renderPlane(p, %f, %f, %f, %f, %f, %f, %f);\n' \
                 '}\n' % (idx, x, y, z, -offset, roll, pitch, yaw)
    flag = '' if len(planes) == 1 else 'else' \
              if idx == len(planes) - 1 else 'if (??) '
    inner_line = '%s {\n' \
                 '  return plane%d(p);\n' \
                 '}\n' % (flag, idx)
    return plane_line, inner_line
    
  content = ''
  for idx, plane in enumerate(planes):
    plane_line, inner_line = GenerateInnerPlane(idx, plane)
    write_str += plane_line
    content += inner_line
  if not planes:
    content += 'assert false;\n' \
               'return false;'
  write_str += 'generator bit getPlane(Vector p) {\n' \
               '%s\n' \
               '}\n' \
               '\n' % content

  # Encode cylinders.
  def GenerateInnerCylinder(idx, cylinder):
    center, norm, radius = cylinder
    cx, cy, cz = center
    dx, dy, dz = norm
    euler_angle = NormToRotationAngles(norm)
    # In sketch I assume roll, pitch, yaw rotates [0, 0, 1] to norm so I need to
    # shift pitch by 90 degrees.
    roll, pitch, yaw = euler_angle 
    assert(roll == 0.0)
    pitch += np.pi / 2.0 
    cylinder_line = 'bit cylinder%d(Vector p) {\n' \
      '  return renderCylinder(p, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);\n' \
      '}\n' % (idx, cx, cy, cz, dx, dy, dz, radius, roll, pitch, yaw)
    flag = '' if len(cylinders) == 1 else 'else' \
              if idx == len(cylinders) - 1 else 'if (??) '
    inner_line = '%s {\n' \
                 '  return cylinder%d(p);\n' \
                 '}\n' % (flag, idx)
    return cylinder_line, inner_line
    
  content = ''
  for idx, cylinder in enumerate(cylinders):
    cylinder_line, inner_line = GenerateInnerCylinder(idx, cylinder)
    write_str += cylinder_line
    content += inner_line
  if not cylinders:
    content += 'assert false;\n' \
               'return false;'
  write_str += 'generator bit getCylinder(Vector p) {\n' \
               '%s\n' \
               '}\n' \
               '\n' % content

  # Write into file.
  with open(output_sketch_file, 'w') as f:
    f.write(write_str)

def GenerateAuxiliaryPlanes(spheres, planes, cylinders, tori):
  # Now add separators (auxiliary primitives).
  # The algorithm is: we first collect all normals from planes, assemble or
  # extend them into orthonormal coordinates. For each coordinate, we collect
  # offsets from all planes, all sphere centers, and all cylinder centers.
  # For a cylinder, we collect offsets by projecting all planes and all sphere
  # centers to its normal.
  coords = ComputeOrthonormalAxis(planes)
  print('surface_primitive_to_sketch::GenerateAuxiliaryPlanes.')
  print('All axis (%d): ' % len(coords))
  PrettyPrintList(coords)
  rotations_and_offsets = []
  all_planes = planes
  init_plane_num = len(planes)
  for coord in coords:
    x, y, z = coord
    # Collect offsets from planes.
    offsets_x = CollectOffsetsAlongNormal(planes, x)
    offsets_y = CollectOffsetsAlongNormal(planes, y)
    offsets_z = CollectOffsetsAlongNormal(planes, z)
    # Collect offsets from spheres.
    sphere_offsets_x, sphere_offsets_y, sphere_offsets_z = \
      GetSphereOffsetsAlongCoords(spheres, coord)
    # Collect offsets from cylinders.
    cylinder_offsets_x, cylinder_offsets_y, cylinder_offsets_z = \
      GetCylinderOffsetsAlongCoords(cylinders, coord)
    # Merge.
    offsets_x += sphere_offsets_x + cylinder_offsets_x
    offsets_y += sphere_offsets_y + cylinder_offsets_y
    offsets_z += sphere_offsets_z + cylinder_offsets_z
    rotations_and_offsets.append(RotationsAndOffsets(coord, \
      offsets_x, offsets_y, offsets_z))
    # Add auxiliary planes. 
    for d in offsets_x:
      plane = MakePlane([x.x, x.y, x.z, -d])
      if IsNew(plane, all_planes, SamePlane, 1e-2):
        all_planes.append(plane)
    for d in offsets_y:
      plane = MakePlane([y.x, y.y, y.z, -d])
      if IsNew(plane, all_planes, SamePlane, 1e-2):
        all_planes.append(plane)
    for d in offsets_z:
      plane = MakePlane([z.x, z.y, z.z, -d])
      if IsNew(plane, all_planes, SamePlane, 1e-2):
        all_planes.append(plane)
  # Print the number of rotations and offsets.
  print('Rotations and offsets (%d): ' % len(rotations_and_offsets))
  PrettyPrintList(rotations_and_offsets)

  # Create cylinder hints.
  cylinder_hints = []
  for c in cylinders:
    center, norm, radius = c
    offsets = CollectOffsetsAlongNormal(planes, norm)
    euler_angles = NormToRotationAngles(norm)
    R = EulerAnglesToMatrix(euler_angles)
    coord = Coordinates(Vector3d(*R[:,0]), Vector3d(*R[:,1]), Vector3d(*R[:,2]))
    offsets += GetSphereOffsetsAlongCoords(spheres, coord)[0]
    _, y, z = np.dot(center, R)
    cylinder_hints.append(CylinderHints(coord, radius, y, z, offsets))
    # Add more planes.
    for d in offsets:
      plane = MakePlane([norm.x, norm.y, norm.z, -d])
      if IsNew(plane, all_planes, SamePlane, 1e-2):
        all_planes.append(plane)
  print('Cylinder hints (%d): ' % len(cylinder_hints))
  PrettyPrintList(cylinder_hints)
  print('GenerateAuxiliaryPlanes: done.')
  return all_planes[init_plane_num:]

def SolidifySurfacePrimitives(spheres, planes, cylinders, tori, max_offset):
  # Given spheres, planes, and cylinders, do the following:
  # - For spheres: do nothing.
  # - For planes: generate CuboidHint using EXISTING planes only. The algorithm
  #   works as followsing:
  #   - a) Check all triplets of normals to see if they are orthogonal. If so,
  #        use them to generate a CuboidHint, collect parallel planes, and add
  #        two more planes at +/-max_offset.
  #   - b) Check each pair of normals to see if they are orthogonal AND if there
  #        is no other normals that are orthogonal to both. We add two planes at
  #        +/-max_offset to generate another CuboidHint.
  #   - c) Finally, for those planes whose normals never appeared in a) or b),
  #        we add two planes at +/-max_offset to generate the CuboidHint.
  # - For cylinders: generate CylinderHint for each cylinder using EXISTING
  #   planes only. In other words, we loop over all planes and add those with
  #   the same direction as the cylinder axis. Furthermore, we add two more
  #   planes at +/-max_offset.
  coords = ComputeOrthonormalAxis(planes)
  print('surface_primitive_to_sketch::SolidifySurfacePrimitives.')
  print('All axis (%d): ' % len(coords))
  PrettyPrintList(coords)
  rotations_and_offsets = []
  for coord in coords:
    x, y, z = coord
    # Collect offsets from planes.
    offsets_x = CollectOffsetsAlongNormal(planes, x)
    offsets_y = CollectOffsetsAlongNormal(planes, y)
    offsets_z = CollectOffsetsAlongNormal(planes, z)
    offsets_x += [-max_offset, max_offset]
    offsets_y += [-max_offset, max_offset]
    offsets_z += [-max_offset, max_offset]
    rotations_and_offsets.append(RotationsAndOffsets(coord, \
      offsets_x, offsets_y, offsets_z))
  # Print the number of rotations and offsets.
  print('Rotations and offsets (%d): ' % len(rotations_and_offsets))
  PrettyPrintList(rotations_and_offsets)

  # Create cylinder hints.
  cylinder_hints = []
  for c in cylinders:
    center, norm, radius = c
    offsets = CollectOffsetsAlongNormal(planes, norm)
    offsets += [-max_offset, max_offset]
    euler_angles = NormToRotationAngles(norm)
    R = EulerAnglesToMatrix(euler_angles)
    coord = Coordinates(Vector3d(*R[:,0]), Vector3d(*R[:,1]), Vector3d(*R[:,2]))
    _, y, z = np.dot(center, R)
    cylinder_hints.append(CylinderHints(coord, radius, y, z, offsets))
  print('Cylinder hints (%d): ' % len(cylinder_hints))
  PrettyPrintList(cylinder_hints)

  return spheres, rotations_and_offsets, cylinder_hints, tori

# Note that this is just a rough estimation.
def CountMinimumNumberOfSolidPrimitives(prim_file):
  spheres, planes, cylinders, tori = ReadPrimitiveFile(prim_file)
  return len(spheres) + len(cylinders) + len(planes) // 6 + len(tori)

def WriteSurfacePrimitivesToSolidSketch(prim_file, sketch_file, max_offset):
  spheres, planes, cylinders, tori = ReadPrimitiveFile(prim_file)
  spheres, rotations_and_offsets, cylinder_hints, tori = \
    SolidifySurfacePrimitives(spheres, planes, cylinders, tori, max_offset)
  # Add a giant sphere to allow for negation if necessary.
  spheres.append(MakeSphere([0.0, 0.0, 0.0, 3.0 * max_offset]))
  WriteSolidPrimitivesToSketch(sketch_file, spheres, rotations_and_offsets, \
    cylinder_hints, tori)

def WriteSolidPrimitivesToSketch(file_name, spheres, rotations_and_offsets, \
  cylinder_hints, tori):
  outer_string = 'generator bit getSphere(Vector p) {\n' \
                 'SPHERE_CONTENT\n' \
                 '}\n' \
                 'generator bit getTorus(Vector p) {\n' \
                 'TORUS_CONTENT\n' \
                 '}\n' \
                 '\n'  \
                 'CUBOID_HINT\n' \
                 '\n' \
                 'CYLINDER_HINT\n'
  write_str = ''
  def GenerateSphere(idx, sphere):
    center, radius = sphere
    x, y, z = center
    sphere_line = 'bit sphere%d(Vector p) {{\n' \
                  '  return renderSphere(p, %f, %f, %f, %f);\n' \
                  '}}\n' % (idx, x, y, z, radius)
    flag = '' if len(spheres) == 1 else 'else' \
              if idx == len(spheres) - 1 else 'if (??) '
    inner_line = '%s {{\n' \
                 'return sphere%d(p);\n' \
                 '}}\n' % (flag, idx)
    return sphere_line, inner_line
    
  content = ''
  for idx, sphere in enumerate(spheres):
    sphere_line, inner_line = GenerateSphere(idx, sphere)
    write_str += sphere_line
    content += inner_line
  if not spheres:
    content += 'assert false;\n' \
               'return false;'
  write_str += outer_string.replace('SPHERE_CONTENT', content)

  # Generate cuboid hints.
  def PrintList(l):
    return str(l).replace('[', '{').replace(']', '}')
  def GenerateCuboidHint(rotation_and_offset):
    coord, x, y, z = rotation_and_offset
    roll, pitch, yaw = CoordToEulerAngle(coord)
    inner_line = 'new CuboidHint(theta_x = %f, theta_y = %f, theta_z = %f,\n' \
                 '  xlen = %d, ylen = %d, zlen = %d,\n' \
                 '  xlist = %s,\n' \
                 '  ylist = %s,\n' \
                 '  zlist = %s)\n' % \
                 (float(roll), float(pitch), float(yaw), \
                  len(x), len(y), len(z), \
                  PrintList(x), PrintList(y), PrintList(z))
    return inner_line
  # End of cuboid hint functions.
  cuboid_hint = ''
  if not rotations_and_offsets:
    cuboid_hint = 'int numCuboidHints = 1;\n' \
                  'CuboidHint[numCuboidHints] cuboidHints = {null};\n'
  else:
    cuboid_hint = 'int numCuboidHints = %d;\n' \
                  'CuboidHint[numCuboidHints] cuboidHints = CUBOID_HINTS_LIST;'\
                  % len(rotations_and_offsets)
    cuboid_hints_list = '{\n'
    for i, r in enumerate(rotations_and_offsets):
      cuboid_hints_list += GenerateCuboidHint(r)
      if i != len(rotations_and_offsets) - 1:
        cuboid_hints_list += ', \n'
    cuboid_hints_list += '}'
    cuboid_hint = cuboid_hint.replace('CUBOID_HINTS_LIST', cuboid_hints_list)
  write_str = write_str.replace('CUBOID_HINT', cuboid_hint)

  # Generate cylinder hints.
  def GenerateCylinderHint(c):
    coord, radius, y, z, offsets = c
    roll, pitch, yaw = CoordToEulerAngle(coord)
    inner_line = \
      'new CylinderHint(theta_x = %f, theta_y = %f, theta_z = %f,\n'\
      '                 radius = %f, y = %f, z = %f, xlen = %d,\n' \
      '                 xlist = %s)\n' % \
      (float(roll), float(pitch), float(yaw), float(radius), \
       float(y), float(z), len(offsets), PrintList(offsets))
    return inner_line
  # End of the helper function.
  cylinder_hint = ''
  if not cylinder_hints:
    cylinder_hint = 'int numCylinderHints = 1;\n' \
                    'CylinderHint[numCylinderHints] cylinderHints = {null};\n'
  else:
    cylinder_hint = \
      'int numCylinderHints = %d;\n' \
      'CylinderHint[numCylinderHints] cylinderHints = CYLINDER_HINTS_LIST;\n' \
      % (len(cylinder_hints))
    cylinder_hints_list = '{\n'
    for i, c in enumerate(cylinder_hints):
      cylinder_hints_list += GenerateCylinderHint(c)
      if i != len(cylinder_hints) - 1:
        cylinder_hints_list += ', \n'
    cylinder_hints_list += '}'
    cylinder_hint = cylinder_hint.replace('CYLINDER_HINTS_LIST', \
      cylinder_hints_list)
  write_str = write_str.replace('CYLINDER_HINT', cylinder_hint)

  # Tori.
  def GenerateTorus(idx, torus):
    center, norm, R, r = torus
    cx, cy, cz = center
    # Compute roll, pitch, yaw from norm.
    nx, ny, nz = norm
    euler_angles = NormToRotationAngles(norm)
    roll, pitch, yaw = euler_angles
    torus_line = 'bit torus%d(Vector p) {{\n' \
                 '  return renderTorus(p, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);\n' \
                 '}}\n' % (idx, cx, cy, cz, nx, ny, nz, roll, pitch, yaw, R, r)
    flag = '' if len(tori) == 1 else 'else' \
              if idx == len(tori) - 1 else 'if (??) '
    inner_line = '%s {{\n' \
                 'return torus%d(p);\n' \
                 '}}\n' % (flag, idx)
    return torus_line, inner_line
 
  content = ''
  for idx, torus in enumerate(tori):
    torus_line, inner_line = GenerateTorus(idx, torus)
    write_str += torus_line
    content += inner_line
  if not tori:
    content += 'assert false;\n' \
               'return false;'
  write_str = write_str.replace('TORUS_CONTENT', content)

  # Write into file.
  with open(file_name, 'w') as f:
    f.write(write_str)

if __name__ == '__main__':
  # Do nothing.
  pass
