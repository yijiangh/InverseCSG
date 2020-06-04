translate([-0.000000, -0.000000, -0.000000])
difference() {
  intersection() {
    cube(size = [10.000000, 10.000000, 10.000000], center = true);
    sphere(r = 6.250000, $fn = 60);
  }
  union() {
    rotate([90, 0, 0])
    cylinder(h = 15.000000, r1 = 2.500000, r2 = 2.500000, center = true, $fn = 60);
    rotate([0, 90, 0])
    cylinder(h = 15.000000, r1 = 2.500000, r2 = 2.500000, center = true, $fn = 60);    
    cylinder(h = 15.000000, r1 = 2.500000, r2 = 2.500000, center = true, $fn = 60);
  }
}
