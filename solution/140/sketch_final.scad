intersection() {
union() {
difference() {
translate([1.474, 0.02, -0.227]) cube(size = [0.137, 0.866, 0.143], center = false);
translate([1.302, 0.588, -0.14]) cube(size = [16.798, 0.208, 0.286], center = false);
}
translate([-1.564, 0.998, -0.227]) cube(size = [3.176, 0.148, 0.373], center = false);
translate([-1.564, 0.588, -0.227]) cube(size = [3.176, 0.41, 0.087], center = false);
translate([-1.302, 0.02, -0.227]) cube(size = [2.605, 0.568, 0.143], center = false);
translate([-1.564, 0.02, -0.227]) cube(size = [0.09, 0.568, 0.143], center = false);
difference() {
rotate([180, 0, 180])
translate([-1.389, 0.49, -0.146])
cylinder(h = 0.373, r1 = 0.172, r2 = 0.172, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-1.388, 0.49, -0.146])
cylinder(h = 0.373, r1 = 0.083, r2 = 0.083, center = false, $fn = 12);
}
translate([1.302, -5, -0.227]) cube(size = [0.172, 0.688, 0.373], center = false);
difference() {
translate([-1.564, 4.497, -0.227]) cube(size = [3.176, 0.503, 0.373], center = false);
translate([-18.1, 4.642, -0.14]) cube(size = [36.2, 0.358, 18.24], center = false);
}
difference() {
union() {
rotate([0, 0, 0])
translate([-1.388, -4.129, -0.084])
cylinder(h = 0.229, r1 = 0.173, r2 = 0.173, center = false, $fn = 12);
difference() {
translate([-1.564, -4.312, -0.227]) cube(size = [3.176, 0.281, 0.143], center = false);
rotate([180, 0, 180])
translate([-1.389, -4.214, -18.1])
cylinder(h = 18.327, r1 = 0.083, r2 = 0.083, center = false, $fn = 12);
}
}
rotate([0, 0, 0])
translate([-1.389, -4.128, -18.1])
cylinder(h = 36.2, r1 = 0.083, r2 = 0.083, center = false, $fn = 12);
}
translate([-1.564, 0.796, -0.227]) cube(size = [2.639, 0.09, 0.373], center = false);
difference() {
union() {
translate([-1.475, -1.288, -0.227]) cube(size = [0.172, 2.175, 0.373], center = false);
rotate([0, 0, 0])
translate([-1.389, 0.117, -0.227])
cylinder(h = 0.373, r1 = 0.172, r2 = 0.172, center = false, $fn = 12);
}
rotate([0, 0, 0])
translate([-1.387, 0.118, -0.227])
cylinder(h = 0.373, r1 = 0.083, r2 = 0.083, center = false, $fn = 12);
}
difference() {
difference() {
union() {
rotate([180, 90, 180])
translate([-0.071, 0.967, -1.564])
cylinder(h = 3.176, r1 = 0.194, r2 = 0.194, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-1.075, -1.116, -0.146])
cylinder(h = 0.373, r1 = 0.173, r2 = 0.173, center = false, $fn = 12);
translate([1.302, -4.312, -0.227]) cube(size = [0.172, 9.312, 0.373], center = false);
translate([1.075, -1.288, -0.227]) cube(size = [0.399, 2.175, 0.143], center = false);
}
intersection() {
translate([-1.564, -18.1, -0.227]) cube(size = [19.664, 19.098, 18.327], center = false);
union() {
translate([-1.564, -0.944, -18.1]) cube(size = [0.09, 1.942, 18.246], center = false);
rotate([180, 0, 180])
translate([-1.389, -4.214, -0.146])
cylinder(h = 0.373, r1 = 0.172, r2 = 0.172, center = false, $fn = 12);
}
}
}
union() {
difference() {
translate([-1.564, 0.886, -0.227]) cube(size = [3.039, 0.26, 18.327], center = false);
rotate([180, 90, 180])
translate([-0.08, 1.03, -18.1])
cylinder(h = 19.574, r1 = 0.147, r2 = 0.147, center = false, $fn = 12);
}
intersection() {
union() {
translate([-1.564, 0.886, -0.227]) cube(size = [3.176, 0.112, 18.327], center = false);
translate([1.075, -18.1, -0.227]) cube(size = [0.227, 18.896, 0.373], center = false);
}
translate([-1.564, -0.944, -0.227]) cube(size = [3.176, 2.09, 18.327], center = false);
}
rotate([180, 0, 180])
translate([-1.074, -1.116, -18.1])
cylinder(h = 18.327, r1 = 0.083, r2 = 0.083, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-1.389, 0.49, -0.146])
cylinder(h = 0.373, r1 = 0.172, r2 = 0.172, center = false, $fn = 12);
}
}
difference() {
union() {
rotate([180, 0, 180])
translate([-1.389, -4.214, -0.146])
cylinder(h = 0.286, r1 = 0.172, r2 = 0.172, center = false, $fn = 12);
translate([-1.564, -5, -0.227]) cube(size = [3.176, 0.688, 0.087], center = false);
difference() {
translate([-1.475, -5, -0.227]) cube(size = [0.172, 3.712, 0.373], center = false);
translate([-1.475, -4.312, -0.227]) cube(size = [2.949, 0.281, 0.373], center = false);
}
}
rotate([180, 0, 180])
translate([-1.389, -4.214, -0.146])
cylinder(h = 0.286, r1 = 0.083, r2 = 0.083, center = false, $fn = 12);
}
translate([-1.475, 0.998, -0.227]) cube(size = [0.172, 4.002, 0.373], center = false);
}
translate([-1.942, -6, -0.273]) cube(size = [3.883, 12, 0.546], center = false);
}
