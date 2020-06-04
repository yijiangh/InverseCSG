intersection() {
translate([-6, -5.998, -3.545]) cube(size = [12, 11.996, 7.091], center = false);
union() {
difference() {
union() {
translate([-3.068, -2.501, -2.955]) cube(size = [0.795, 0.91, 5.909], center = false);
difference() {
translate([-3.759, -2.501, 2.5]) cube(size = [0.691, 5.007, 0.455], center = false);
rotate([180, 90, -90])
translate([-2.373, 3.759, -18.1])
cylinder(h = 36.2, r1 = 0.355, r2 = 0.355, center = false, $fn = 12);
}
rotate([180, 0, 180])
translate([-0.003, 0.005, -2.955])
cylinder(h = 0.227, r1 = 4.71, r2 = 4.71, center = false, $fn = 12);
difference() {
translate([-3.068, -2.501, 2.5]) cube(size = [1.08, 5.007, 0.227], center = false);
rotate([180, 90, -90])
translate([-2.379, 1.922, -2.501])
cylinder(h = 5.007, r1 = 0.352, r2 = 0.352, center = false, $fn = 12);
}
translate([3.977, -0.001, -2.955])
cylinder(h = 5.682, r1 = 0.45, r2 = 0.45, center = false, $fn = 12);
translate([-1.988, -3.445, 2.5])
cylinder(h = 0.455, r1 = 0.452, r2 = 0.452, center = false, $fn = 12);
}
union() {
difference() {
rotate([180, 0, 180])
translate([-0.003, 0.005, -2.5])
cylinder(h = 20.6, r1 = 4.71, r2 = 4.71, center = false, $fn = 12);
rotate([180, 90, 180])
translate([2.501, -1.865, -18.1])
cylinder(h = 15.827, r1 = 0.219, r2 = 0.219, center = false, $fn = 12);
}
rotate([180, 0, 180])
translate([-0.003, 0.005, 2.955])
cylinder(h = 15.145, r1 = 4.71, r2 = 4.71, center = false, $fn = 12);
rotate([180, 90, 180])
translate([-2.489, 2.506, -18.1])
cylinder(h = 16.112, r1 = 0.236, r2 = 0.236, center = false, $fn = 12);
translate([-1.987, -3.444, -18.1])
cylinder(h = 20.827, r1 = 0.113, r2 = 0.113, center = false, $fn = 12);
rotate([0, 1, -19])
translate([-0.045, -0.001, -18.1])
cylinder(h = 36.2, r1 = 0.795, r2 = 0.795, center = false, $fn = 12);
translate([3.977, 0.001, -18.1])
cylinder(h = 20.827, r1 = 0.113, r2 = 0.113, center = false, $fn = 12);
rotate([180, 90, 180])
translate([-2.501, -2.501, -3.759])
cylinder(h = 21.859, r1 = 0.226, r2 = 0.226, center = false, $fn = 12);
}
}
difference() {
union() {
translate([-3.409, -2.273, -2.955]) cube(size = [1.136, 4.545, 5.682], center = false);
translate([-1.988, -2.273, 2.727]) cube(size = [20.088, 0.511, 0.227], center = false);
intersection() {
difference() {
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
translate([-1.988, -2.273, -18.1]) cube(size = [20.088, 3.864, 15.145], center = false);
}
difference() {
translate([-0.016, -0.01, 1.591])
cylinder(h = 1.364, r1 = 5.012, r2 = 5.012, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-0.003, 0.005, -18.1])
cylinder(h = 16.509, r1 = 4.71, r2 = 4.71, center = false, $fn = 12);
}
}
translate([-1.987, 3.445, 2.5])
cylinder(h = 15.6, r1 = 0.453, r2 = 0.453, center = false, $fn = 12);
}
union() {
translate([-1.989, 3.444, 2.5])
cylinder(h = 0.227, r1 = 0.113, r2 = 0.113, center = false, $fn = 12);
translate([-3.759, -1.591, -2.955]) cube(size = [1.487, 3.182, 4.659], center = false);
difference() {
union() {
translate([-3.759, 2.273, 1.591]) cube(size = [1.032, 0.233, 1.136], center = false);
translate([-3.068, -1.761, -2.955]) cube(size = [0.341, 3.523, 4.773], center = false);
}
rotate([180, 90, 180])
translate([2.5, 1.879, -3.068])
cylinder(h = 0.341, r1 = 0.23, r2 = 0.23, center = false, $fn = 12);
}
difference() {
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
translate([0.028, 0.016, -18.1])
cylinder(h = 21.055, r1 = 5.03, r2 = 5.03, center = false, $fn = 12);
}
}
}
}
}
