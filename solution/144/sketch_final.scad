intersection() {
translate([-6, -6, -3.6]) cube(size = [12, 12, 7.2], center = false);
union() {
translate([-5, -5, -3]) cube(size = [10, 10, 3], center = false);
difference() {
difference() {
union() {
translate([0.002, -0.012, -3])
cylinder(h = 5, r1 = 3.984, r2 = 3.984, center = false, $fn = 12);
translate([0.008, 0.003, 1.5])
cylinder(h = 16.6, r1 = 2.979, r2 = 2.979, center = false, $fn = 12);
}
difference() {
union() {
rotate([180, 0, 45])
translate([-0.5, -18.1, -18.1]) cube(size = [1, 36.2, 16.6], center = false);
translate([-0.5, -5, 1.5]) cube(size = [1, 10, 0.5], center = false);
}
translate([0.008, 0.003, 1.5])
cylinder(h = 16.6, r1 = 2.979, r2 = 2.979, center = false, $fn = 12);
}
}
union() {
difference() {
translate([-5, -0.5, 1.5]) cube(size = [23.1, 1, 0.5], center = false);
translate([0.004, 0.001, 1.5])
cylinder(h = 0.5, r1 = 1.986, r2 = 1.986, center = false, $fn = 12);
}
difference() {
union() {
rotate([180, 0, 45])
translate([-18.1, -0.5, -3]) cube(size = [36.2, 1, 1.5], center = false);
translate([0.008, 0.003, 0])
cylinder(h = 3, r1 = 2.979, r2 = 2.979, center = false, $fn = 12);
}
difference() {
translate([0.004, 0.001, -18.1])
cylinder(h = 21.1, r1 = 1.986, r2 = 1.986, center = false, $fn = 12);
translate([-0.002, -0.003, 0])
cylinder(h = 18.1, r1 = 1.001, r2 = 1.001, center = false, $fn = 12);
}
}
translate([0.008, 0.003, 3])
cylinder(h = 15.1, r1 = 2.979, r2 = 2.979, center = false, $fn = 12);
}
}
}
}
