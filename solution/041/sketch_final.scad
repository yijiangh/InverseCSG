intersection() {
translate([-3.557, -1.429, -6]) cube(size = [7.114, 2.857, 12], center = false);
union() {
difference() {
difference() {
union() {
difference() {
translate([-2.75, -1.19, 2.619]) cube(size = [20.85, 2.381, 2.381], center = false);
rotate([180, 90, -90])
translate([-4.165, 1.324, -18.1])
cylinder(h = 19.291, r1 = 0.95, r2 = 0.95, center = false, $fn = 12);
}
intersection() {
rotate([-180, 0, 45])
translate([-2.331, -2.331, -5]) cube(size = [20.431, 20.431, 23.1], center = false);
translate([-2.964, -18.1, -5]) cube(size = [0.691, 19.291, 23.1], center = false);
}
}
intersection() {
translate([-2.964, -18.1, -4.105]) cube(size = [21.064, 36.2, 9.105], center = false);
union() {
rotate([-180, 0, 45])
translate([-18.1, 1.843, -3.214]) cube(size = [36.2, 16.257, 5.833], center = false);
rotate([180, 90, -180])
translate([-4.107, 0.001, -18.1])
cylinder(h = 36.2, r1 = 0.306, r2 = 0.306, center = false, $fn = 12);
}
}
}
union() {
rotate([180, 90, -180])
translate([4.108, 0.001, -2.964])
cylinder(h = 21.064, r1 = 0.307, r2 = 0.307, center = false, $fn = 12);
translate([-2.273, 0.357, 2.619]) cube(size = [20.373, 17.743, 0.595], center = false);
difference() {
difference() {
translate([-2.273, -18.1, 3.214]) cube(size = [20.373, 36.2, 14.886], center = false);
rotate([-180, 0, 45])
translate([-18.1, -18.1, -4.096]) cube(size = [15.769, 19.943, 7.31], center = false);
}
difference() {
rotate([-180, 0, 45])
translate([-2.331, -18.1, -4.096]) cube(size = [20.431, 19.943, 0.881], center = false);
rotate([-180, 90, 179])
translate([-4.096, -0.026, -18.1])
cylinder(h = 36.2, r1 = 0.664, r2 = 0.664, center = false, $fn = 12);
}
}
translate([-1.323, -1.19, 3.214]) cube(size = [19.424, 19.291, 0.881], center = false);
}
}
intersection() {
difference() {
difference() {
union() {
translate([-3.202, 0.937, -4.105])
cylinder(h = 7.319, r1 = 6.167, r2 = 6.167, center = false, $fn = 12);
translate([-2.964, -18.1, -5]) cube(size = [0.691, 36.2, 0.895], center = false);
}
union() {
rotate([-180, 0, 45])
translate([-2.331, 1.843, 2.619]) cube(size = [20.431, 16.257, 0.595], center = false);
rotate([180, 90, -90])
translate([1.846, -2.19, 0.357])
cylinder(h = 17.743, r1 = 0.193, r2 = 0.193, center = false, $fn = 12);
}
}
union() {
rotate([180, 90, -90])
translate([-1.846, -2.191, -18.1])
cylinder(h = 36.2, r1 = 0.193, r2 = 0.193, center = false, $fn = 12);
rotate([180, 90, -90])
translate([-0.001, -0.345, -18.1])
cylinder(h = 36.2, r1 = 1.368, r2 = 1.368, center = false, $fn = 12);
rotate([180, 90, -90])
translate([4.175, 1.315, -1.19])
cylinder(h = 19.291, r1 = 0.961, r2 = 0.961, center = false, $fn = 12);
}
}
union() {
difference() {
translate([-2.75, -1.19, -5]) cube(size = [20.85, 2.381, 2.381], center = false);
rotate([-180, 0, 45])
translate([-2.331, -2.331, 3.214]) cube(size = [20.431, 20.431, 1.786], center = false);
}
difference() {
union() {
translate([-2.75, 0.357, -2.619]) cube(size = [20.85, 0.833, 6.715], center = false);
translate([-2.75, -1.19, -2.619]) cube(size = [0.477, 1.548, 5.238], center = false);
}
union() {
rotate([180, 90, -90])
translate([-1.845, 1.5, 0.357])
cylinder(h = 17.743, r1 = 0.178, r2 = 0.178, center = false, $fn = 12);
rotate([180, 90, -90])
translate([1.845, 1.5, -18.1])
cylinder(h = 19.291, r1 = 0.178, r2 = 0.178, center = false, $fn = 12);
}
}
difference() {
translate([-2.273, -1.19, -4.105]) cube(size = [0.95, 2.381, 1.486], center = false);
rotate([0, 90, 0])
translate([4.105, 0.002, -18.1])
cylinder(h = 36.2, r1 = 0.664, r2 = 0.664, center = false, $fn = 12);
}
}
}
}
}
