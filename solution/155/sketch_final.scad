intersection() {
translate([-4.187, -6, -1.322]) cube(size = [8.374, 12, 2.645], center = false);
union() {
intersection() {
rotate([0, 90, 0])
translate([1.035, -0.002, -18.1])
cylinder(h = 36.2, r1 = 1.416, r2 = 1.416, center = false, $fn = 12);
difference() {
intersection() {
rotate([90, 11, 0])
translate([-1.806, -18.1, -18.1]) cube(size = [19.906, 36.2, 36.2], center = false);
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
}
union() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [16.294, 36.2, 36.2], center = false);
translate([-0.418, -0.005, -18.1])
cylinder(h = 17.472, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
}
}
translate([-18.1, -18.1, -1.102]) cube(size = [36.2, 36.2, 0.284], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 17.085], center = false);
}
difference() {
difference() {
difference() {
union() {
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [19.219, 36.2, 19.866], center = false);
translate([-18.1, 4.242, -1.102]) cube(size = [19.219, 0.474, 2.204], center = false);
}
union() {
translate([-1.372, 4.653, -18.1])
cylinder(h = 36.2, r1 = 1.404, r2 = 1.404, center = false, $fn = 12);
rotate([0, 90, 0])
translate([1.035, -0.002, -18.1])
cylinder(h = 19.219, r1 = 1.416, r2 = 1.416, center = false, $fn = 12);
}
}
union() {
translate([-18.1, 4.242, -18.1]) cube(size = [36.2, 0.758, 16.998], center = false);
intersection() {
translate([-18.1, -18.1, -0.628]) cube(size = [19.219, 22.816, 18.728], center = false);
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 19.866], center = false);
}
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [16.294, 36.2, 36.2], center = false);
}
}
union() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
intersection() {
rotate([11, 0, 0])
translate([-18.1, -18.1, -1.015]) cube(size = [19.219, 36.2, 19.115], center = false);
translate([-18.1, -18.1, -1.102]) cube(size = [36.2, 22.342, 0.474], center = false);
}
translate([-18.1, 5, -18.1]) cube(size = [19.219, 13.1, 19.202], center = false);
translate([-18.1, -18.1, -18.1]) cube(size = [19.219, 22.816, 16.998], center = false);
}
}
difference() {
intersection() {
union() {
difference() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [15.711, 36.2, 36.2], center = false);
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
}
intersection() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 22.816, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
rotate([-180, 0, 45])
translate([0.238, -18.1, 0.628]) cube(size = [17.862, 36.2, 0.474], center = false);
}
}
union() {
translate([-3.489, -18.1, -1.102]) cube(size = [21.589, 22.816, 2.204], center = false);
intersection() {
rotate([-11, 0, 0])
translate([-18.1, -18.1, -0.461]) cube(size = [36.2, 36.2, 2.226], center = false);
translate([-3.489, 4.242, -1.102]) cube(size = [21.589, 0.758, 2.204], center = false);
}
}
}
union() {
translate([-1.372, 4.653, -18.1])
cylinder(h = 17.472, r1 = 1.404, r2 = 1.404, center = false, $fn = 12);
rotate([-11, 0, 0])
translate([-3.489, -18.1, -18.1]) cube(size = [21.589, 36.2, 17.639], center = false);
difference() {
translate([-18.1, 4.242, -0.628]) cube(size = [36.2, 0.474, 1.73], center = false);
rotate([-11, 0, 0])
translate([-18.1, -18.1, 1.766]) cube(size = [36.2, 36.2, 16.334], center = false);
}
translate([-18.1, -18.1, -0.628]) cube(size = [36.2, 22.342, 1.73], center = false);
rotate([-180, 0, 45])
translate([0.238, -18.1, 1.102]) cube(size = [17.862, 36.2, 16.998], center = false);
difference() {
rotate([-180, 0, 45])
translate([-18.1, -18.1, 0.628]) cube(size = [36.2, 36.2, 0.474], center = false);
rotate([11, 0, 0])
translate([-3.489, -18.1, -18.1]) cube(size = [21.589, 36.2, 17.085], center = false);
}
}
}
difference() {
difference() {
rotate([180, 0, 45])
translate([-18.1, -0.331, 0.818]) cube(size = [36.2, 18.431, 0.284], center = false);
translate([-2.437, -2.369, -18.1])
cylinder(h = 36.2, r1 = 0.142, r2 = 0.142, center = false, $fn = 12);
}
union() {
rotate([90, 11, 0])
translate([-1.806, -18.1, -18.1]) cube(size = [19.906, 36.2, 22.342], center = false);
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 15.776, 36.2], center = false);
}
}
intersection() {
difference() {
translate([-18.1, -18.1, -1.102]) cube(size = [36.2, 36.2, 0.474], center = false);
translate([2.794, 4.446, -1.102])
cylinder(h = 2.204, r1 = 1.69, r2 = 1.69, center = false, $fn = 12);
}
rotate([11, 0, 0])
translate([1.119, -18.1, -18.1]) cube(size = [16.981, 36.2, 17.085], center = false);
difference() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -4.242]) cube(size = [19.778, 36.2, 22.342], center = false);
translate([1.714, 1.779, -18.1])
cylinder(h = 36.2, r1 = 0.284, r2 = 0.284, center = false, $fn = 12);
}
}
intersection() {
difference() {
translate([-3.489, -4.716, -1.102]) cube(size = [21.589, 0.474, 2.204], center = false);
translate([-1.369, -4.666, -18.1])
cylinder(h = 17.472, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
}
union() {
translate([-3.489, -18.1, -1.102]) cube(size = [21.589, 13.858, 0.474], center = false);
rotate([11, 0, 0])
translate([-3.489, -18.1, 1.773]) cube(size = [21.589, 36.2, 16.327], center = false);
}
union() {
rotate([90, 11, 0])
translate([-18.1, -18.1, 4.242]) cube(size = [15.711, 36.2, 0.758], center = false);
translate([-1.369, -4.666, -18.1])
cylinder(h = 19.202, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
}
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 22.816], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 36.2], center = false);
}
difference() {
translate([-1.842, 1.777, -1.102])
cylinder(h = 0.284, r1 = 0.282, r2 = 0.282, center = false, $fn = 12);
translate([-1.842, 1.778, -1.102])
cylinder(h = 19.202, r1 = 0.142, r2 = 0.142, center = false, $fn = 12);
}
difference() {
intersection() {
union() {
translate([1.714, 1.779, -1.102])
cylinder(h = 0.284, r1 = 0.284, r2 = 0.284, center = false, $fn = 12);
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [20.641, 36.2, 17.639], center = false);
difference() {
rotate([90, 11, 0])
translate([1.679, -0.269, -18.1]) cube(size = [1.232, 18.369, 36.2], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [20.641, 20.424, 36.2], center = false);
}
}
union() {
rotate([180, 0, 45])
translate([0.238, -0.331, 0.628]) cube(size = [17.862, 18.431, 0.19], center = false);
difference() {
translate([1.714, 1.779, -1.102])
cylinder(h = 0.284, r1 = 0.284, r2 = 0.284, center = false, $fn = 12);
translate([1.712, 1.778, -1.102])
cylinder(h = 19.202, r1 = 0.141, r2 = 0.141, center = false, $fn = 12);
}
}
}
union() {
translate([2.305, 2.371, -0.818])
cylinder(h = 0.19, r1 = 0.282, r2 = 0.282, center = false, $fn = 12);
translate([2.794, 4.446, -18.1])
cylinder(h = 36.2, r1 = 1.69, r2 = 1.69, center = false, $fn = 12);
translate([2.305, 2.371, -1.102])
cylinder(h = 0.284, r1 = 0.282, r2 = 0.282, center = false, $fn = 12);
translate([1.714, 1.779, -0.818])
cylinder(h = 18.917, r1 = 0.284, r2 = 0.284, center = false, $fn = 12);
rotate([11, 0, 0])
translate([-18.1, -18.1, -1.015]) cube(size = [36.2, 20.424, 19.115], center = false);
translate([2.794, 4.446, -18.1])
cylinder(h = 17.282, r1 = 1.69, r2 = 1.69, center = false, $fn = 12);
rotate([180, 0, 45])
translate([-18.1, -0.331, 0.628]) cube(size = [18.338, 18.431, 0.19], center = false);
rotate([-11, 0, 0])
translate([2.541, -18.1, -18.1]) cube(size = [15.559, 36.2, 17.639], center = false);
}
}
difference() {
union() {
rotate([-180, 0, 0])
translate([2.541, -18.1, -18.1]) cube(size = [0.474, 20.875, 18.728], center = false);
intersection() {
rotate([-90, -5, 0])
translate([-18.1, -18.1, -2.775]) cube(size = [21.528, 36.2, 20.875], center = false);
rotate([-180, 0, 45])
translate([0.238, -18.1, 0.628]) cube(size = [17.862, 36.2, 0.474], center = false);
}
difference() {
intersection() {
rotate([-180, 0, 45])
translate([-0.331, -18.1, 0.628]) cube(size = [18.431, 36.2, 0.474], center = false);
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 19.539, 36.2], center = false);
}
union() {
rotate([-180, 0, 0])
translate([-18.1, 2.775, -1.102]) cube(size = [21.589, 15.325, 2.204], center = false);
rotate([-11, 0, 0])
translate([-18.1, -2.323, -18.1]) cube(size = [20.641, 20.424, 36.2], center = false);
}
}
}
union() {
intersection() {
rotate([-180, 0, 0])
translate([2.541, -18.1, -1.102]) cube(size = [0.474, 36.2, 1.73], center = false);
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 19.539, 20.875], center = false);
}
translate([2.305, -2.372, -18.1])
cylinder(h = 17.472, r1 = 0.281, r2 = 0.281, center = false, $fn = 12);
rotate([11, 0, 0])
translate([-18.1, -1.743, -18.1]) cube(size = [21.589, 19.843, 36.2], center = false);
rotate([-180, 0, 45])
translate([-18.1, -18.1, -18.1]) cube(size = [17.769, 36.2, 36.2], center = false);
rotate([-180, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [21.589, 36.2, 16.998], center = false);
rotate([-180, 0, 0])
translate([3.489, -18.1, -18.1]) cube(size = [14.611, 36.2, 36.2], center = false);
}
}
intersection() {
union() {
difference() {
rotate([180, 0, 45])
translate([-18.1, -18.1, -1.102]) cube(size = [17.769, 36.2, 1.919], center = false);
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 13.858, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
}
difference() {
translate([-18.1, -4.716, -1.102]) cube(size = [36.2, 22.816, 0.284], center = false);
union() {
translate([2.304, -2.37, -18.1])
cylinder(h = 36.2, r1 = 0.141, r2 = 0.141, center = false, $fn = 12);
translate([1.711, -1.779, -1.102])
cylinder(h = 2.204, r1 = 0.14, r2 = 0.14, center = false, $fn = 12);
}
}
}
difference() {
intersection() {
difference() {
rotate([180, 0, 45])
translate([-18.1, 0.238, 0.628]) cube(size = [18.338, 17.862, 0.474], center = false);
translate([2.794, -4.451, -1.102])
cylinder(h = 0.474, r1 = 1.694, r2 = 1.694, center = false, $fn = 12);
}
rotate([90, 11, 0])
translate([-1.806, -18.1, -18.1]) cube(size = [19.906, 36.2, 23.1], center = false);
}
union() {
translate([-0.418, -0.005, -1.102])
cylinder(h = 19.202, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
translate([-1.369, -4.666, -1.102])
cylinder(h = 0.474, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
translate([1.119, -18.1, -0.818]) cube(size = [16.981, 13.384, 0.19], center = false);
}
}
}
intersection() {
union() {
difference() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -4.242]) cube(size = [21.01, 36.2, 22.342], center = false);
rotate([180, 0, 45])
translate([0.238, -0.331, -18.1]) cube(size = [17.862, 18.431, 18.917], center = false);
}
difference() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -4.242]) cube(size = [21.01, 17.831, 22.342], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [20.641, 20.424, 17.085], center = false);
}
}
difference() {
union() {
rotate([90, 11, 0])
translate([1.679, -18.1, -4.242]) cube(size = [1.232, 36.2, 22.342], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [20.641, 20.424, 36.2], center = false);
}
union() {
translate([2.794, 4.446, -1.102])
cylinder(h = 19.202, r1 = 1.69, r2 = 1.69, center = false, $fn = 12);
translate([-0.418, -0.005, -18.1])
cylinder(h = 17.472, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
}
}
difference() {
union() {
translate([1.712, 1.778, -0.628])
cylinder(h = 18.728, r1 = 0.141, r2 = 0.141, center = false, $fn = 12);
difference() {
rotate([180, 0, 45])
translate([0.238, -18.1, 0.628]) cube(size = [17.862, 36.2, 0.474], center = false);
translate([3.011, -0.006, -18.1])
cylinder(h = 36.2, r1 = 1.402, r2 = 1.402, center = false, $fn = 12);
}
}
intersection() {
union() {
translate([2.305, 2.371, -18.1])
cylinder(h = 17.472, r1 = 0.282, r2 = 0.282, center = false, $fn = 12);
translate([1.714, 1.779, -18.1])
cylinder(h = 36.2, r1 = 0.284, r2 = 0.284, center = false, $fn = 12);
}
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 17.831, 36.2], center = false);
}
}
}
difference() {
difference() {
difference() {
union() {
rotate([-180, 0, 45])
translate([-0.331, -18.1, 0.628]) cube(size = [18.431, 36.2, 0.474], center = false);
rotate([-180, 0, 0])
translate([2.541, -18.1, -1.102]) cube(size = [0.948, 20.875, 2.204], center = false);
}
difference() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 20.875], center = false);
rotate([11, 0, 0])
translate([3.015, -18.1, -18.1]) cube(size = [0.474, 16.357, 36.2], center = false);
}
}
translate([2.794, -4.451, -18.1])
cylinder(h = 36.2, r1 = 1.694, r2 = 1.694, center = false, $fn = 12);
}
difference() {
union() {
rotate([-90, -5, 0])
translate([3.428, -18.1, -2.775]) cube(size = [14.672, 36.2, 20.875], center = false);
rotate([90, 11, 0])
translate([2.91, 1.439, -18.1]) cube(size = [15.19, 16.661, 20.875], center = false);
rotate([-180, 0, 45])
translate([0.238, -18.1, 0.628]) cube(size = [17.862, 36.2, 17.472], center = false);
}
rotate([180, 90, -90])
translate([-0.873, -3.142, -18.1])
cylinder(h = 36.2, r1 = 0.218, r2 = 0.218, center = false, $fn = 12);
}
}
intersection() {
difference() {
difference() {
rotate([-180, 0, 0])
translate([-18.1, -2.771, 0.628]) cube(size = [21.589, 20.871, 17.472], center = false);
translate([-0.418, -0.005, -18.1])
cylinder(h = 36.2, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
}
intersection() {
rotate([180, 0, 45])
translate([-18.1, -18.1, -1.102]) cube(size = [36.2, 36.2, 1.919], center = false);
translate([1.714, -1.779, -0.818])
cylinder(h = 0.19, r1 = 0.285, r2 = 0.285, center = false, $fn = 12);
}
}
union() {
difference() {
rotate([11, 0, 0])
translate([-18.1, -1.743, -18.1]) cube(size = [21.115, 19.843, 36.2], center = false);
rotate([180, 0, 45])
translate([-18.1, -18.1, 0.628]) cube(size = [36.2, 18.338, 0.474], center = false);
}
rotate([90, 11, 0])
translate([-18.1, 1.439, -2.771]) cube(size = [21.01, 16.661, 20.871], center = false);
difference() {
difference() {
rotate([180, 0, 45])
translate([-18.1, -18.1, 0.628]) cube(size = [36.2, 18.338, 17.472], center = false);
rotate([90, 11, 0])
translate([-18.1, -18.1, -2.771]) cube(size = [21.01, 19.539, 20.871], center = false);
}
difference() {
rotate([11, 0, 0])
translate([3.015, -1.743, -18.1]) cube(size = [0.474, 19.843, 36.2], center = false);
rotate([180, 90, -90])
translate([-0.873, -3.142, -18.1])
cylinder(h = 36.2, r1 = 0.218, r2 = 0.218, center = false, $fn = 12);
}
}
translate([2.305, 2.371, -18.1])
cylinder(h = 17.282, r1 = 0.282, r2 = 0.282, center = false, $fn = 12);
}
difference() {
difference() {
rotate([-180, 0, 0])
translate([-18.1, -18.1, -1.102]) cube(size = [21.115, 36.2, 2.204], center = false);
translate([3.011, -0.006, -1.102])
cylinder(h = 2.204, r1 = 1.402, r2 = 1.402, center = false, $fn = 12);
}
translate([2.304, 2.37, -18.1])
cylinder(h = 17.472, r1 = 0.141, r2 = 0.141, center = false, $fn = 12);
}
}
difference() {
intersection() {
difference() {
rotate([-180, 0, 0])
translate([2.541, -2.771, -1.102]) cube(size = [0.948, 20.871, 2.204], center = false);
rotate([90, 11, 0])
translate([2.91, 1.439, -18.1]) cube(size = [15.19, 16.661, 36.2], center = false);
}
difference() {
rotate([-90, -5, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [21.528, 36.2, 36.2], center = false);
rotate([0, 90, 0])
translate([1.035, -0.002, 2.541])
cylinder(h = 0.948, r1 = 1.416, r2 = 1.416, center = false, $fn = 12);
}
}
intersection() {
union() {
rotate([-180, 0, 0])
translate([2.541, -2.771, -18.1]) cube(size = [0.474, 20.871, 18.917], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [21.589, 16.357, 36.2], center = false);
}
union() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -2.771]) cube(size = [36.2, 19.539, 20.871], center = false);
rotate([11, 0, 0])
translate([2.541, -18.1, -18.1]) cube(size = [15.559, 16.357, 36.2], center = false);
}
}
}
intersection() {
difference() {
rotate([90, 11, 0])
translate([-1.806, -18.1, -5]) cube(size = [3.485, 36.2, 0.284], center = false);
difference() {
translate([-18.1, 4.242, -18.1]) cube(size = [19.219, 0.758, 16.998], center = false);
rotate([11, 0, 0])
translate([1.119, -18.1, -1.015]) cube(size = [16.981, 36.2, 19.115], center = false);
}
}
difference() {
union() {
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [19.219, 36.2, 19.866], center = false);
rotate([180, 90, 180])
translate([-0.888, 4.784, -18.1])
cylinder(h = 19.219, r1 = 0.207, r2 = 0.207, center = false, $fn = 12);
}
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 23.1, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
}
}
intersection() {
difference() {
difference() {
rotate([-180, 0, 45])
translate([-0.331, -18.1, 0.628]) cube(size = [0.568, 36.2, 0.474], center = false);
translate([-2.436, 2.373, -0.818])
cylinder(h = 18.917, r1 = 0.281, r2 = 0.281, center = false, $fn = 12);
}
union() {
rotate([0, 90, 0])
translate([1.035, -0.002, -18.1])
cylinder(h = 36.2, r1 = 1.416, r2 = 1.416, center = false, $fn = 12);
translate([-1.842, 1.777, -18.1])
cylinder(h = 36.2, r1 = 0.282, r2 = 0.282, center = false, $fn = 12);
}
}
union() {
rotate([-180, 0, 45])
translate([0.238, -18.1, 0.818]) cube(size = [17.862, 36.2, 17.282], center = false);
rotate([11, 0, 0])
translate([-18.1, 2.324, -18.1]) cube(size = [36.2, 15.776, 36.2], center = false);
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [15.711, 36.2, 36.2], center = false);
translate([-2.436, 2.373, -18.1])
cylinder(h = 36.2, r1 = 0.281, r2 = 0.281, center = false, $fn = 12);
intersection() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
rotate([-180, 0, 45])
translate([-18.1, -18.1, 0.818]) cube(size = [36.2, 36.2, 17.282], center = false);
}
rotate([-180, 0, 45])
translate([0.238, -18.1, 0.628]) cube(size = [17.862, 36.2, 0.474], center = false);
}
union() {
difference() {
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 17.639], center = false);
translate([-2.434, 2.37, -18.1])
cylinder(h = 17.282, r1 = 0.142, r2 = 0.142, center = false, $fn = 12);
}
difference() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
translate([-2.434, 2.37, -1.102])
cylinder(h = 19.202, r1 = 0.142, r2 = 0.142, center = false, $fn = 12);
}
}
}
difference() {
intersection() {
union() {
translate([-1.842, 1.778, -18.1])
cylinder(h = 16.998, r1 = 0.142, r2 = 0.142, center = false, $fn = 12);
intersection() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
translate([-18.1, -18.1, -0.818]) cube(size = [36.2, 36.2, 0.19], center = false);
}
}
union() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
translate([-18.1, -18.1, -0.628]) cube(size = [36.2, 36.2, 18.728], center = false);
}
difference() {
rotate([90, 11, 0])
translate([-1.806, -18.1, -18.1]) cube(size = [19.906, 36.2, 36.2], center = false);
translate([-0.418, -0.005, -18.1])
cylinder(h = 36.2, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
}
}
intersection() {
difference() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
union() {
rotate([0, 90, 0])
translate([1.035, -0.002, -18.1])
cylinder(h = 36.2, r1 = 1.416, r2 = 1.416, center = false, $fn = 12);
translate([-18.1, -18.1, -0.628]) cube(size = [36.2, 36.2, 18.728], center = false);
}
}
union() {
translate([-1.842, 1.777, -18.1])
cylinder(h = 17.472, r1 = 0.282, r2 = 0.282, center = false, $fn = 12);
rotate([11, 0, 0])
translate([-18.1, 1.744, -18.1]) cube(size = [36.2, 16.356, 17.085], center = false);
difference() {
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 17.639], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 19.844, 17.085], center = false);
}
}
}
}
difference() {
difference() {
rotate([180, 90, -90])
translate([1.054, 1.37, -18.1])
cylinder(h = 36.2, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
union() {
rotate([0, 90, 0])
translate([1.035, -0.002, -18.1])
cylinder(h = 36.2, r1 = 1.416, r2 = 1.416, center = false, $fn = 12);
rotate([-180, 0, 45])
translate([0.238, -18.1, 1.102]) cube(size = [17.862, 36.2, 16.998], center = false);
}
}
union() {
rotate([-180, 0, 45])
translate([-18.1, -18.1, -18.1]) cube(size = [18.338, 36.2, 36.2], center = false);
rotate([-11, 0, 0])
translate([-18.1, -18.1, -0.461]) cube(size = [36.2, 36.2, 18.561], center = false);
}
}
intersection() {
difference() {
rotate([-11, 0, 0])
translate([-18.1, -2.323, -18.1]) cube(size = [36.2, 20.424, 36.2], center = false);
translate([-2.437, -2.375, -1.102])
cylinder(h = 0.474, r1 = 0.279, r2 = 0.279, center = false, $fn = 12);
}
rotate([180, 0, 45])
translate([-18.1, -0.331, 0.628]) cube(size = [17.769, 0.569, 0.19], center = false);
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [15.711, 36.2, 36.2], center = false);
}
intersection() {
difference() {
union() {
translate([-1.369, -4.666, -18.1])
cylinder(h = 36.2, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
difference() {
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
rotate([90, 11, 0])
translate([-2.389, -18.1, 4.716]) cube(size = [20.489, 36.2, 13.384], center = false);
}
}
rotate([180, 90, -90])
translate([1.054, 1.37, -5])
cylinder(h = 0.284, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
}
union() {
intersection() {
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 19.873], center = false);
translate([-3.489, -5, -1.102]) cube(size = [21.589, 0.284, 2.204], center = false);
}
difference() {
rotate([180, 90, 180])
translate([-0.876, -4.772, -18.1])
cylinder(h = 36.2, r1 = 0.225, r2 = 0.225, center = false, $fn = 12);
rotate([90, 11, 0])
translate([-2.389, -18.1, 5]) cube(size = [20.489, 36.2, 13.1], center = false);
}
}
translate([-3.489, -5, -18.1]) cube(size = [21.589, 0.284, 19.202], center = false);
}
intersection() {
difference() {
difference() {
rotate([90, 11, 0])
translate([-1.806, -18.1, -18.1]) cube(size = [3.485, 36.2, 22.816], center = false);
rotate([180, 0, 45])
translate([-0.331, -18.1, -1.102]) cube(size = [18.431, 36.2, 1.73], center = false);
}
union() {
translate([2.794, -4.451, -0.818])
cylinder(h = 1.919, r1 = 1.694, r2 = 1.694, center = false, $fn = 12);
translate([1.714, -1.779, -0.818])
cylinder(h = 18.917, r1 = 0.285, r2 = 0.285, center = false, $fn = 12);
}
}
difference() {
difference() {
rotate([180, 0, 45])
translate([-18.1, -18.1, -1.102]) cube(size = [18.338, 36.2, 1.919], center = false);
rotate([11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [19.219, 36.2, 19.873], center = false);
}
translate([-18.1, -4.242, -0.628]) cube(size = [36.2, 22.342, 1.73], center = false);
}
}
difference() {
union() {
difference() {
rotate([90, 11, 0])
translate([-1.806, -18.1, 4.716]) cube(size = [3.485, 36.2, 0.284], center = false);
translate([-18.1, -5, -18.1]) cube(size = [19.219, 0.284, 16.998], center = false);
}
intersection() {
translate([-1.369, -4.666, -18.1])
cylinder(h = 16.998, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
translate([-18.1, -5, -18.1]) cube(size = [36.2, 0.284, 16.998], center = false);
}
}
union() {
rotate([180, 90, -90])
translate([1.054, 1.37, -5])
cylinder(h = 0.284, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
rotate([11, 0, 0])
translate([1.119, -18.1, -18.1]) cube(size = [16.981, 36.2, 36.2], center = false);
difference() {
rotate([11, 0, 0])
translate([-18.1, -18.1, 1.773]) cube(size = [19.219, 36.2, 16.327], center = false);
rotate([180, 90, 180])
translate([-0.876, -4.772, -18.1])
cylinder(h = 36.2, r1 = 0.225, r2 = 0.225, center = false, $fn = 12);
}
}
}
difference() {
difference() {
union() {
rotate([180, 90, 180])
translate([-0.888, 4.784, -3.489])
cylinder(h = 21.589, r1 = 0.207, r2 = 0.207, center = false, $fn = 12);
rotate([90, 11, 0])
translate([-2.389, -18.1, -4.716]) cube(size = [20.489, 36.2, 0.474], center = false);
difference() {
rotate([-11, 0, 0])
translate([-3.489, -18.1, -0.461]) cube(size = [21.589, 36.2, 2.226], center = false);
rotate([180, 90, -90])
translate([1.054, 1.37, 4.242])
cylinder(h = 0.758, r1 = 1.428, r2 = 1.428, center = false, $fn = 12);
}
}
union() {
difference() {
rotate([-11, 0, 0])
translate([-3.489, -18.1, -18.1]) cube(size = [21.589, 36.2, 19.866], center = false);
rotate([90, 11, 0])
translate([-2.389, -18.1, -5]) cube(size = [20.489, 36.2, 0.284], center = false);
}
difference() {
rotate([90, 11, 0])
translate([-2.389, -18.1, -5]) cube(size = [20.489, 36.2, 0.758], center = false);
translate([-1.372, 4.653, -0.628])
cylinder(h = 1.73, r1 = 1.404, r2 = 1.404, center = false, $fn = 12);
}
}
}
difference() {
rotate([11, 0, 0])
translate([-3.489, -18.1, -18.1]) cube(size = [21.589, 36.2, 17.085], center = false);
rotate([180, 90, 180])
translate([-0.888, 4.784, -3.489])
cylinder(h = 21.589, r1 = 0.207, r2 = 0.207, center = false, $fn = 12);
}
}
difference() {
intersection() {
rotate([-180, 0, 0])
translate([3.015, -2.771, -1.102]) cube(size = [0.474, 20.871, 1.73], center = false);
rotate([11, 0, 0])
translate([-18.1, -1.743, -18.1]) cube(size = [21.589, 19.843, 36.2], center = false);
rotate([180, 90, -90])
translate([-0.873, -3.142, -18.1])
cylinder(h = 36.2, r1 = 0.218, r2 = 0.218, center = false, $fn = 12);
}
rotate([-180, 0, 0])
translate([-18.1, -2.771, 0.628]) cube(size = [21.115, 20.871, 0.474], center = false);
}
difference() {
intersection() {
union() {
difference() {
rotate([180, 0, 45])
translate([-18.1, -0.331, 0.818]) cube(size = [36.2, 18.431, 0.284], center = false);
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 13.858, 17.282], center = false);
}
rotate([180, 0, 45])
translate([-18.1, -18.1, 0.818]) cube(size = [17.769, 17.769, 0.284], center = false);
translate([-3.489, -4.242, -0.818]) cube(size = [21.589, 22.342, 0.19], center = false);
}
union() {
difference() {
rotate([90, 11, 0])
translate([-1.806, -18.1, -18.1]) cube(size = [19.906, 36.2, 36.2], center = false);
rotate([-11, 0, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 16.356, 36.2], center = false);
}
difference() {
rotate([-11, 0, 0])
translate([-3.489, -18.1, -18.1]) cube(size = [21.589, 15.776, 36.2], center = false);
translate([-2.437, -2.375, -0.818])
cylinder(h = 18.917, r1 = 0.279, r2 = 0.279, center = false, $fn = 12);
}
}
}
union() {
translate([-1.846, -1.779, -0.818])
cylinder(h = 0.19, r1 = 0.286, r2 = 0.286, center = false, $fn = 12);
translate([-1.369, -4.666, -18.1])
cylinder(h = 36.2, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
translate([-1.842, -1.778, -18.1])
cylinder(h = 17.282, r1 = 0.141, r2 = 0.141, center = false, $fn = 12);
translate([-0.418, -0.005, -1.102])
cylinder(h = 19.202, r1 = 1.409, r2 = 1.409, center = false, $fn = 12);
difference() {
rotate([90, 11, 0])
translate([-1.806, -18.1, -18.1]) cube(size = [19.906, 36.2, 36.2], center = false);
rotate([180, 0, 45])
translate([-18.1, -18.1, -18.1]) cube(size = [17.769, 18.338, 36.2], center = false);
}
}
}
intersection() {
difference() {
translate([-3.489, -4.242, -1.102]) cube(size = [21.589, 22.342, 0.474], center = false);
translate([-2.437, -2.375, -18.1])
cylinder(h = 17.472, r1 = 0.279, r2 = 0.279, center = false, $fn = 12);
}
union() {
rotate([90, 11, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [16.294, 36.2, 22.342], center = false);
rotate([180, 0, 45])
translate([-18.1, -0.331, 0.628]) cube(size = [17.769, 18.431, 0.474], center = false);
}
difference() {
union() {
rotate([-11, 0, 0])
translate([-3.489, -2.323, -18.1]) cube(size = [21.589, 0.58, 36.2], center = false);
rotate([180, 0, 45])
translate([-18.1, -18.1, -18.1]) cube(size = [17.769, 17.769, 19.202], center = false);
}
union() {
rotate([180, 0, 45])
translate([-18.1, -0.331, -18.1]) cube(size = [17.769, 0.569, 18.917], center = false);
translate([-3.88, -0.004, -1.102])
cylinder(h = 19.202, r1 = 1.435, r2 = 1.435, center = false, $fn = 12);
}
}
}
}
}
