import sys
import os
import numpy as np
import helper
from sklearn import cluster, mixture
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from itertools import cycle, islice

def SegmentPointCloud(data_file, seg_num, seg_file_prefix, visualize=False):
  # Load point cloud data from file.
  points = helper.LoadDataFile(data_file)
  if visualize:
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.scatter(points[:, 0], points[:, 1], points[:, 2], c = 'r')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    ax.set_aspect('equal')
    plt.show()
  # Clustering.
  cluster_result = cluster.AgglomerativeClustering(n_clusters = seg_num)
  cluster_result.fit(points)
  labels = cluster_result.labels_.astype(np.int)
  # Display the segmentation results.
  if visualize:
    colors = np.array(list(islice(cycle(['#377eb8', '#ff7f00', '#4daf4a',
      '#f781bf', '#a65628', '#984ea3', '#999999', '#e41a1c', '#dede00',
      '#000000']), int(max(labels) + 1))))
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.scatter(points[:, 0], points[:, 1], points[:, 2], color = colors[labels])
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    ax.set_aspect('equal')
    plt.show()
  # Save all segmentation results into file. The file names will be:
  # seg_file_prefix_0.data, seg_file_prefix_1.data, ...
  for i in range(seg_num):
    seg_file_name = seg_file_prefix + '_' + str(i) + '.data'
    seg_points = points[np.array(labels)==i, :]
    helper.SaveDataFile(seg_file_name, seg_points)

if __name__ == '__main__':
  # Usage: python3 point_cloud_seg.py <data_file> <seg_num> <seg_file_prefix> <visualize>
  data_file = sys.argv[1]
  seg_num = int(sys.argv[2])
  seg_file_prefix = sys.argv[3]
  visualize = sys.argv[4] == 'True'
  SegmentPointCloud(data_file, seg_num, seg_file_prefix, visualize)
