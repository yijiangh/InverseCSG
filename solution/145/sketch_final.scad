intersection() {
translate([-3.6, -6, -2.4]) cube(size = [7.2, 12, 4.8], center = false);
union() {
difference() {
translate([-1.999, 4.011, 1]) cube(size = [1.51, 0.485, 1], center = false);
translate([-0.489, 3.995, 1.5])
cylinder(h = 16.6, r1 = 0.511, r2 = 0.511, center = false, $fn = 12);
}
difference() {
union() {
difference() {
translate([-3, -5, -2]) cube(size = [2.511, 5, 2], center = false);
translate([-1.499, -3, -18.1])
cylinder(h = 18.1, r1 = 0.401, r2 = 0.401, center = false, $fn = 12);
}
difference() {
translate([-1, 3, 1]) cube(size = [2.466, 1.496, 1], center = false);
translate([0.515, 3, 1.5]) cube(size = [0.493, 1.011, 16.6], center = false);
}
}
union() {
translate([0.515, 4.011, 1.5])
cylinder(h = 0.5, r1 = 0.483, r2 = 0.483, center = false, $fn = 12);
translate([-3, 0.5, 1.5]) cube(size = [3.515, 3.996, 0.5], center = false);
translate([-1.499, -3, -1])
cylinder(h = 2, r1 = 0.599, r2 = 0.599, center = false, $fn = 12);
}
}
difference() {
union() {
translate([-1.999, 0, -2]) cube(size = [4.999, 5, 4], center = false);
translate([-0.489, -5, -2]) cube(size = [3.489, 5, 1], center = false);
translate([0.515, 4.011, 2])
cylinder(h = 16.1, r1 = 0.483, r2 = 0.483, center = false, $fn = 12);
}
union() {
translate([2.5, 4.499, -2])
cylinder(h = 20.1, r1 = 0.199, r2 = 0.199, center = false, $fn = 12);
translate([2.499, 0.499, -18.1])
cylinder(h = 20.1, r1 = 0.2, r2 = 0.2, center = false, $fn = 12);
translate([1.5, -3, -18.1])
cylinder(h = 17.1, r1 = 0.399, r2 = 0.399, center = false, $fn = 12);
translate([-1.999, 0.5, 1]) cube(size = [3.997, 3.996, 17.1], center = false);
}
}
difference() {
translate([-1.999, 0, 1]) cube(size = [0.475, 0.99, 1], center = false);
translate([-1.507, 0.99, 1])
cylinder(h = 17.1, r1 = 0.488, r2 = 0.488, center = false, $fn = 12);
}
difference() {
translate([1.467, 2.469, 0]) cube(size = [0.531, 2.531, 2], center = false);
translate([1.467, 2.469, 1])
cylinder(h = 1, r1 = 0.543, r2 = 0.543, center = false, $fn = 12);
}
difference() {
translate([-3, 3, -2]) cube(size = [2, 2, 4], center = false);
translate([-2.499, 4.502, -2])
cylinder(h = 4, r1 = 0.2, r2 = 0.2, center = false, $fn = 12);
}
difference() {
translate([-3, 0, -2]) cube(size = [1.001, 4.011, 4], center = false);
translate([-2.499, 0.501, -2])
cylinder(h = 4, r1 = 0.2, r2 = 0.2, center = false, $fn = 12);
}
difference() {
translate([-0.489, -5, -2]) cube(size = [3.489, 5, 2], center = false);
translate([1.501, -2.999, -18.1])
cylinder(h = 19.6, r1 = 0.6, r2 = 0.6, center = false, $fn = 12);
}
difference() {
union() {
translate([1.467, 0, 1]) cube(size = [0.531, 0.99, 1], center = false);
translate([-1.999, 2.469, -2]) cube(size = [0.475, 1.542, 4], center = false);
}
union() {
translate([1.495, 1.003, 0])
cylinder(h = 2, r1 = 0.506, r2 = 0.506, center = false, $fn = 12);
translate([-1.525, 2.523, 1])
cylinder(h = 17.1, r1 = 0.466, r2 = 0.466, center = false, $fn = 12);
}
}
}
}
