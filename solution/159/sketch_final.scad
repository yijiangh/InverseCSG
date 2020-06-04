intersection() {
translate([-3.6, -3.6, -6]) cube(size = [7.2, 7.2, 12], center = false);
union() {
intersection() {
translate([-3, -3, -5]) cube(size = [6, 21.25, 10], center = false);
translate([2.484, 2.472, -18.25])
cylinder(h = 13.25, r1 = 0.75, r2 = 0.75, center = false, $fn = 12);
}
intersection() {
difference() {
translate([-3, -3, -5]) cube(size = [6, 6, 10], center = false);
union() {
translate([-1.251, 2.451, -5])
cylinder(h = 23.25, r1 = 0.293, r2 = 0.293, center = false, $fn = 12);
translate([0.01, -0.01, -18.25])
cylinder(h = 36.5, r1 = 2.251, r2 = 2.251, center = false, $fn = 12);
}
}
difference() {
difference() {
difference() {
translate([0, 0, 0]) sphere(r = 54.75, $fn = 12);
translate([-2.453, -1.251, -18.25])
cylinder(h = 23.25, r1 = 0.299, r2 = 0.299, center = false, $fn = 12);
}
union() {
translate([2.473, -2.475, -18.25])
cylinder(h = 36.5, r1 = 0.751, r2 = 0.751, center = false, $fn = 12);
translate([2.484, 2.472, -18.25])
cylinder(h = 23.25, r1 = 0.75, r2 = 0.75, center = false, $fn = 12);
}
}
union() {
translate([1.246, -2.448, -18.25])
cylinder(h = 23.25, r1 = 0.302, r2 = 0.302, center = false, $fn = 12);
translate([2.452, 1.25, -18.25])
cylinder(h = 23.25, r1 = 0.303, r2 = 0.303, center = false, $fn = 12);
translate([-2.463, 2.471, -5])
cylinder(h = 10, r1 = 0.747, r2 = 0.747, center = false, $fn = 12);
translate([-2.475, -2.466, -5])
cylinder(h = 23.25, r1 = 0.745, r2 = 0.745, center = false, $fn = 12);
}
}
}
}
}
