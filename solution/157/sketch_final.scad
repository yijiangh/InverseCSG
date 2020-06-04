intersection() {
translate([-6, -6, -3.6]) cube(size = [12, 12, 7.2], center = false);
union() {
difference() {
union() {
translate([1.078, 3.327, -3])
cylinder(h = 6, r1 = 0.502, r2 = 0.502, center = false, $fn = 12);
difference() {
union() {
translate([0.002, -0.01, -3])
cylinder(h = 3, r1 = 4.991, r2 = 4.991, center = false, $fn = 12);
translate([3.497, -0.003, 0])
cylinder(h = 3, r1 = 0.496, r2 = 0.496, center = false, $fn = 12);
}
union() {
translate([-1.075, -3.329, -19])
cylinder(h = 38, r1 = 0.996, r2 = 0.996, center = false, $fn = 12);
translate([-1.081, 3.325, -19])
cylinder(h = 38, r1 = 0.996, r2 = 0.996, center = false, $fn = 12);
}
}
translate([1.081, -3.326, 0])
cylinder(h = 3, r1 = 0.498, r2 = 0.498, center = false, $fn = 12);
translate([0.032, 0.015, 0])
cylinder(h = 2.5, r1 = 1.992, r2 = 1.992, center = false, $fn = 12);
}
union() {
translate([0.004, 0.004, -3])
cylinder(h = 5.5, r1 = 1.495, r2 = 1.495, center = false, $fn = 12);
translate([2.837, -2.072, -3])
cylinder(h = 22, r1 = 0.997, r2 = 0.997, center = false, $fn = 12);
translate([-3.496, -0.013, -3])
cylinder(h = 22, r1 = 0.997, r2 = 0.997, center = false, $fn = 12);
translate([2.83, 2.059, -3])
cylinder(h = 3, r1 = 0.992, r2 = 0.992, center = false, $fn = 12);
}
}
translate([-2.835, -2.058, 0])
cylinder(h = 3, r1 = 0.503, r2 = 0.503, center = false, $fn = 12);
translate([-2.834, 2.051, 0])
cylinder(h = 3, r1 = 0.497, r2 = 0.497, center = false, $fn = 12);
}
}
