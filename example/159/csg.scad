res = 60;

module cys(r, h, d, a) {
  rotate([0, 0, a])
  translate([d, 0, 0])
  cylinder(r = r, h = h, center = true, $fn = res);
}

difference() {
  cube(size = [6, 6, 10], center = true);

  union() {
    cys(0.3, 20, 2.75, 27);
    cys(0.3, 20, 2.75, 27 + 90);
    cys(0.3, 20, 2.75, 27 + 180);
    cys(0.3, 20, 2.75, 27 + 270);
    
    cys(2.25, 20, 0, 0);
    
    cys(0.75, 20, 3.5, 45);
    cys(0.75, 20, 3.5, 45 + 90);
    cys(0.75, 20, 3.5, 45 + 180);
    cys(0.75, 20, 3.5, 45 + 270);
  }
}