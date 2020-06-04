import os
import sys

# Usage: python3 run_tests.py <build_dir> <test_name>
# Example:
# python3 run_tests.py ../build one_cube
# python3 run_tests.py ../build one_sphere
# python3 run_tests.py ../build 001
# python3 run_tests.py ../build 011

if len(sys.argv) < 3:
  print('Error: please specify the test case name.')
  sys.exit(-1)

build_dir = sys.argv[1]
test_name = sys.argv[2]

if test_name == 'one_cube':
  os.system('python3 main.py --builddir %s --outdir ../one_cube --mesh example/one_cube/csg_low_res.off --eps 0.1 --surfacedensity 100 --volumedensity 10' % build_dir)
elif test_name == 'rotated_cuboid':
  os.system('python3 main.py --builddir %s --outdir ../rotated_cuboid --mesh example/rotated_cuboid/csg_low_res.off --eps 0.1 --surfacedensity 100 --volumedensity 10' % build_dir)
elif test_name == 'two_cuboids':
  os.system('python3 main.py --builddir %s --outdir ../two_cuboids --mesh example/two_cuboids/csg_low_res.off --eps 0.1 --surfacedensity 100 --volumedensity 10' % build_dir)
elif test_name == 'one_sphere':
  os.system('python3 main.py --builddir %s --outdir ../one_sphere --mesh example/one_sphere/csg_high_res.off --eps 0.1 --surfacedensity 100 --volumedensity 10' % build_dir)
elif test_name == 'one_cylinder':
  os.system('python3 main.py --builddir %s --outdir ../one_cylinder --mesh example/one_cylinder/csg_high_res.off --eps 0.1 --surfacedensity 100 --volumedensity 10' % build_dir)
elif test_name == 'rotated_cylinder':
  os.system('python3 main.py --builddir %s --outdir ../rotated_cylinder --mesh example/rotated_cylinder/csg_high_res.off --eps 0.1 --surfacedensity 100 --volumedensity 10' % build_dir)
elif test_name == 'three_cuboids_one_cylinder':
  os.system('python3 main.py --builddir %s --outdir ../three_cuboids_one_cylinder --mesh example/three_cuboids_one_cylinder/csg_high_res.off --eps 0.1 --surfacedensity 100 --volumedensity 10' % build_dir)
elif test_name == 'torus':
  os.system('python3 main.py --builddir %s --outdir ../torus --mesh example/torus/csg_high_res.off --eps 0.1 --surfacedensity 4000 --volumedensity 100' % build_dir)
elif test_name == 'torus_cube':
  os.system('python3 main.py --builddir %s --outdir ../torus_cube --mesh example/torus_cube/csg_high_res.off --eps 0.1 --surfacedensity 400 --volumedensity 100' % build_dir)
elif test_name == 'single_torus':
  os.system('python3 main.py --builddir %s --outdir ../single_torus --mesh example/single_torus/csg_high_res.off --eps 0.1 --surfacedensity 40 --volumedensity 10' % build_dir)
elif test_name == 'spot':
  os.system('python3 main.py --builddir %s --outdir ../spot --mesh example/spot/csg_high_res.off --eps 0.1 --surfacedensity 4000 --volumedensity 100 --timeout 180' % build_dir)
elif test_name == 'double_torus':
  os.system('python3 main.py --builddir %s --outdir ../double_torus --mesh example/double_torus/csg_high_res.off --eps 0.1 --surfacedensity 4000 --volumedensity 100' % build_dir)
elif test_name == 'bunny':
  os.system('python3 main.py --builddir %s --outdir ../bunny --mesh example/bunny/csg_high_res.off --eps 0.1 --surfacedensity 4000 --volumedensity 100' % build_dir)
elif test_name == 'ex_163':
  os.system('python3 main.py --builddir %s --outdir ../ex_163 --mesh example/163/csg_high_res.off --eps 0.05 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_164':
  os.system('python3 main.py --builddir %s --outdir ../ex_164 --mesh example/164/csg_high_res.off --eps 0.01 --surfacedensity 4000 --volumedensity 100' % build_dir)
elif test_name == 'ex_165':
  os.system('python3 main.py --builddir %s --outdir ../ex_165 --mesh example/165/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 100' % build_dir)
elif test_name == 'ex_166':
  os.system('python3 main.py --builddir %s --outdir ../ex_166 --mesh example/166/csg_high_res.off --eps 0.05 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_167':
  os.system('python3 main.py --builddir %s --outdir ../ex_167 --mesh example/167/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_168':
  os.system('python3 main.py --builddir %s --outdir ../ex_168 --mesh example/168/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_169':
  os.system('python3 main.py --builddir %s --outdir ../ex_169 --mesh example/169/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_170':
  os.system('python3 main.py --builddir %s --outdir ../ex_170 --mesh example/170/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_171':
  os.system('python3 main.py --builddir %s --outdir ../ex_171 --mesh example/171/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_172':
  os.system('python3 main.py --builddir %s --outdir ../ex_172 --mesh example/172/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_173':
  os.system('python3 main.py --builddir %s --outdir ../ex_173 --mesh example/173/csg_high_res.off --eps 0.02 --surfacedensity 4000 --volumedensity 100' % build_dir)
elif test_name == 'ex_174':
  os.system('python3 main.py --builddir %s --outdir ../ex_174 --mesh example/174/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_175':
  os.system('python3 main.py --builddir %s --outdir ../ex_175 --mesh example/175/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_176':
  os.system('python3 main.py --builddir %s --outdir ../ex_176 --mesh example/176/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'base':
  os.system('python3 main.py --builddir %s --outdir ../base --mesh example/base/csg_high_res.off --eps 0.02 --surfacedensity 2000 --volumedensity 25' % build_dir)
elif test_name == 'ex_162':
  os.system('python3 main.py --builddir %s --outdir ../162 --mesh example/162/csg_high_res.off --eps 0.02 --surfacedensity 2000 --volumedensity 25' % build_dir)
elif test_name == 'hallway':
  os.system('python3 main.py --builddir %s --outdir ../hallway --mesh example/hallway/csg_high_res.off --eps 0.02 --surfacedensity 2000 --volumedensity 100' % build_dir)
elif test_name == 'ex_161':
  os.system('python3 main.py --builddir %s --outdir ../161 --mesh example/161/csg_high_res.off --eps 0.02 --surfacedensity 2000 --volumedensity 25' % build_dir)
elif test_name == 'ex_160':
  os.system('python3 main.py --builddir %s --outdir ../ex_160 --mesh example/160/csg_high_res.off --initsample 100 --countersample 100 --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_011':
  os.system('python3 main.py --builddir %s --outdir ../ex_011 --mesh example/011/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_023':
  os.system('python3 main.py --builddir %s --outdir ../ex_023 --mesh example/023/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25 --timeout 1800' % build_dir)
elif test_name == 'ex_039':
  os.system('python3 main.py --builddir %s --outdir ../ex_039 --mesh example/039/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_040':
  os.system('python3 main.py --builddir %s --outdir ../ex_040 --mesh example/040/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_041':
  os.system('python3 main.py --builddir %s --outdir ../ex_041 --mesh example/041/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_043':
  os.system('python3 main.py --builddir %s --outdir ../ex_043 --mesh example/043/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_045':
  os.system('python3 main.py --builddir %s --outdir ../ex_045 --mesh example/045/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_046':
  os.system('python3 main.py --builddir %s --outdir ../ex_046 --mesh example/046/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_050':
  os.system('python3 main.py --builddir %s --outdir ../ex_050 --mesh example/050/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_054':
  os.system('python3 main.py --builddir %s --outdir ../ex_054 --mesh example/054/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_056':
  os.system('python3 main.py --builddir %s --outdir ../ex_056 --mesh example/056/csg_high_res.off --eps 0.02 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_057':
  os.system('python3 main.py --builddir %s --outdir ../ex_057 --mesh example/057/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_059':
  os.system('python3 main.py --builddir %s --outdir ../ex_059 --mesh example/059/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_060':
  os.system('python3 main.py --builddir %s --outdir ../ex_060 --mesh example/060/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_062':
  os.system('python3 main.py --builddir %s --outdir ../ex_062 --mesh example/062/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_065':
  os.system('python3 main.py --builddir %s --outdir ../ex_065 --mesh example/065/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_066':
  os.system('python3 main.py --builddir %s --outdir ../ex_066 --mesh example/066/csg_high_res.off --eps 0.02 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_067':
  os.system('python3 main.py --builddir %s --outdir ../ex_067 --mesh example/067/csg_high_res.off --eps 0.05 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_068':
  os.system('python3 main.py --builddir %s --outdir ../ex_068 --mesh example/068/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_069':
  os.system('python3 main.py --builddir %s --outdir ../ex_069 --mesh example/069/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_072':
  os.system('python3 main.py --builddir %s --outdir ../ex_072 --mesh example/072/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_074':
  os.system('python3 main.py --builddir %s --outdir ../ex_074 --mesh example/074/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_075':
  os.system('python3 main.py --builddir %s --outdir ../ex_075 --mesh example/075/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_078':
  os.system('python3 main.py --builddir %s --outdir ../ex_078 --mesh example/081/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_079':
  os.system('python3 main.py --builddir %s --outdir ../ex_079 --mesh example/079/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_081':
  os.system('python3 main.py --builddir %s --outdir ../ex_081 --mesh example/081/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_082':
  os.system('python3 main.py --builddir %s --outdir ../ex_082 --mesh example/082/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_090':
  os.system('python3 main.py --builddir %s --outdir ../ex_090 --mesh example/090/csg_high_res.off --eps 0.05 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_091':
  os.system('python3 main.py --builddir %s --outdir ../ex_091 --mesh example/091/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_096':
  os.system('python3 main.py --builddir %s --outdir ../ex_096 --mesh example/096/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_098':
  os.system('python3 main.py --builddir %s --outdir ../ex_098 --mesh example/098/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_101':
  os.system('python3 main.py --builddir %s --outdir ../ex_101 --mesh example/101/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_102':
  os.system('python3 main.py --builddir %s --outdir ../ex_102 --mesh example/102/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_103':
  os.system('python3 main.py --builddir %s --outdir ../ex_103 --mesh example/105/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_104':
  os.system('python3 main.py --builddir %s --outdir ../ex_104 --mesh example/104/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_105':
  os.system('python3 main.py --builddir %s --outdir ../ex_105 --mesh example/105/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_106':
  os.system('python3 main.py --builddir %s --outdir ../ex_106 --mesh example/106/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_107':
  os.system('python3 main.py --builddir %s --outdir ../ex_107 --mesh example/107/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_108':
  os.system('python3 main.py --builddir %s --outdir ../ex_108 --mesh example/108/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_109':
  os.system('python3 main.py --builddir %s --outdir ../ex_109 --mesh example/109/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_111':
  os.system('python3 main.py --builddir %s --outdir ../ex_111 --mesh example/111/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_112':
  os.system('python3 main.py --builddir %s --outdir ../ex_112 --mesh example/112/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_114':
  os.system('python3 main.py --builddir %s --outdir ../ex_114 --mesh example/114/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_115':
  os.system('python3 main.py --builddir %s --outdir ../ex_115 --mesh example/115/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_117':
  os.system('python3 main.py --builddir %s --outdir ../ex_117 --mesh example/117/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_118':
  os.system('python3 main.py --builddir %s --outdir ../ex_118 --mesh example/118/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_122':
  os.system('python3 main.py --builddir %s --outdir ../ex_122 --mesh example/122/csg_high_res.off --eps 0.01 --surfacedensity 2000 --volumedensity 50' % build_dir)
elif test_name == 'ex_123':
  os.system('python3 main.py --builddir %s --outdir ../ex_123 --mesh example/123/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_126':
  os.system('python3 main.py --builddir %s --outdir ../ex_126 --mesh example/126/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_127':
  os.system('python3 main.py --builddir %s --outdir ../ex_127 --mesh example/127/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_128':
  os.system('python3 main.py --builddir %s --outdir ../ex_128 --mesh example/128/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_129':
  os.system('python3 main.py --builddir %s --outdir ../ex_129 --mesh example/129/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_130':
  os.system('python3 main.py --builddir %s --outdir ../ex_130 --mesh example/130/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_131':
  os.system('python3 main.py --builddir %s --outdir ../ex_131 --mesh example/131/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_133':
  os.system('python3 main.py --builddir %s --outdir ../ex_133 --mesh example/133/csg_high_res.off --eps 0.01 --surfacedensity 4000 --volumedensity 200' % build_dir)
elif test_name == 'ex_134':
  os.system('python3 main.py --builddir %s --outdir ../ex_134 --mesh example/134/csg_high_res.off --eps 0.05 --surfacedensity 1000 --volumedensity 10' % build_dir)
elif test_name == 'ex_139':
  os.system('python3 main.py --builddir %s --outdir ../ex_139 --mesh example/139/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_140':
  os.system('python3 main.py --builddir %s --outdir ../ex_140 --mesh example/140/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 50' % build_dir)
elif test_name == 'ex_142':
  os.system('python3 main.py --builddir %s --outdir ../ex_142 --mesh example/142/csg_high_res.off --eps 0.01 --surfacedensity 2000 --volumedensity 50' % build_dir)
elif test_name == 'ex_143':
  os.system('python3 main.py --builddir %s --outdir ../ex_143 --mesh example/143/csg_high_res.off --eps 0.01 --surfacedensity 1000 --volumedensity 200' % build_dir)
elif test_name == 'ex_144':
  os.system('python3 main.py --builddir %s --outdir ../ex_144 --mesh example/144/csg_high_res.off --eps 0.01 --surfacedensity 4000 --volumedensity 200' % build_dir)
elif test_name == 'ex_145':
  os.system('python3 main.py --builddir %s --outdir ../ex_145 --mesh example/145/csg_high_res.off --eps 0.01 --surfacedensity 4000 --volumedensity 200' % build_dir)
elif test_name == 'ex_146':
  os.system('python3 main.py --builddir %s --outdir ../ex_146 --mesh example/146/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_147':
  os.system('python3 main.py --builddir %s --outdir ../ex_147 --mesh example/147/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_148':
  os.system('python3 main.py --builddir %s --outdir ../ex_148 --mesh example/148/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_150':
  os.system('python3 main.py --builddir %s --outdir ../ex_150 --mesh example/150/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_151':
  os.system('python3 main.py --builddir %s --outdir ../ex_151 --mesh example/151/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_152':
  os.system('python3 main.py --builddir %s --outdir ../ex_152 --mesh example/152/csg_high_res.off --eps 0.01 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_153':
  os.system('python3 main.py --builddir %s --outdir ../ex_153 --mesh example/153/csg_high_res.off --eps 0.02 --surfacedensity 1000 --volumedensity 25 --timeout 600' % build_dir)
elif test_name == 'ex_155':
  os.system('python3 main.py --builddir %s --outdir ../ex_155 --mesh example/155/csg_high_res.off --eps 0.01 --surfacedensity 4000 --volumedensity 200' % build_dir)
elif test_name == 'ex_156':
  os.system('python3 main.py --builddir %s --outdir ../ex_156 --mesh example/156/csg_high_res.off --eps 0.01 --surfacedensity 4000 --volumedensity 200' % build_dir)
elif test_name == 'ex_157':
  os.system('python3 main.py --builddir %s --outdir ../ex_157 --mesh example/157/csg_high_res.off --eps 0.1 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_158':
  os.system('python3 main.py --builddir %s --outdir ../ex_158 --mesh example/158/csg_high_res.off --eps 0.1 --surfacedensity 250 --volumedensity 25' % build_dir)
elif test_name == 'ex_159':
  os.system('python3 main.py --builddir %s --outdir ../ex_159 --mesh example/159/csg_high_res.off --eps 0.025 --surfacedensity 250 --volumedensity 25' % build_dir)
else:
  print('Unknown test case: %s' % test_name)
  sys.exit(-1)
