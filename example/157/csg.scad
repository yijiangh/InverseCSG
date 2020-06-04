res = 60;

module cys(radius, height, dist, angle) {
  rotate([0, 0, angle])
  translate([dist, 0, 0])
  cylinder(h = height, r1 = radius, r2 = radius, center = true, $fn = res);
}

difference() {
union() {
  translate([0, 0, -1.5])
  cys(5, 3, 0, 0);
  
  cys(0.5, 6, 3.5, 0);
  cys(0.5, 6, 3.5, 72);
  cys(0.5, 6, 3.5, 72 * 2);
  cys(0.5, 6, 3.5, 72 * 3);
  cys(0.5, 6, 3.5, 72 * 4);
  
  cys(2, 5, 0, 0);
}

union() {
  cys(1, 10, 3.5, 72 + 36);
  cys(1, 10, 3.5, 72 * 2 + 36);
  cys(1, 10, 3.5, 72 * 3 + 36);
  cys(1, 10, 3.5, 72 * 4 + 36);
  cys(1, 10, 3.5, 72 * 5 + 36);
  cys(1.5, 10, 0, 0);
}
}