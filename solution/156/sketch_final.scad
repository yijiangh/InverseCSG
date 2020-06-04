intersection() {
translate([-6, -3.201, -3.279]) cube(size = [12, 6.402, 6.558], center = false);
union() {
difference() {
difference() {
difference() {
difference() {
translate([-18.1, -2.667, -2.733]) cube(size = [17.635, 5.335, 5.465], center = false);
rotate([180, 90, -90])
translate([-0.682, 2.949, -2.667])
cylinder(h = 20.767, r1 = 1.639, r2 = 1.639, center = false, $fn = 12);
}
union() {
rotate([180, 90, -90])
translate([3.236, 2.872, -2.667])
cylinder(h = 5.335, r1 = 1.877, r2 = 1.877, center = false, $fn = 12);
translate([-18.1, -1.028, -2.733]) cube(size = [17.042, 2.056, 5.465], center = false);
}
}
rotate([-180, 90, -180])
translate([-0.665, -1.837, -18.1])
cylinder(h = 15.228, r1 = 0.213, r2 = 0.213, center = false, $fn = 12);
}
union() {
difference() {
translate([-18.1, -18.1, -2.733]) cube(size = [15.228, 36.2, 5.465], center = false);
rotate([180, 90, -90])
translate([-0.685, 2.962, -18.1])
cylinder(h = 36.2, r1 = 2.037, r2 = 2.037, center = false, $fn = 12);
}
rotate([180, 90, -180])
translate([-0.677, 1.868, -18.1])
cylinder(h = 15.228, r1 = 0.214, r2 = 0.214, center = false, $fn = 12);
}
}
difference() {
translate([-1.058, -2.667, -2.733]) cube(size = [4.919, 5.335, 0.651], center = false);
union() {
rotate([180, 0, 180])
translate([-2.293, 0.001, -18.1])
cylinder(h = 36.2, r1 = 1.559, r2 = 1.559, center = false, $fn = 12);
rotate([-180, 1, 129])
translate([-1.741, -1.011, -18.1])
cylinder(h = 36.2, r1 = 0.225, r2 = 0.225, center = false, $fn = 12);
}
}
intersection() {
union() {
difference() {
translate([3.861, -1.028, -2.733]) cube(size = [1.141, 3.696, 0.651], center = false);
rotate([180, 0, 180])
translate([-4.348, 2.024, -18.1])
cylinder(h = 20.833, r1 = 0.225, r2 = 0.225, center = false, $fn = 12);
}
rotate([-180, 2, -134])
translate([-1.454, -4.035, -18.1])
cylinder(h = 36.2, r1 = 1.153, r2 = 1.153, center = false, $fn = 12);
}
union() {
rotate([180, 2, 133])
translate([-1.425, 3.95, -18.1])
cylinder(h = 36.2, r1 = 1.253, r2 = 1.253, center = false, $fn = 12);
difference() {
translate([3.861, -2.667, -2.733]) cube(size = [1.141, 3.695, 0.651], center = false);
rotate([0, 0, 0])
translate([4.358, -2.021, -18.1])
cylinder(h = 36.2, r1 = 0.226, r2 = 0.226, center = false, $fn = 12);
}
}
}
}
}
