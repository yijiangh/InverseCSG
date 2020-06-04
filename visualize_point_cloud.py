import sys
import os
import numpy as np
import helper
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def VisualizePointCloud(data_file):
  points = helper.LoadDataFile(data_file)
  fig = plt.figure()
  ax = Axes3D(fig)
  ax.scatter(points[:, 0], points[:, 1], points[:, 2], c = 'r')
  ax.set_xlabel('x')
  ax.set_ylabel('y')
  ax.set_zlabel('z')
  ax.set_aspect('equal')
  plt.show()

if __name__ == '__main__':
  # Usage: python3 visualize_point_cloud.py <data file>
  VisualizePointCloud(sys.argv[1])
