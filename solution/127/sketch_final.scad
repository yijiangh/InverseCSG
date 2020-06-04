intersection() {
translate([-6, -5.893, -3.589]) cube(size = [12, 11.786, 7.179], center = false);
union() {
difference() {
translate([-4.525, -4.44, -2.991])
cylinder(h = 2.054, r1 = 0.481, r2 = 0.481, center = false, $fn = 12);
union() {
rotate([0, 0, -24])
translate([-2.045, -18.1, -2.277]) cube(size = [5.612, 15.675, 5.268], center = false);
rotate([180, 0, 180])
translate([4.545, -4.166, -2.991])
cylinder(h = 21.091, r1 = 0.461, r2 = 0.461, center = false, $fn = 12);
}
}
intersection() {
rotate([0, 0, -24])
translate([-2.045, 4.436, -2.991]) cube(size = [20.145, 1.493, 5.982], center = false);
translate([4.143, 2.071, -2.991]) cube(size = [0.857, 16.029, 5.982], center = false);
}
intersection() {
union() {
rotate([0, 0, -24])
translate([-2.045, -18.1, -2.991]) cube(size = [5.612, 36.2, 0.714], center = false);
intersection() {
rotate([0, 0, 0])
translate([1.165, -6.961, -2.991])
cylinder(h = 21.091, r1 = 5.279, r2 = 5.279, center = false, $fn = 12);
translate([3.751, -3.661, -2.991]) cube(size = [1.249, 21.761, 5.982], center = false);
}
rotate([0, 0, -24])
translate([2.298, -18.1, -2.277]) cube(size = [1.268, 36.2, 1.339], center = false);
}
difference() {
intersection() {
rotate([0, 0, 0])
translate([1.675, -4.937, -18.1])
cylinder(h = 21.091, r1 = 3.637, r2 = 3.637, center = false, $fn = 12);
translate([-5, -3.661, -2.991]) cube(size = [10, 21.761, 21.091], center = false);
}
union() {
translate([-2.146, -0.806, -18.1])
cylinder(h = 15.823, r1 = 2.862, r2 = 2.862, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-3.097, -1.28, -2.991])
cylinder(h = 21.091, r1 = 0.723, r2 = 0.723, center = false, $fn = 12);
}
}
}
difference() {
intersection() {
union() {
rotate([0, 0, -24])
translate([-2.045, 0.939, -2.991]) cube(size = [20.145, 3.498, 0.714], center = false);
rotate([0, 0, -24])
translate([-0.426, -18.1, -2.991]) cube(size = [2.725, 22.537, 5.982], center = false);
translate([-1.348, 1.979, -18.1])
cylinder(h = 15.823, r1 = 0.094, r2 = 0.094, center = false, $fn = 12);
}
union() {
difference() {
rotate([0, 0, -24])
translate([-18.1, 0.939, -2.991]) cube(size = [20.398, 4.991, 21.091], center = false);
rotate([0, 0, 0])
translate([0.268, 1.622, -2.277])
cylinder(h = 20.377, r1 = 0.448, r2 = 0.448, center = false, $fn = 12);
}
difference() {
rotate([0, 0, -24])
translate([-0.426, -18.1, -2.991]) cube(size = [18.526, 19.687, 2.054], center = false);
rotate([0, 0, 0])
translate([1.165, -6.961, -18.1])
cylinder(h = 36.2, r1 = 5.279, r2 = 5.279, center = false, $fn = 12);
}
}
}
union() {
translate([-2.146, -0.806, -2.991])
cylinder(h = 0.714, r1 = 2.862, r2 = 2.862, center = false, $fn = 12);
rotate([0, 0, 0])
translate([3.117, -0.384, -2.991])
cylinder(h = 2.054, r1 = 0.739, r2 = 0.739, center = false, $fn = 12);
difference() {
rotate([0, 0, -24])
translate([-2.045, 0.939, -2.991]) cube(size = [20.145, 3.498, 5.982], center = false);
translate([-18.1, -18.1, -2.991]) cube(size = [21.851, 20.171, 2.054], center = false);
}
translate([0.178, 1.518, -2.991])
cylinder(h = 21.091, r1 = 0.222, r2 = 0.222, center = false, $fn = 12);
translate([-18.1, 2.071, -2.991]) cube(size = [20.473, 2.841, 0.714], center = false);
translate([-18.1, -18.1, -2.277]) cube(size = [20.473, 19.722, 5.268], center = false);
}
}
translate([4.544, 4.449, -0.937])
cylinder(h = 3.929, r1 = 0.462, r2 = 0.462, center = false, $fn = 12);
difference() {
union() {
intersection() {
union() {
rotate([-180, 0, 24])
translate([-18.1, -18.1, -2.991]) cube(size = [36.2, 23.108, 5.982], center = false);
translate([4.143, -18.1, -2.991]) cube(size = [13.957, 36.2, 5.982], center = false);
}
translate([-5, -4.625, -18.1]) cube(size = [10, 22.725, 21.091], center = false);
}
intersection() {
union() {
rotate([180, 0, 180])
translate([-4.56, -4.473, -2.991])
cylinder(h = 5.982, r1 = 0.437, r2 = 0.437, center = false, $fn = 12);
rotate([0, 0, -24])
translate([-2.045, -18.1, -2.991]) cube(size = [8.047, 15.675, 5.982], center = false);
}
union() {
translate([-18.1, -4.911, -2.991]) cube(size = [23.1, 1.25, 5.982], center = false);
rotate([0, 0, -24])
translate([-18.1, -18.1, -18.1]) cube(size = [24.101, 15.675, 15.109], center = false);
}
}
}
union() {
rotate([180, 0, 180])
translate([-0.177, -4.072, -18.1])
cylinder(h = 36.2, r1 = 0.223, r2 = 0.223, center = false, $fn = 12);
translate([-18.1, -3.661, -18.1]) cube(size = [18.816, 21.761, 21.091], center = false);
rotate([0, 0, -24])
translate([-2.045, -18.1, -0.937]) cube(size = [5.612, 36.2, 3.929], center = false);
translate([-0.993, 6.091, -18.1])
cylinder(h = 21.091, r1 = 4.363, r2 = 4.363, center = false, $fn = 12);
translate([2.373, -3.661, -2.991]) cube(size = [2.627, 21.761, 5.982], center = false);
translate([-18.1, -4.911, -0.937]) cube(size = [21.851, 23.011, 3.929], center = false);
translate([-5, -4.625, -2.277]) cube(size = [5.716, 22.725, 1.339], center = false);
translate([-4.461, -4.074, -2.991])
cylinder(h = 0.714, r1 = 0.222, r2 = 0.222, center = false, $fn = 12);
}
}
intersection() {
difference() {
difference() {
rotate([0, 0, 0])
translate([1.364, 3.837, -18.1])
cylinder(h = 21.091, r1 = 3.842, r2 = 3.842, center = false, $fn = 12);
rotate([-180, 0, 24])
translate([-18.1, -1.851, -18.1]) cube(size = [36.2, 19.951, 19.038], center = false);
}
union() {
translate([-0.993, 6.091, -18.1])
cylinder(h = 17.163, r1 = 4.363, r2 = 4.363, center = false, $fn = 12);
rotate([0, 0, -24])
translate([2.298, 5.531, -2.991]) cube(size = [15.802, 12.569, 2.054], center = false);
}
}
union() {
translate([3.751, -18.1, -2.991]) cube(size = [0.392, 23.012, 5.982], center = false);
difference() {
translate([2.373, -18.1, -2.991]) cube(size = [2.627, 23.012, 2.054], center = false);
rotate([0, 0, -24])
translate([-0.426, 5.531, -18.1]) cube(size = [18.526, 0.399, 17.163], center = false);
}
}
}
difference() {
difference() {
union() {
rotate([0, 0, -24])
translate([-18.1, 5.93, -0.937]) cube(size = [20.398, 12.17, 3.929], center = false);
rotate([0, 0, -24])
translate([-18.1, -18.1, -0.937]) cube(size = [20.398, 22.537, 3.929], center = false);
}
translate([-18.1, 4.912, -18.1]) cube(size = [36.2, 13.188, 36.2], center = false);
}
translate([-18.1, -18.1, -0.937]) cube(size = [21.851, 36.2, 19.038], center = false);
}
rotate([180, 0, 180])
translate([-3.528, 4.472, 0.938])
cylinder(h = 2.054, r1 = 0.436, r2 = 0.436, center = false, $fn = 12);
intersection() {
rotate([0, 0, -24])
translate([2.298, -18.1, -2.991]) cube(size = [3.703, 36.2, 2.054], center = false);
translate([-18.1, -4.911, -18.1]) cube(size = [22.243, 23.011, 17.163], center = false);
difference() {
rotate([0, 0, 0])
translate([1.165, -6.961, -2.991])
cylinder(h = 2.054, r1 = 5.279, r2 = 5.279, center = false, $fn = 12);
rotate([0, 0, 0])
translate([0.264, -4.171, -2.277])
cylinder(h = 20.377, r1 = 0.453, r2 = 0.453, center = false, $fn = 12);
}
}
intersection() {
rotate([0, 0, -24])
translate([2.298, 1.587, -0.937]) cube(size = [15.802, 2.849, 3.929], center = false);
union() {
translate([3.751, -18.1, -0.937]) cube(size = [1.249, 23.012, 19.038], center = false);
rotate([0, 0, -24])
translate([-2.045, -18.1, -2.991]) cube(size = [1.619, 19.039, 0.714], center = false);
}
rotate([0, 0, 0])
translate([1.364, 3.837, -2.991])
cylinder(h = 21.091, r1 = 3.842, r2 = 3.842, center = false, $fn = 12);
}
translate([4.544, 4.449, -2.991])
cylinder(h = 5.982, r1 = 0.462, r2 = 0.462, center = false, $fn = 12);
}
}
