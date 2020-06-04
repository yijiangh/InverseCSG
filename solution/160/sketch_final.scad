intersection() {
translate([-3.776, -6, -1.966]) cube(size = [7.552, 12, 3.931], center = false);
union() {
difference() {
translate([2.026, 1.036, -1.638]) cube(size = [1.035, 3.964, 1.034], center = false);
translate([2.026, -18.1, -1.293]) cube(size = [0.69, 22.755, 0.69], center = false);
}
intersection() {
union() {
rotate([90, 0, 0])
translate([-18.1, -18.1, -1.138]) cube(size = [19.091, 18.876, 19.238], center = false);
rotate([180, 90, -90])
translate([-0.261, -0.646, 0.448])
cylinder(h = 0.483, r1 = 1.381, r2 = 1.381, center = false, $fn = 12);
translate([-2.417, 0.332, -0.431])
cylinder(h = 1.207, r1 = 3.581, r2 = 3.581, center = false, $fn = 12);
rotate([180, 90, -90])
translate([-0.6, -0.985, 0.448])
cylinder(h = 0.69, r1 = 0.179, r2 = 0.179, center = false, $fn = 12);
}
difference() {
rotate([90, 1, 0])
translate([-18.1, -18.1, -1.138]) cube(size = [36.2, 36.2, 19.238], center = false);
rotate([90, 0, 0])
translate([0.129, -0.431, -0.931]) cube(size = [17.971, 1.464, 0.483], center = false);
}
union() {
rotate([90, 0, 0])
translate([0.302, 0.431, -1.138]) cube(size = [17.798, 0.602, 0.897], center = false);
translate([0.647, 0.69, 1.033])
cylinder(h = 17.067, r1 = 0.099, r2 = 0.099, center = false, $fn = 12);
}
}
rotate([180, 90, 180])
translate([-0.087, 0.69, 1.94])
cylinder(h = 0.603, r1 = 0.516, r2 = 0.516, center = false, $fn = 12);
rotate([180, 90, 180])
translate([-0.258, 0.517, 2.026])
cylinder(h = 1.035, r1 = 0.103, r2 = 0.103, center = false, $fn = 12);
intersection() {
rotate([180, 90, 180])
translate([1.294, 3.966, -3.147])
cylinder(h = 21.246, r1 = 0.137, r2 = 0.137, center = false, $fn = 12);
translate([-2.547, 0.957, -18.1])
cylinder(h = 17.497, r1 = 3.711, r2 = 3.711, center = false, $fn = 12);
}
intersection() {
rotate([180, 90, -90])
translate([0.217, -2.278, 0])
cylinder(h = 0.335, r1 = 0.438, r2 = 0.438, center = false, $fn = 12);
translate([2.636, 0.691, -0.603])
cylinder(h = 1.034, r1 = 0.518, r2 = 0.518, center = false, $fn = 12);
}
intersection() {
translate([-2.547, 0.957, -18.1])
cylinder(h = 19.133, r1 = 3.711, r2 = 3.711, center = false, $fn = 12);
union() {
translate([0.647, 0, -0.776])
cylinder(h = 1.379, r1 = 0.206, r2 = 0.206, center = false, $fn = 12);
intersection() {
translate([0.647, 0.69, 0.776])
cylinder(h = 0.257, r1 = 0.346, r2 = 0.346, center = false, $fn = 12);
rotate([90, 1, 0])
translate([-18.1, 0.871, -1.138]) cube(size = [36.2, 17.229, 19.238], center = false);
}
translate([0.647, 0.69, -0.259])
cylinder(h = 1.291, r1 = 0.099, r2 = 0.099, center = false, $fn = 12);
}
}
difference() {
union() {
translate([2.198, 0.334, 0.086]) cube(size = [0.948, 0.702, 0.69], center = false);
rotate([180, 90, 180])
translate([-0.087, 0.69, 2.198])
cylinder(h = 0.517, r1 = 0.516, r2 = 0.516, center = false, $fn = 12);
}
translate([2.543, 0, 0.086]) cube(size = [0.517, 18.1, 0.69], center = false);
}
rotate([180, 90, 180])
translate([-0.604, 0.518, 2.543])
cylinder(h = 0.517, r1 = 0.104, r2 = 0.104, center = false, $fn = 12);
translate([2.026, -5, -1.638]) cube(size = [0.69, 0.69, 1.034], center = false);
intersection() {
translate([-3.147, -18.1, -1.638]) cube(size = [0.345, 36.2, 1.034], center = false);
union() {
translate([-18.1, -4.659, -18.1]) cube(size = [15.298, 4.315, 36.2], center = false);
translate([-2.417, 0.332, -1.638])
cylinder(h = 0.345, r1 = 3.581, r2 = 3.581, center = false, $fn = 12);
}
}
difference() {
union() {
difference() {
translate([-2.802, -5, -1.638]) cube(size = [0.69, 4.656, 1.034], center = false);
translate([-2.457, -3.621, -18.1])
cylinder(h = 17.497, r1 = 0.171, r2 = 0.171, center = false, $fn = 12);
}
translate([2.026, -4.659, -1.638]) cube(size = [1.035, 4.315, 1.034], center = false);
}
union() {
translate([-2.802, -4.31, -1.293]) cube(size = [5.517, 3.966, 0.69], center = false);
translate([-2.457, -1.725, -18.1])
cylinder(h = 36.2, r1 = 0.171, r2 = 0.171, center = false, $fn = 12);
}
}
translate([-2.801, -4.659, -1.638])
cylinder(h = 1.034, r1 = 0.341, r2 = 0.341, center = false, $fn = 12);
rotate([180, 90, 180])
translate([1.295, -2.932, -2.802])
cylinder(h = 5.517, r1 = 0.138, r2 = 0.138, center = false, $fn = 12);
intersection() {
union() {
difference() {
translate([-18.1, -0.345, -1.293]) cube(size = [21.246, 0.345, 0.69], center = false);
rotate([180, 90, 180])
translate([0.423, -0.353, -18.1])
cylinder(h = 20.816, r1 = 0.355, r2 = 0.355, center = false, $fn = 12);
}
intersection() {
rotate([180, 90, -90])
translate([0.217, -2.278, 0.334])
cylinder(h = 17.766, r1 = 0.438, r2 = 0.438, center = false, $fn = 12);
translate([2.636, 0.691, -18.1])
cylinder(h = 18.186, r1 = 0.518, r2 = 0.518, center = false, $fn = 12);
}
rotate([180, 90, 180])
translate([-0.259, 0.862, 1.94])
cylinder(h = 1.121, r1 = 0.103, r2 = 0.103, center = false, $fn = 12);
translate([-18.1, 0, -1.638]) cube(size = [21.161, 0.335, 1.034], center = false);
difference() {
translate([-18.1, 0, -1.293]) cube(size = [21.161, 1.38, 2.241], center = false);
translate([2.543, 0.334, -0.603]) cube(size = [0.431, 1.046, 18.704], center = false);
}
}
union() {
translate([2.543, 0.334, -0.603]) cube(size = [0.172, 17.766, 18.704], center = false);
difference() {
rotate([180, 90, 180])
translate([-0.088, 0.69, -18.1])
cylinder(h = 20.04, r1 = 0.138, r2 = 0.138, center = false, $fn = 12);
translate([-2.417, 0.332, -0.603])
cylinder(h = 1.034, r1 = 3.581, r2 = 3.581, center = false, $fn = 12);
}
rotate([180, 90, 180])
translate([-0.616, 0.334, 2.198])
cylinder(h = 0.345, r1 = 0.327, r2 = 0.327, center = false, $fn = 12);
translate([2.716, -0.345, -1.638]) cube(size = [0.345, 1.381, 1.034], center = false);
translate([2.716, 0.334, 0.086]) cube(size = [0.431, 0.702, 0.69], center = false);
rotate([180, 90, 180])
translate([-0.609, 1.036, 2.198])
cylinder(h = 0.345, r1 = 0.34, r2 = 0.34, center = false, $fn = 12);
translate([2.198, -0.345, -1.638]) cube(size = [0.345, 1.724, 2.069], center = false);
}
}
translate([2.716, -4.657, -1.638])
cylinder(h = 1.034, r1 = 0.342, r2 = 0.342, center = false, $fn = 12);

difference() {
rotate([180, 90, 180])
translate([1.293, 0.69, -18.1])
cylinder(h = 20.298, r1 = 0.138, r2 = 0.138, center = false, $fn = 12);
translate([-2.417, 0.332, -1.638])
cylinder(h = 1.034, r1 = 3.581, r2 = 3.581, center = false, $fn = 12);
}
intersection() {
translate([-2.547, 0.957, -1.638])
cylinder(h = 1.034, r1 = 3.711, r2 = 3.711, center = false, $fn = 12);
union() {
rotate([180, 90, 180])
translate([1.293, 0.69, -2.284])
cylinder(h = 20.385, r1 = 0.138, r2 = 0.138, center = false, $fn = 12);
translate([-3.147, -0.345, -1.638]) cube(size = [0.345, 5.345, 1.034], center = false);
}
}
translate([2.198, 0.334, -1.293]) cube(size = [0.345, 0.702, 2.241], center = false);
translate([-2.629, 0, -1.293]) cube(size = [0.345, 1.38, 1.724], center = false);

intersection() {
translate([-2.547, 0.957, -0.603])
cylinder(h = 1.034, r1 = 3.711, r2 = 3.711, center = false, $fn = 12);
rotate([180, 90, 180])
translate([-0.088, 0.69, -2.026])
cylinder(h = 20.126, r1 = 0.138, r2 = 0.138, center = false, $fn = 12);
}
rotate([180, 90, 180])
translate([-0.616, 0.334, -2.629])
cylinder(h = 0.345, r1 = 0.327, r2 = 0.327, center = false, $fn = 12);
difference() {
union() {
difference() {
translate([-3.147, -0.345, -1.638]) cube(size = [1.034, 5.345, 0.345], center = false);
translate([-2.456, 2.071, -18.1])
cylinder(h = 16.807, r1 = 0.172, r2 = 0.172, center = false, $fn = 12);
}
translate([-2.629, -0.345, -1.293]) cube(size = [0.345, 1.381, 0.69], center = false);
difference() {
translate([-3.147, 1.379, -1.293]) cube(size = [1.034, 3.621, 0.69], center = false);
translate([-2.547, 0.957, -1.293])
cylinder(h = 0.69, r1 = 3.711, r2 = 3.711, center = false, $fn = 12);
}
rotate([180, 90, 180])
translate([-0.609, 1.036, -2.629])
cylinder(h = 0.345, r1 = 0.34, r2 = 0.34, center = false, $fn = 12);
rotate([180, 90, 180])
translate([-0.087, 0.69, -2.629])
cylinder(h = 0.603, r1 = 0.516, r2 = 0.516, center = false, $fn = 12);
translate([-2.629, 0.334, -1.293]) cube(size = [0.345, 0.702, 2.241], center = false);
}
rotate([180, 90, 180])
translate([0.423, -0.353, -2.629])
cylinder(h = 0.517, r1 = 0.355, r2 = 0.355, center = false, $fn = 12);
}
difference() {
rotate([180, 90, 180])
translate([1.294, 3.966, -18.1])
cylinder(h = 21.161, r1 = 0.137, r2 = 0.137, center = false, $fn = 12);
translate([-2.547, 0.957, -18.1])
cylinder(h = 17.497, r1 = 3.711, r2 = 3.711, center = false, $fn = 12);
}
rotate([180, 90, 180])
translate([-0.603, 0.862, 2.198])
cylinder(h = 0.948, r1 = 0.103, r2 = 0.103, center = false, $fn = 12);
intersection() {
rotate([180, 90, -90])
translate([-0.261, -0.646, -18.1])
cylinder(h = 19.031, r1 = 1.381, r2 = 1.381, center = false, $fn = 12);
union() {
rotate([90, 0, 0])
translate([0.129, -0.776, -0.448]) cube(size = [17.971, 1.552, 0.207], center = false);
translate([0.646, 0, -18.1])
cylinder(h = 18.359, r1 = 0.086, r2 = 0.086, center = false, $fn = 12);
}
translate([-2.417, 0.332, -18.1])
cylinder(h = 18.703, r1 = 3.581, r2 = 3.581, center = false, $fn = 12);
}
intersection() {
union() {
rotate([90, 0, 0])
translate([0.302, -0.259, -18.1]) cube(size = [0.69, 0.69, 17.859], center = false);
intersection() {
translate([-2.547, 0.957, -0.776])
cylinder(h = 1.552, r1 = 3.711, r2 = 3.711, center = false, $fn = 12);
rotate([180, 90, -90])
translate([-0.261, -0.646, 0.931])
cylinder(h = 0.207, r1 = 1.381, r2 = 1.381, center = false, $fn = 12);
}
translate([0.646, 0.002, -0.431])
cylinder(h = 0.69, r1 = 0.346, r2 = 0.346, center = false, $fn = 12);
}
difference() {
union() {
rotate([180, 90, -90])
translate([-0.596, -0.307, 0.931])
cylinder(h = 0.207, r1 = 0.181, r2 = 0.181, center = false, $fn = 12);
rotate([90, 0, 0])
translate([0.129, -0.776, -1.138]) cube(size = [17.971, 1.379, 19.238], center = false);
}
intersection() {
rotate([180, 90, -90])
translate([-0.261, -0.646, -18.1])
cylinder(h = 19.031, r1 = 1.381, r2 = 1.381, center = false, $fn = 12);
translate([0.647, 0.69, -0.431])
cylinder(h = 0.172, r1 = 0.346, r2 = 0.346, center = false, $fn = 12);
}
}
}
translate([2.026, -0.345, -1.638]) cube(size = [1.035, 1.381, 0.345], center = false);
difference() {
union() {
rotate([90, 0, 0])
translate([0.302, 0.603, -1.138]) cube(size = [0.69, 0.173, 0.207], center = false);
rotate([180, 90, -90])
translate([-0.596, -0.307, 0.241])
cylinder(h = 0.207, r1 = 0.181, r2 = 0.181, center = false, $fn = 12);
}
union() {
rotate([90, 0, 0])
translate([0.991, -0.431, -0.448]) cube(size = [17.109, 1.034, 0.207], center = false);
rotate([90, 0, 0])
translate([0.302, 0.431, -1.138]) cube(size = [0.69, 0.172, 0.207], center = false);
}
}
}
}
