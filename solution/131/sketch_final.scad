intersection() {
union() {
intersection() {
translate([1.219, -4.718, -18.1]) cube(size = [2.644, 0.4, 23.1], center = false);
union() {
difference() {
difference() {
translate([1.219, -4.718, -5]) cube(size = [2.644, 0.4, 10], center = false);
translate([-18.1, -4.718, -3.87]) cube(size = [21.562, 3.04, 7.76], center = false);
}
union() {
rotate([180, 90, -90])
translate([-3.908, -1.219, -18.1])
cylinder(h = 36.2, r1 = 0.686, r2 = 0.686, center = false, $fn = 12);
rotate([180, 90, -90])
translate([3.911, -1.219, -4.718])
cylinder(h = 3.747, r1 = 0.684, r2 = 0.684, center = false, $fn = 12);
}
}
difference() {
translate([1.908, -4.718, -5]) cube(size = [1.555, 1.103, 8.89], center = false);
union() {
rotate([180, 90, -90])
translate([2.995, -2.663, -4.718])
cylinder(h = 1.103, r1 = 0.399, r2 = 0.399, center = false, $fn = 12);
rotate([180, 90, -90])
translate([-2.804, -2.665, -18.1])
cylinder(h = 36.2, r1 = 0.399, r2 = 0.399, center = false, $fn = 12);
}
}
}
}
intersection() {
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 36.2], center = false);
difference() {
difference() {
rotate([180, 90, -90])
translate([4.641, -0.138, 1.707])
cylinder(h = 1.242, r1 = 2.314, r2 = 2.314, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-5.191, -1.766, -18.1])
cylinder(h = 36.2, r1 = 8.653, r2 = 8.653, center = false, $fn = 12);
}
translate([-3.462, 1.707, -4.6]) cube(size = [4.681, 1.242, 0.73], center = false);
}
}
difference() {
union() {
translate([-3.052, -2.88, 4.6])
cylinder(h = 0.4, r1 = 1.156, r2 = 1.156, center = false, $fn = 12);
translate([-3.052, -2.88, -5])
cylinder(h = 9.6, r1 = 1.156, r2 = 1.156, center = false, $fn = 12);
translate([-3.862, -4.718, 4.6]) cube(size = [0.4, 6.425, 0.4], center = false);
difference() {
union() {
translate([3.117, -2.886, -5])
cylinder(h = 0.4, r1 = 1.096, r2 = 1.096, center = false, $fn = 12);
translate([-3.862, -4.318, -5]) cube(size = [1.955, 3.347, 10], center = false);
}
union() {
rotate([180, 90, -90])
translate([4.641, -0.138, -2.27])
cylinder(h = 20.37, r1 = 2.314, r2 = 2.314, center = false, $fn = 12);
translate([1.219, -4.318, -5]) cube(size = [16.881, 2.048, 0.4], center = false);
}
}
}
union() {
translate([-3.113, -2.883, -4.6])
cylinder(h = 22.7, r1 = 0.899, r2 = 0.899, center = false, $fn = 12);
translate([-3.462, -4.718, -4.6]) cube(size = [4.681, 3.747, 9.2], center = false);
translate([-3.462, -4.318, -3.87]) cube(size = [1.555, 6.025, 21.97], center = false);
rotate([180, 90, 180])
translate([3.87, -0.946, -18.1])
cylinder(h = 19.319, r1 = 0.742, r2 = 0.742, center = false, $fn = 12);
translate([-3.862, -1.678, -3.87]) cube(size = [1.955, 3.385, 7.76], center = false);
rotate([0, 0, 0])
translate([-3.113, -2.886, -18.1])
cylinder(h = 36.2, r1 = 0.5, r2 = 0.5, center = false, $fn = 12);
rotate([180, 90, 180])
translate([-3.895, -0.971, -18.1])
cylinder(h = 14.637, r1 = 0.708, r2 = 0.708, center = false, $fn = 12);
}
}
difference() {
union() {
translate([-3.862, 2.413, -3.87]) cube(size = [0.4, 1.555, 8.87], center = false);
difference() {
rotate([180, 0, 180])
translate([3.114, 3.619, -5])
cylinder(h = 8.87, r1 = 1.096, r2 = 1.096, center = false, $fn = 12);
translate([-3.462, 1.707, -3.87]) cube(size = [1.555, 2.26, 21.97], center = false);
}
}
union() {
translate([-3.462, 1.707, 5]) cube(size = [6.925, 16.393, 13.1], center = false);
translate([-3.114, 3.62, -18.1])
cylinder(h = 23.1, r1 = 0.899, r2 = 0.899, center = false, $fn = 12);
translate([3.113, 3.618, -18.1])
cylinder(h = 23.1, r1 = 1.1, r2 = 1.1, center = false, $fn = 12);
}
}
difference() {
difference() {
union() {
translate([1.908, -4.318, -5]) cube(size = [1.955, 6.025, 9.6], center = false);
translate([3.117, -2.886, -4.6])
cylinder(h = 9.6, r1 = 1.096, r2 = 1.096, center = false, $fn = 12);
difference() {
translate([1.219, -4.318, -4.6]) cube(size = [2.644, 6.025, 9.6], center = false);
rotate([180, 90, -90])
translate([3.911, -1.219, -4.318])
cylinder(h = 6.025, r1 = 0.684, r2 = 0.684, center = false, $fn = 12);
}
}
union() {
rotate([180, 0, 180])
translate([-3.111, -2.884, -18.1])
cylinder(h = 36.2, r1 = 0.9, r2 = 0.9, center = false, $fn = 12);
translate([1.219, -0.971, -4.6]) cube(size = [2.644, 2.678, 9.2], center = false);
rotate([180, 90, 180])
translate([3.87, -0.946, 3.462])
cylinder(h = 14.637, r1 = 0.742, r2 = 0.742, center = false, $fn = 12);
rotate([180, 90, -90])
translate([4.641, -0.138, -3.614])
cylinder(h = 5.322, r1 = 2.314, r2 = 2.314, center = false, $fn = 12);
}
}
intersection() {
union() {
difference() {
translate([-18.1, -4.318, -3.87]) cube(size = [21.962, 6.025, 8.87], center = false);
translate([1.219, -3.614, -3.87]) cube(size = [2.644, 1.937, 8.47], center = false);
}
rotate([-180, 90, 180])
translate([3.895, -3.614, 1.219])
cylinder(h = 2.244, r1 = 0.706, r2 = 0.706, center = false, $fn = 12);
translate([1.219, -3.614, -4.6]) cube(size = [2.244, 21.714, 9.2], center = false);
}
union() {
translate([-18.1, -3.614, -18.1]) cube(size = [36.2, 21.714, 21.99], center = false);
translate([-18.1, -4.718, -18.1]) cube(size = [21.562, 22.817, 23.1], center = false);
rotate([180, 90, 180])
translate([-3.895, -0.971, -18.1])
cylinder(h = 36.2, r1 = 0.708, r2 = 0.708, center = false, $fn = 12);
}
}
}
intersection() {
difference() {
difference() {
translate([-3.862, -18.1, -5]) cube(size = [2.651, 17.129, 9.6], center = false);
rotate([-180, 90, 180])
translate([3.895, -3.614, -3.462])
cylinder(h = 21.562, r1 = 0.706, r2 = 0.706, center = false, $fn = 12);
}
union() {
rotate([180, 90, -90])
translate([3.911, 1.212, -18.1])
cylinder(h = 14.486, r1 = 0.688, r2 = 0.688, center = false, $fn = 12);
translate([-3.113, -2.883, -4.6])
cylinder(h = 0.73, r1 = 0.899, r2 = 0.899, center = false, $fn = 12);
}
}
union() {
difference() {
translate([-3.862, -4.718, 3.89]) cube(size = [2.651, 0.4, 1.11], center = false);
rotate([180, 90, -90])
translate([-3.906, 1.21, -18.1])
cylinder(h = 36.2, r1 = 0.695, r2 = 0.695, center = false, $fn = 12);
}
difference() {
translate([-3.862, -4.718, -5]) cube(size = [21.962, 1.103, 8.89], center = false);
translate([-3.862, -4.718, -3.87]) cube(size = [2.651, 3.04, 7.76], center = false);
}
}
}
intersection() {
difference() {
translate([-3.462, 3.968, 3.89]) cube(size = [4.681, 14.132, 0.71], center = false);
union() {
rotate([180, 90, -90])
translate([-3.906, 1.21, -18.1])
cylinder(h = 22.468, r1 = 0.695, r2 = 0.695, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-5.191, -1.766, -4.6])
cylinder(h = 0.71, r1 = 8.653, r2 = 8.653, center = false, $fn = 12);
}
}
union() {
translate([-1.908, 3.968, -3.87]) cube(size = [3.127, 0.4, 8.47], center = false);
rotate([180, 0, 180])
translate([3.114, 3.619, -5])
cylinder(h = 0.4, r1 = 1.096, r2 = 1.096, center = false, $fn = 12);
translate([-3.462, 2.413, 3.89]) cube(size = [7.325, 1.555, 0.71], center = false);
}
}
difference() {
difference() {
difference() {
union() {
translate([-3.862, -0.971, -5]) cube(size = [7.725, 5.338, 1.13], center = false);
rotate([180, 0, 180])
translate([3.114, 3.619, 3.87])
cylinder(h = 1.13, r1 = 1.096, r2 = 1.096, center = false, $fn = 12);
}
rotate([180, 0, 180])
translate([-3.112, 3.615, 4.6])
cylinder(h = 13.5, r1 = 0.5, r2 = 0.5, center = false, $fn = 12);
}
union() {
translate([3.116, 3.62, -4.6])
cylinder(h = 22.7, r1 = 0.898, r2 = 0.898, center = false, $fn = 12);
rotate([180, 90, -90])
translate([3.911, 1.212, -0.971])
cylinder(h = 19.07, r1 = 0.688, r2 = 0.688, center = false, $fn = 12);
rotate([180, 90, 180])
translate([3.897, 1.706, -18.1])
cylinder(h = 36.2, r1 = 0.707, r2 = 0.707, center = false, $fn = 12);
}
}
union() {
rotate([0, 0, 0])
translate([-3.094, 3.614, -18.1])
cylinder(h = 13.5, r1 = 0.499, r2 = 0.499, center = false, $fn = 12);
translate([-3.862, -0.971, -4.6]) cube(size = [7.325, 2.678, 22.7], center = false);
rotate([180, 90, -90])
translate([4.641, -0.138, -18.1])
cylinder(h = 21.049, r1 = 2.314, r2 = 2.314, center = false, $fn = 12);
difference() {
union() {
translate([-3.114, 3.62, -4.6])
cylinder(h = 22.7, r1 = 0.899, r2 = 0.899, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-5.191, -1.766, -18.1])
cylinder(h = 22.7, r1 = 8.653, r2 = 8.653, center = false, $fn = 12);
}
translate([3.462, 1.707, -4.6]) cube(size = [14.637, 16.393, 22.7], center = false);
}
translate([-3.462, 1.707, -4.6]) cube(size = [4.681, 2.26, 0.73], center = false);
}
}
difference() {
difference() {
translate([-3.862, -4.718, -5]) cube(size = [5.081, 0.4, 10], center = false);
rotate([180, 90, -90])
translate([-2.804, 2.664, -18.1])
cylinder(h = 36.2, r1 = 0.398, r2 = 0.398, center = false, $fn = 12);
}
union() {
translate([-1.908, -4.718, -4.6]) cube(size = [3.127, 0.4, 9.2], center = false);
rotate([180, 90, -90])
translate([2.995, 2.665, -4.718])
cylinder(h = 1.103, r1 = 0.399, r2 = 0.399, center = false, $fn = 12);
}
}
intersection() {
difference() {
translate([-3.462, -4.718, -5]) cube(size = [21.562, 2.448, 0.4], center = false);
rotate([0, 0, 0])
translate([3.112, -2.883, -5])
cylinder(h = 23.1, r1 = 0.5, r2 = 0.5, center = false, $fn = 12);
}
union() {
translate([3.117, -2.886, -5])
cylinder(h = 0.4, r1 = 1.096, r2 = 1.096, center = false, $fn = 12);
rotate([180, 90, -90])
translate([4.641, -0.138, -4.718])
cylinder(h = 2.448, r1 = 2.314, r2 = 2.314, center = false, $fn = 12);
}
}
difference() {
difference() {
difference() {
union() {
translate([-3.862, 1.707, -3.87]) cube(size = [7.725, 2.66, 8.87], center = false);
translate([3.113, 3.618, -3.87])
cylinder(h = 8.87, r1 = 1.1, r2 = 1.1, center = false, $fn = 12);
}
union() {
translate([-3.862, 1.707, -3.87]) cube(size = [0.4, 2.66, 7.76], center = false);
translate([-1.908, 1.707, -3.87]) cube(size = [3.127, 2.66, 8.47], center = false);
}
}
union() {
rotate([180, 90, 180])
translate([-3.89, 1.707, -3.862])
cylinder(h = 21.962, r1 = 0.711, r2 = 0.711, center = false, $fn = 12);
translate([3.116, 3.62, -18.1])
cylinder(h = 36.2, r1 = 0.898, r2 = 0.898, center = false, $fn = 12);
translate([-3.462, 1.707, -3.87]) cube(size = [6.925, 2.26, 21.97], center = false);
rotate([180, 0, 180])
translate([3.114, 3.619, -5])
cylinder(h = 8.87, r1 = 1.096, r2 = 1.096, center = false, $fn = 12);
}
}
union() {
rotate([180, 90, -90])
translate([-3.908, -1.219, 3.968])
cylinder(h = 14.132, r1 = 0.686, r2 = 0.686, center = false, $fn = 12);
difference() {
union() {
translate([1.219, 2.413, -18.1]) cube(size = [0.689, 1.955, 21.99], center = false);
translate([3.462, 1.707, -3.87]) cube(size = [0.4, 16.393, 8.47], center = false);
}
union() {
translate([3.462, 2.413, -3.87]) cube(size = [14.637, 15.687, 7.76], center = false);
rotate([180, 0, 180])
translate([-5.191, -1.766, -4.6])
cylinder(h = 0.71, r1 = 8.653, r2 = 8.653, center = false, $fn = 12);
}
}
}
}
intersection() {
union() {
difference() {
translate([3.113, 3.618, -5])
cylinder(h = 1.13, r1 = 1.1, r2 = 1.1, center = false, $fn = 12);
translate([1.219, 1.707, -18.1]) cube(size = [2.644, 2.66, 14.23], center = false);
}
translate([-3.462, -18.1, -4.6]) cube(size = [4.681, 22.468, 22.7], center = false);
translate([1.219, 3.968, -4.6]) cube(size = [2.644, 0.4, 0.73], center = false);
}
difference() {
union() {
translate([1.219, 1.707, -18.1]) cube(size = [16.881, 16.393, 36.2], center = false);
translate([-3.462, 4.368, -18.1]) cube(size = [4.681, 13.732, 14.23], center = false);
}
union() {
translate([3.116, 3.62, -4.6])
cylinder(h = 22.7, r1 = 0.898, r2 = 0.898, center = false, $fn = 12);
rotate([180, 90, -90])
translate([3.911, -1.219, 1.707])
cylinder(h = 2.66, r1 = 0.684, r2 = 0.684, center = false, $fn = 12);
}
}
}
}
translate([-5.055, -5.661, -6]) cube(size = [10.11, 11.322, 12], center = false);
}
