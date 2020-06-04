translate([-0.000000, -1.668193, -0.000000])
difference() {
  union() {
    sphere(r = 3.336382, $fn = 60);
    translate([0.000000, 3.336382, 0.000000])
    sphere(r = 3.336382, $fn = 60);
  }
  translate([0.000000, -3.336382, 0.000000])
  cube(size = [3.002744, 4.003658, 2.669105], center = false);
}
