intersection() {
translate([-5.326, -5.326, -6]) cube(size = [10.652, 10.652, 12], center = false);
union() {
intersection() {
union() {
difference() {
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
rotate([-180, 0, 7])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 18.101, 23.1], center = false);
}
intersection() {
rotate([-180, 0, 25])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 19.278, 23.1], center = false);
rotate([-180, 0, 5])
translate([-18.1, -1.177, -18.1]) cube(size = [36.2, 19.278, 36.2], center = false);
}
}
union() {
intersection() {
rotate([-180, 0, 22])
translate([-18.1, 0, -18.1]) cube(size = [36.2, 18.1, 36.2], center = false);
translate([0, -0.001, -5])
cylinder(h = 3.838, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
}
rotate([-180, 0, 7])
translate([-18.1, 0.001, 1.162]) cube(size = [36.2, 18.099, 3.838], center = false);
}
union() {
difference() {
translate([0, -0.001, -18.1])
cylinder(h = 13.1, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
}
intersection() {
translate([-0.014, 0.024, -5])
cylinder(h = 3.838, r1 = 3.562, r2 = 3.562, center = false, $fn = 12);
translate([0, -0.001, -18.1])
cylinder(h = 36.2, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
}
difference() {
translate([0, -0.001, -18.1])
cylinder(h = 16.938, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
rotate([-180, 0, 7])
translate([-18.1, 0.001, -18.1]) cube(size = [36.2, 18.099, 36.2], center = false);
}
}
}
intersection() {
difference() {
difference() {
translate([0, -0.001, -5])
cylinder(h = 3.838, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
translate([5.775, 1.548, -18.1])
cylinder(h = 16.938, r1 = 4.744, r2 = 4.744, center = false, $fn = 12);
}
difference() {
rotate([0, 0, -8])
translate([-18.1, -0.001, -5]) cube(size = [18.1, 18.101, 3.838], center = false);
rotate([0, 0, -25])
translate([-18.1, -1.172, -5]) cube(size = [16.924, 19.272, 3.838], center = false);
}
}
difference() {
union() {
difference() {
translate([-9.487, -0.001, -5])
cylinder(h = 3.838, r1 = 8.765, r2 = 8.765, center = false, $fn = 12);
translate([-8.309, -4.804, -5])
cylinder(h = 3.838, r1 = 8.869, r2 = 8.869, center = false, $fn = 12);
}
rotate([0, 0, -22])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 18.1, 16.938], center = false);
rotate([0, 0, -25])
translate([-1.176, -1.172, -18.1]) cube(size = [19.276, 19.272, 16.938], center = false);
}
union() {
intersection() {
rotate([-180, 0, 38])
translate([0, -18.1, -18.1]) cube(size = [18.1, 36.2, 23.1], center = false);
translate([-9.487, -0.001, -5])
cylinder(h = 23.1, r1 = 8.765, r2 = 8.765, center = false, $fn = 12);
}
intersection() {
rotate([0, 0, -35])
translate([-18.1, 1.178, -5]) cube(size = [36.2, 16.922, 23.1], center = false);
rotate([-180, 0, 5])
translate([-18.1, -18.1, 1.162]) cube(size = [16.923, 36.2, 3.838], center = false);
}
}
}
union() {
intersection() {
rotate([0, 0, -5])
translate([-18.1, -18.1, -18.1]) cube(size = [19.277, 36.2, 16.938], center = false);
rotate([-180, 0, 35])
translate([-1.179, -18.1, 1.162]) cube(size = [19.279, 36.2, 3.838], center = false);
}
intersection() {
rotate([0, 0, -8])
translate([-18.1, -0.001, -18.1]) cube(size = [18.1, 18.101, 36.2], center = false);
rotate([0, 0, -5])
translate([-18.1, -18.1, -5]) cube(size = [19.277, 19.278, 23.1], center = false);
}
}
}
translate([-0.027, -0.019, -5])
cylinder(h = 3.838, r1 = 3.518, r2 = 3.518, center = false, $fn = 12);
intersection() {
rotate([0, 0, -38])
translate([0, -18.1, -5]) cube(size = [18.1, 36.2, 3.838], center = false);
difference() {
translate([0, -0.001, -5])
cylinder(h = 3.838, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
union() {
rotate([0, 0, -35])
translate([1.179, -18.1, -18.1]) cube(size = [16.921, 36.2, 36.2], center = false);
rotate([-180, 0, 35])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 16.922, 36.2], center = false);
rotate([-180, 0, 37])
translate([-18.1, 0.001, 1.162]) cube(size = [36.2, 18.099, 3.838], center = false);
}
}
}
intersection() {
difference() {
difference() {
rotate([0, 0, -25])
translate([-18.1, -18.1, -5]) cube(size = [19.274, 19.277, 3.838], center = false);
rotate([0, 0, -5])
translate([-18.1, -18.1, -18.1]) cube(size = [16.923, 36.2, 36.2], center = false);
}
union() {
translate([-9.487, -0.001, -18.1])
cylinder(h = 16.938, r1 = 8.765, r2 = 8.765, center = false, $fn = 12);
rotate([0, 0, -8])
translate([0, -18.1, -5]) cube(size = [18.1, 36.2, 23.1], center = false);
}
}
translate([0, -0.001, -5])
cylinder(h = 23.1, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
}
intersection() {
rotate([0, 0, -22])
translate([-18.1, 0, -18.1]) cube(size = [36.2, 18.1, 36.2], center = false);
difference() {
difference() {
translate([0, -0.001, -5])
cylinder(h = 3.838, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
rotate([0, 0, -25])
translate([-18.1, 1.177, -18.1]) cube(size = [36.2, 16.923, 36.2], center = false);
}
difference() {
rotate([0, 0, -35])
translate([-18.1, -1.178, -5]) cube(size = [36.2, 19.278, 3.838], center = false);
rotate([-180, 0, 5])
translate([1.177, -18.1, 1.162]) cube(size = [16.923, 36.2, 16.938], center = false);
}
}
rotate([0, 0, -5])
translate([-18.1, -1.177, -5]) cube(size = [36.2, 19.278, 23.1], center = false);
}
difference() {
translate([0.001, 0, -1.162])
cylinder(h = 6.162, r1 = 3.015, r2 = 3.015, center = false, $fn = 12);
translate([-1.035, -18.1, 0.96]) cube(size = [2.07, 36.2, 17.14], center = false);
}
difference() {
translate([0, -0.001, -5])
cylinder(h = 3.838, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
difference() {
union() {
rotate([-180, 0, 5])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 19.278, 23.1], center = false);
intersection() {
translate([0, -0.001, -18.1])
cylinder(h = 36.2, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
rotate([-180, 0, 35])
translate([-18.1, 1.178, -18.1]) cube(size = [36.2, 16.922, 36.2], center = false);
}
rotate([0, 0, -38])
translate([0, -18.1, -5]) cube(size = [18.1, 36.2, 23.1], center = false);
rotate([0, 0, -35])
translate([-18.1, -18.1, -18.1]) cube(size = [16.921, 36.2, 36.2], center = false);
}
intersection() {
rotate([-180, 0, 22])
translate([-18.1, -18.1, 1.162]) cube(size = [36.2, 18.1, 3.838], center = false);
rotate([-180, 0, 7])
translate([-18.1, 0.001, -18.1]) cube(size = [36.2, 18.099, 36.2], center = false);
rotate([-180, 0, 7])
translate([-18.1, 0.001, -18.1]) cube(size = [36.2, 18.099, 23.1], center = false);
translate([0, -0.001, -18.1])
cylinder(h = 16.938, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
rotate([-180, 0, 25])
translate([-18.1, -1.177, -18.1]) cube(size = [36.2, 19.278, 36.2], center = false);
}
}
}
difference() {
intersection() {
difference() {
translate([0, -0.001, -5])
cylinder(h = 3.838, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
rotate([0, 0, -8])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 18.099, 36.2], center = false);
}
rotate([-180, 0, 25])
translate([-18.1, -18.1, 1.162]) cube(size = [19.276, 36.2, 3.838], center = false);
difference() {
rotate([-180, 0, 5])
translate([-1.177, -18.1, -18.1]) cube(size = [19.277, 36.2, 36.2], center = false);
translate([-9.487, -0.001, -5])
cylinder(h = 23.1, r1 = 8.765, r2 = 8.765, center = false, $fn = 12);
}
}
rotate([-180, 0, 8])
translate([0, -18.1, -18.1]) cube(size = [18.1, 36.2, 23.1], center = false);
}
translate([0.022, 0.069, -5])
cylinder(h = 3.838, r1 = 3.478, r2 = 3.478, center = false, $fn = 12);
difference() {
intersection() {
union() {
translate([-0.014, 0.024, -18.1])
cylinder(h = 16.938, r1 = 3.562, r2 = 3.562, center = false, $fn = 12);
rotate([-180, 0, 5])
translate([-18.1, -18.1, -18.1]) cube(size = [19.277, 36.2, 23.1], center = false);
difference() {
rotate([0, 0, -35])
translate([-18.1, -1.178, -18.1]) cube(size = [36.2, 19.278, 36.2], center = false);
translate([5.775, 1.548, -18.1])
cylinder(h = 16.938, r1 = 4.744, r2 = 4.744, center = false, $fn = 12);
}
}
union() {
rotate([-180, 0, 5])
translate([1.177, -18.1, 1.162]) cube(size = [16.923, 36.2, 3.838], center = false);
rotate([-180, 0, 22])
translate([-18.1, -18.1, 1.162]) cube(size = [18.099, 36.2, 3.838], center = false);
}
difference() {
translate([0, -0.001, -18.1])
cylinder(h = 36.2, r1 = 4.504, r2 = 4.504, center = false, $fn = 12);
translate([-9.487, -0.001, -18.1])
cylinder(h = 36.2, r1 = 8.765, r2 = 8.765, center = false, $fn = 12);
}
}
union() {
rotate([0, 0, -22])
translate([-18.1, 0, -18.1]) cube(size = [36.2, 18.1, 36.2], center = false);
difference() {
rotate([-180, 0, 35])
translate([1.179, -18.1, 1.162]) cube(size = [16.921, 36.2, 16.938], center = false);
translate([-0.014, 0.024, -5])
cylinder(h = 3.838, r1 = 3.562, r2 = 3.562, center = false, $fn = 12);
}
rotate([-180, 0, 25])
translate([-18.1, -18.1, -18.1]) cube(size = [16.934, 36.2, 36.2], center = false);
translate([-8.309, -4.804, -18.1])
cylinder(h = 16.938, r1 = 8.869, r2 = 8.869, center = false, $fn = 12);
}
}
}
}
