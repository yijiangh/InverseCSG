intersection() {
translate([-6, -6, -3.3]) cube(size = [12, 12, 6.6], center = false);
union() {
difference() {
translate([0.009, 0.019, 0.25])
cylinder(h = 1.5, r1 = 2.994, r2 = 2.994, center = false, $fn = 12);
translate([0.014, 0.036, 1.25])
cylinder(h = 1, r1 = 1.003, r2 = 1.003, center = false, $fn = 12);
}
difference() {
union() {
translate([0.009, 0.019, 2.25])
cylinder(h = 0.5, r1 = 2.994, r2 = 2.994, center = false, $fn = 12);
translate([-0.009, 0.002, 1.75])
cylinder(h = 1, r1 = 2.5, r2 = 2.5, center = false, $fn = 12);
}
translate([0.038, 0, 1.75])
cylinder(h = 17.25, r1 = 1.502, r2 = 1.502, center = false, $fn = 12);
}
difference() {
difference() {
difference() {
difference() {
translate([-5, -5, -2.75]) cube(size = [10, 10, 3], center = false);
translate([2.253, -3.906, -2.75])
cylinder(h = 21.75, r1 = 0.5, r2 = 0.5, center = false, $fn = 12);
}
union() {
translate([4.603, -4.614, -2.75])
cylinder(h = 21.75, r1 = 1.517, r2 = 1.517, center = false, $fn = 12);
translate([-4.608, 4.627, -2.75])
cylinder(h = 3, r1 = 1.518, r2 = 1.518, center = false, $fn = 12);
}
}
translate([-3.893, -2.245, -2.75])
cylinder(h = 21.75, r1 = 0.503, r2 = 0.503, center = false, $fn = 12);
}
union() {
translate([-4.62, -4.603, -19])
cylinder(h = 19.25, r1 = 1.518, r2 = 1.518, center = false, $fn = 12);
translate([4.59, 4.608, -2.75])
cylinder(h = 21.75, r1 = 1.502, r2 = 1.502, center = false, $fn = 12);
translate([-2.25, 3.899, -19])
cylinder(h = 19.25, r1 = 0.498, r2 = 0.498, center = false, $fn = 12);
translate([3.898, 2.249, -19])
cylinder(h = 19.25, r1 = 0.504, r2 = 0.504, center = false, $fn = 12);
}
}
}
}
