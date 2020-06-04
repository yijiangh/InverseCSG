intersection() {
union() {
translate([0.002, 1.102, -5])
cylinder(h = 7.169, r1 = 0.222, r2 = 0.222, center = false, $fn = 12);
intersection() {
union() {
rotate([180, 0, 180])
translate([0.002, 0.002, -2.537])
cylinder(h = 20.737, r1 = 1.469, r2 = 1.469, center = false, $fn = 12);
translate([-0.007, 0.001, -4.947]) sphere(r = 3.635, $fn = 12);
intersection() {
translate([0, 0, -1.324])
cylinder(h = 19.524, r1 = 0.22, r2 = 0.22, center = false, $fn = 12);
translate([0, 0, 0]) sphere(r = 54.6, $fn = 12);
}
translate([-0.002, 0.001, 2.348]) sphere(r = 1.179, $fn = 12);
}
union() {
intersection() {
translate([0.002, -1.104, -5])
cylinder(h = 7.169, r1 = 0.22, r2 = 0.22, center = false, $fn = 12);
translate([0, 0, 0]) sphere(r = 54.6, $fn = 12);
}
translate([-1.103, -0.001, -5])
cylinder(h = 7.169, r1 = 0.218, r2 = 0.218, center = false, $fn = 12);
difference() {
union() {
rotate([180, 0, 180])
translate([0.002, 0.002, -18.2])
cylinder(h = 16.031, r1 = 1.469, r2 = 1.469, center = false, $fn = 12);
translate([-18.2, -18.2, -5]) cube(size = [36.4, 36.4, 3.676], center = false);
}
rotate([180, 0, 180])
translate([0.002, 0.002, 5])
cylinder(h = 13.2, r1 = 1.469, r2 = 1.469, center = false, $fn = 12);
}
}
}
translate([1.104, 0, -5])
cylinder(h = 7.537, r1 = 0.222, r2 = 0.222, center = false, $fn = 12);
}
translate([-4.406, -4.406, -6]) cube(size = [8.811, 8.811, 12], center = false);
}
