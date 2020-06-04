intersection() {
translate([-6, -1.405, -2.842]) cube(size = [12, 2.811, 5.684], center = false);
union() {
difference() {
difference() {
rotate([-90, -30, 0])
translate([-1.004, -0.48, -1.171]) cube(size = [19.104, 3.368, 2.342], center = false);
translate([-5, -1.171, -18.1]) cube(size = [23.1, 0.842, 36.2], center = false);
}
union() {
translate([-0.091, -0.25, -2.368])
cylinder(h = 20.468, r1 = 0.395, r2 = 0.395, center = false, $fn = 12);
rotate([90, 30, 0])
translate([-1.004, -18.1, -1.171]) cube(size = [19.104, 36.2, 1.5], center = false);
}
}
difference() {
difference() {
translate([-5, -1.171, -2.368]) cube(size = [5.724, 2.342, 4.737], center = false);
translate([-0.091, -0.25, -2.368])
cylinder(h = 4.737, r1 = 0.395, r2 = 0.395, center = false, $fn = 12);
}
intersection() {
rotate([90, 30, 0])
translate([-18.1, -18.1, -1.171]) cube(size = [17.096, 36.2, 2.342], center = false);
translate([-18.1, -1.171, -1.263]) cube(size = [18.824, 2.342, 2.526], center = false);
}
}
difference() {
union() {
difference() {
translate([-5, -1.171, -2.368]) cube(size = [10, 2.342, 4.737], center = false);
rotate([-90, -30, 0])
translate([-1.004, -0.48, -18.1]) cube(size = [19.104, 3.368, 19.271], center = false);
}
intersection() {
rotate([90, 30, 0])
translate([-1.004, 2.888, 0.539]) cube(size = [19.104, 15.212, 0.632], center = false);
translate([0.724, -1.171, -1.263]) cube(size = [4.276, 0.632, 3.632], center = false);
}
translate([0.724, -0.539, -2.368]) cube(size = [4.276, 1.711, 1.105], center = false);
}
union() {
rotate([180, 90, -90])
translate([-1.052, 4.263, -18.1])
cylinder(h = 18.508, r1 = 0.157, r2 = 0.157, center = false, $fn = 12);
intersection() {
translate([-5, -1.171, -18.1]) cube(size = [5.724, 2.342, 19.363], center = false);
rotate([180, 90, -90])
translate([0, 2.619, -18.1])
cylinder(h = 19.271, r1 = 0.658, r2 = 0.658, center = false, $fn = 12);
}
rotate([180, 90, -90])
translate([1.052, 4.263, -18.1])
cylinder(h = 18.508, r1 = 0.157, r2 = 0.157, center = false, $fn = 12);
intersection() {
union() {
translate([0.724, -1.171, -2.368]) cube(size = [4.276, 0.632, 4.737], center = false);
rotate([90, 30, 0])
translate([-3.531, -18.1, -18.1]) cube(size = [21.631, 36.2, 19.271], center = false);
}
union() {
translate([-0.091, -0.25, -18.1])
cylinder(h = 36.2, r1 = 0.395, r2 = 0.395, center = false, $fn = 12);
rotate([-90, -30, 0])
translate([-3.531, -18.1, -1.171]) cube(size = [2.526, 20.988, 0.842], center = false);
}
}
}
}
intersection() {
union() {
translate([0.724, -1.171, -2.368]) cube(size = [4.276, 2.342, 3.632], center = false);
rotate([-90, -30, 0])
translate([-18.1, -18.1, -1.171]) cube(size = [17.096, 17.62, 1.579], center = false);
}
union() {
translate([4.092, -18.1, -1.263]) cube(size = [0.908, 17.56, 19.363], center = false);
rotate([90, 30, 0])
translate([-1.004, -18.1, -1.171]) cube(size = [19.104, 17.62, 2.342], center = false);
}
}
intersection() {
difference() {
rotate([90, 30, 0])
translate([-3.531, -0.48, -18.1]) cube(size = [21.631, 18.58, 19.271], center = false);
rotate([180, 90, -90])
translate([0.001, -2.406, -1.171])
cylinder(h = 2.342, r1 = 1.247, r2 = 1.247, center = false, $fn = 12);
}
union() {
translate([0.724, -0.539, -2.368]) cube(size = [4.276, 1.711, 4.737], center = false);
rotate([-90, -30, 0])
translate([-1.004, -18.1, -18.1]) cube(size = [19.104, 17.62, 16.929], center = false);
}
}
}
}
