import os
import sys
import numpy as np
import helper

# This file just provides a handy way to debug data files...
# Usage: python3 print_data_file <data file>
if __name__ == '__main__':
  data = helper.LoadDataFile(sys.argv[1])
  print('Dimension: %d x %d' % (data.shape[0], data.shape[1]))
  print(data)
