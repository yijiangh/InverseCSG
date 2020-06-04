intersection() {
translate([-6.000000, -3.264516, -2.977332])
cube(size = [12.000000, 6.529032, 5.954664], center = false);
union() {
// Begin.
union() {
difference() {
union() {
rotate([0, -0.0974028, -0.0349504])
translate([1.35175, 0.00311, -0.03972])
rotate([0, 90, 0])
cylinder(h = 7.2965, r1 = 2.17617, r2 = 2.17617, center = true, $fn = 12);

rotate([0, 0.027502, 0.00286479])
translate([-2.99958, -0.01139, -0.0133])
rotate([0, 90, 0])
cylinder(h = 4.00084, r1 = 2.4835, r2 = 2.4835, center = true, $fn = 12);
}

union() {
union() {
rotate([0, 0.0315127, 0.0395341])
translate([-3.64825, 0.002361, -1.44653])
rotate([0, 90, 0])
cylinder(h = 2.7035, r1 = 0.5923, r2 = 0.5923, center = true, $fn = 12);

rotate([0, -0, 0])
translate([2.88655, -0.000479996, 0])
cube(size = [4.2269, 1.63208, 36.4], center = true);
}

rotate([0, -0.100268, -0.0842248])
translate([-10.2483, -0.007944, 1.50162])
rotate([0, 90, 0])
cylinder(h = 15.9035, r1 = 0.6011, r2 = 0.6011, center = true, $fn = 12);
}
}

intersection() {
rotate([0, -0, 0])
translate([9.48655, 0, 8.37674])
cube(size = [17.4269, 36.4, 19.6465], center = true);

intersection() {
union() {
translate([3.3064, -0.10321, -0.01738])
rotate([0, -0.696144, 1.23547])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.24781, 0, 0])
circle(r = 0.37765, $fn = 12);

difference() {
translate([3.37272, -0.17168, -0.05466])
rotate([0, -0.054431, 0.740834])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.48883, 0, 0])
circle(r = 0.381, $fn = 12);

rotate([0, -0, 90])
translate([-9.50826, -3.12375, -0.48886])
rotate([0, 90, 0])
cylinder(h = 17.3835, r1 = 1.87625, r2 = 1.87625, center = true, $fn = 12);
}
}

rotate([0, -0, 90])
translate([0, -3.12375, -0.48886])
rotate([0, 90, 0])
cylinder(h = 36.4, r1 = 1.87625, r2 = 1.87625, center = true, $fn = 12);
}
}
}
// End.
}
}
