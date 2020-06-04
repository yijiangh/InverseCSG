translate([-0.817131, -4.391542, -3.400172])
rotate([2, 4, 25])
union() {
  difference() {
    difference() {
      cube(size = [6.117765, 6.117765, 3.670659], center = false);
      translate([-1.835329, -3.058882, -1.835329])
      rotate([30, 0, 15])
      cube(size = [6.117765, 6.117765, 6.117765], center = false);
    }
    translate([7.341317, 0.000000, 1.835329])
    rotate([0, 0, 30])
    rotate([-90, 0, 0])
    cylinder(h = 12.235529, r1 = 0.367066, r2 = 0.367066, center = false, $fn = 60);
  }
  translate([-2.447106, 4.282435, 1.835329])
  rotate([0, 0, -20])
  rotate([0, 30, 0])
  cube(size = [2.447106, 3.670659, 6.117765], center = false);
}
