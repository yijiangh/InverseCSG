res = 60;

module cys(r, h, d, a) {
  rotate([0, 0, a])
  translate([d, 0, 0])
  cylinder(r = r, h = h, center = true, $fn = res);
}

translate([0, 0, 0.25])
difference() {
union() {
  translate([0, 0, -1.5])
  cube(size = [10, 10, 3], center = true);
  cys(3, 3, 0, 0);
  translate([0, 0, 1.75])
  cys(2.5, 1, 0, 0);
  translate([0, 0, 2.25])
  cys(3, 0.5, 0, 0);
}

union() {
cys(0.5, 10, 4.5, 30);
cys(0.5, 10, 4.5, 120);
cys(0.5, 10, 4.5, 210);
cys(0.5, 10, 4.5, 300);
  
cys(1.5, 10, 6.5, 45);
cys(1.5, 10, 6.5, 135);
cys(1.5, 10, 6.5, 225);
cys(1.5, 10, 6.5, 315);

translate([0, 0, 3])
cys(1.5, 3, 0, 0);

translate([0, 0, 4])
cys(1, 6, 0, 0);
}
}