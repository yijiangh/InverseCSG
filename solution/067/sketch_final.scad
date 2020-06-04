intersection() {
translate([-6, -6, -6]) cube(size = [12, 12, 12], center = false);
union() {
intersection() {
translate([-18.5, -5, -5]) cube(size = [23.5, 10, 10], center = false);
union() {
translate([0, 0, 0]) sphere(r = 55.5, $fn = 12);
translate([0.045, 0.133, 0.177]) sphere(r = 6.632, $fn = 12);
}
difference() {
union() {
translate([0.045, 0.133, 0.177]) sphere(r = 6.632, $fn = 12);
rotate([180, 90, -90])
translate([-0.024, 0.006, -5])
cylinder(h = 23.5, r1 = 3.317, r2 = 3.317, center = false, $fn = 12);
}
union() {
rotate([180, 90, 180])
translate([-0.02, -0.027, -5])
cylinder(h = 10, r1 = 3.306, r2 = 3.306, center = false, $fn = 12);
rotate([180, 90, -90])
translate([-0.024, 0.006, -18.5])
cylinder(h = 23.5, r1 = 3.317, r2 = 3.317, center = false, $fn = 12);
}
}
difference() {
translate([0.045, 0.133, 0.177]) sphere(r = 6.632, $fn = 12);
intersection() {
translate([0, 0, 0]) sphere(r = 55.5, $fn = 12);
translate([-0.008, -0.035, -18.5])
cylinder(h = 23.5, r1 = 3.316, r2 = 3.316, center = false, $fn = 12);
}
}
translate([-5, -5, -18.5]) cube(size = [23.5, 10, 37], center = false);
}
intersection() {
union() {
translate([-0.008, -0.035, 5])
cylinder(h = 13.5, r1 = 3.316, r2 = 3.316, center = false, $fn = 12);
translate([-18.5, -18.5, 5]) cube(size = [37, 13.5, 13.5], center = false);
}
translate([-18.5, -5, -18.5]) cube(size = [37, 23.5, 23.5], center = false);
}
}
}
