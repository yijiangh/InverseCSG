intersection() {
translate([-6, -2.824, -3.529]) cube(size = [12, 5.648, 7.059], center = false);
union() {
difference() {
intersection() {
union() {
translate([-2.494, 0.647, -2.941]) cube(size = [20.594, 1.706, 1.882], center = false);
rotate([180, 90, -90])
translate([2.007, 4.061, -18.1])
cylinder(h = 19.983, r1 = 0.937, r2 = 0.937, center = false, $fn = 12);
}
union() {
translate([-18.1, 0.647, -2.941]) cube(size = [13.676, 1.706, 1.117], center = false);
translate([-4.424, 1.883, -2.941]) cube(size = [3.105, 16.217, 1.882], center = false);
}
}
union() {
rotate([180, 90, -90])
translate([1.883, 3.941, -18.1])
cylinder(h = 20.452, r1 = 0.588, r2 = 0.588, center = false, $fn = 12);
rotate([180, 90, -90])
translate([1.885, 1.319, -18.1])
cylinder(h = 20.452, r1 = 0.587, r2 = 0.587, center = false, $fn = 12);
translate([-1.906, 0.647, -1.824]) cube(size = [0.587, 1.706, 0.765], center = false);
rotate([180, 90, 180])
translate([1.73, 2.088, -4.424])
cylinder(h = 22.524, r1 = 0.076, r2 = 0.076, center = false, $fn = 12);
}
}
difference() {
union() {
difference() {
rotate([-7, 0, 0])
translate([4.529, -18.1, -18.1]) cube(size = [0.471, 16.072, 36.2], center = false);
rotate([-7, 0, 0])
translate([5, -1.414, -18.1]) cube(size = [13.1, 19.514, 36.2], center = false);
}
intersection() {
translate([4.529, -2.353, 1.353]) cube(size = [0.471, 20.453, 0.864], center = false);
rotate([29, 0, 0])
translate([4.529, -18.1, -18.1]) cube(size = [13.571, 18.34, 36.2], center = false);
}
rotate([180, 90, 180])
translate([-2.235, -1.058, 3.943])
cylinder(h = 14.157, r1 = 0.706, r2 = 0.706, center = false, $fn = 12);
difference() {
translate([-18.1, -18.1, -1.824]) cube(size = [23.1, 20.452, 4.041], center = false);
rotate([-7, 0, 0])
translate([-1.906, -1.414, -18.1]) cube(size = [6.906, 19.514, 36.2], center = false);
}
}
difference() {
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
intersection() {
difference() {
rotate([-7, 0, 0])
translate([4.529, -2.028, -18.1]) cube(size = [0.471, 20.128, 36.2], center = false);
rotate([180, 90, 180])
translate([-2.217, -1.063, 3.943])
cylinder(h = 14.157, r1 = 0.183, r2 = 0.183, center = false, $fn = 12);
}
union() {
rotate([-7, 0, 0])
translate([-1.906, -2.028, -18.1]) cube(size = [5.849, 20.128, 36.2], center = false);
rotate([-7, 0, 0])
translate([4.529, -18.1, -18.1]) cube(size = [0.471, 36.2, 36.2], center = false);
}
}
}
}
intersection() {
difference() {
union() {
rotate([29, 0, 0])
translate([-18.1, 0.239, -18.1]) cube(size = [14.087, 17.861, 36.2], center = false);
translate([-4.424, -18.1, -18.1]) cube(size = [0.411, 19.983, 15.629], center = false);
}
union() {
rotate([180, 90, -90])
translate([1.883, 3.941, -18.1])
cylinder(h = 36.2, r1 = 0.588, r2 = 0.588, center = false, $fn = 12);
translate([-4.013, 1.587, -18.1])
cylinder(h = 36.2, r1 = 0.412, r2 = 0.412, center = false, $fn = 12);
}
}
union() {
rotate([180, 90, -90])
translate([2.007, 4.061, -18.1])
cylinder(h = 20.452, r1 = 0.937, r2 = 0.937, center = false, $fn = 12);
translate([-4.013, 1.587, -2.471])
cylinder(h = 20.571, r1 = 0.412, r2 = 0.412, center = false, $fn = 12);
difference() {
rotate([-150, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [14.5, 18.1, 36.2], center = false);
translate([-4.424, -18.1, -2.941]) cube(size = [0.411, 36.2, 0.471], center = false);
}
}
rotate([-150, 0, 0])
translate([-18.1, -0.808, -18.1]) cube(size = [14.087, 0.808, 36.2], center = false);
rotate([180, 90, -90])
translate([2.007, 4.061, 0.647])
cylinder(h = 1.706, r1 = 0.937, r2 = 0.937, center = false, $fn = 12);
difference() {
rotate([-150, 0, 0])
translate([-18.1, -0.808, -18.1]) cube(size = [14.5, 0.808, 36.2], center = false);
translate([-18.1, -18.1, -1.824]) cube(size = [14.087, 20.452, 0.765], center = false);
}
}
intersection() {
translate([-4.013, 0.647, -2.941]) cube(size = [2.107, 1.706, 0.471], center = false);
union() {
rotate([29, 0, 0])
translate([-3.6, -18.1, -18.1]) cube(size = [21.7, 36.2, 36.2], center = false);
rotate([-150, 0, 0])
translate([-4.424, -18.1, -18.1]) cube(size = [0.824, 18.1, 36.2], center = false);
}
difference() {
translate([-4.013, 0.647, -2.941]) cube(size = [2.694, 1.706, 1.882], center = false);
translate([-4.013, 1.587, -2.941])
cylinder(h = 0.471, r1 = 0.412, r2 = 0.412, center = false, $fn = 12);
}
}
difference() {
intersection() {
union() {
rotate([180, 90, 180])
translate([-2.235, -1.058, -5])
cylinder(h = 0.471, r1 = 0.706, r2 = 0.706, center = false, $fn = 12);
rotate([29, 0, 0])
translate([-5, -18.1, -18.1]) cube(size = [0.471, 18.34, 36.2], center = false);
intersection() {
rotate([-150, 0, 0])
translate([-18.1, -0.808, -18.1]) cube(size = [36.2, 18.908, 36.2], center = false);
rotate([90, 0, 0])
translate([-5, 1.353, -18.1]) cube(size = [23.1, 0.864, 36.2], center = false);
}
}
difference() {
difference() {
rotate([-7, 0, 0])
translate([-18.1, -1.414, -18.1]) cube(size = [13.571, 19.514, 36.2], center = false);
rotate([90, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [13.571, 19.453, 36.2], center = false);
}
rotate([180, 90, 180])
translate([-2.217, -1.063, -18.1])
cylinder(h = 36.2, r1 = 0.183, r2 = 0.183, center = false, $fn = 12);
}
}
intersection() {
rotate([-7, 0, 0])
translate([-18.1, -2.028, -18.1]) cube(size = [13.1, 20.128, 36.2], center = false);
rotate([-150, 0, 0])
translate([-4.529, -0.808, -18.1]) cube(size = [22.629, 18.908, 36.2], center = false);
}
}
intersection() {
difference() {
translate([-18.1, -2.353, -2.941]) cube(size = [14.087, 3, 1.117], center = false);
rotate([180, 90, -90])
translate([1.883, 3.941, -18.1])
cylinder(h = 36.2, r1 = 0.588, r2 = 0.588, center = false, $fn = 12);
}
rotate([180, 90, -90])
translate([2.007, 4.061, -2.353])
cylinder(h = 20.453, r1 = 0.937, r2 = 0.937, center = false, $fn = 12);
difference() {
rotate([-7, 0, 0])
translate([-18.1, -2.028, -18.1]) cube(size = [14.087, 20.128, 36.2], center = false);
translate([-4.008, 0.647, -2.941])
cylinder(h = 21.041, r1 = 0.409, r2 = 0.409, center = false, $fn = 12);
}
}
difference() {
translate([-4.013, -2.353, -2.941]) cube(size = [2.694, 3, 0.471], center = false);
translate([-4.008, 0.647, -18.1])
cylinder(h = 15.629, r1 = 0.409, r2 = 0.409, center = false, $fn = 12);
}
intersection() {
union() {
difference() {
rotate([-150, 0, 0])
translate([-18.1, -0.808, -18.1]) cube(size = [36.2, 18.908, 36.2], center = false);
rotate([-7, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 16.686, 36.2], center = false);
}
difference() {
rotate([-7, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 16.686, 36.2], center = false);
rotate([180, 90, 180])
translate([-2.217, -1.063, -18.1])
cylinder(h = 36.2, r1 = 0.183, r2 = 0.183, center = false, $fn = 12);
}
}
union() {
rotate([180, 90, 180])
translate([-2.235, -1.058, -5])
cylinder(h = 0.471, r1 = 0.706, r2 = 0.706, center = false, $fn = 12);
rotate([90, 0, 0])
translate([-5, -1.824, -18.1]) cube(size = [23.1, 4.041, 36.2], center = false);
}
union() {
rotate([-7, 0, 0])
translate([-18.1, -1.414, -18.1]) cube(size = [13.1, 19.514, 36.2], center = false);
intersection() {
rotate([29, 0, 0])
translate([-18.1, 0.239, -18.1]) cube(size = [13.571, 17.861, 36.2], center = false);
rotate([90, 0, 0])
translate([-18.1, -1.824, -18.1]) cube(size = [36.2, 3.177, 36.2], center = false);
}
rotate([-7, 0, 0])
translate([-18.1, -2.028, -18.1]) cube(size = [13.571, 0.614, 36.2], center = false);
}
}
intersection() {
union() {
difference() {
translate([-1.906, -2.353, -2.941]) cube(size = [6.906, 4.706, 1.117], center = false);
translate([0, 0, -2.941])
cylinder(h = 0.471, r1 = 0.471, r2 = 0.471, center = false, $fn = 12);
}
rotate([29, 0, 0])
translate([4.529, 0.239, -18.1]) cube(size = [0.471, 17.861, 36.2], center = false);
}
union() {
translate([4.529, -18.1, -1.824]) cube(size = [0.471, 20.452, 4.041], center = false);
rotate([180, 90, -90])
translate([2.004, -4.059, -2.353])
cylinder(h = 4.706, r1 = 0.941, r2 = 0.941, center = false, $fn = 12);
rotate([-7, 0, 0])
translate([4.529, -18.1, -18.1]) cube(size = [0.471, 16.072, 36.2], center = false);
rotate([-7, 0, 0])
translate([-1.906, -2.028, -18.1]) cube(size = [5.849, 20.128, 36.2], center = false);
}
difference() {
difference() {
rotate([-150, 0, 0])
translate([-1.906, -0.808, -18.1]) cube(size = [20.006, 18.908, 36.2], center = false);
rotate([180, 90, 180])
translate([-2.217, -1.063, -18.1])
cylinder(h = 36.2, r1 = 0.183, r2 = 0.183, center = false, $fn = 12);
}
translate([0, 0.983, -2.941])
cylinder(h = 1.117, r1 = 0.189, r2 = 0.189, center = false, $fn = 12);
}
union() {
difference() {
translate([-18.1, -18.1, -18.1]) cube(size = [22.043, 36.2, 15.629], center = false);
translate([0, -0.983, -2.941])
cylinder(h = 21.041, r1 = 0.188, r2 = 0.188, center = false, $fn = 12);
}
difference() {
rotate([-7, 0, 0])
translate([3.943, -2.028, -18.1]) cube(size = [14.157, 20.128, 36.2], center = false);
rotate([180, 90, -90])
translate([1.884, -3.943, -2.353])
cylinder(h = 20.453, r1 = 0.586, r2 = 0.586, center = false, $fn = 12);
}
}
}
intersection() {
difference() {
difference() {
translate([-2.494, -1.411, -2.471]) cube(size = [1.176, 0.471, 1.412], center = false);
rotate([180, 90, -90])
translate([1.885, 1.319, -2.353])
cylinder(h = 1.413, r1 = 0.587, r2 = 0.587, center = false, $fn = 12);
}
union() {
translate([-1.906, -1.411, -1.824]) cube(size = [0.587, 0.471, 19.924], center = false);
rotate([180, 90, 180])
translate([1.733, -1.147, -2.494])
cylinder(h = 20.594, r1 = 0.076, r2 = 0.076, center = false, $fn = 12);
}
}
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
}
}
}
