union() {
translate([0, 0, -1.5])
cube(size = [10, 10, 3], center = true);

difference() {
cylinder(h = 6, r1 = 2, r2 = 2, center = true, $fn = 30);
cylinder(h = 8, r1 = 1, r2 = 1, center = true, $fn = 30);
}

difference() {
difference() {
cylinder(h = 4, r1 = 4, r2 = 4, center = true, $fn = 30);
cylinder(h = 8, r1 = 3, r2 = 3, center = true, $fn = 30);
}

translate([0, 0, 2])
union() {
cube(size = [1, 10, 1], center = true);

rotate([0, 0, 45])
cube(size = [1, 10, 1], center = true);

rotate([0, 0, 90])
cube(size = [1, 10, 1], center = true);

rotate([0, 0, 135])
cube(size = [1, 10, 1], center = true);
}

}
  
}