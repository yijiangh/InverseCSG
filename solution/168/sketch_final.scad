intersection() {
translate([-5.182512, -5.181288, -6.000000])
cube(size = [10.365024, 10.362576, 12.000000], center = false);
union() {
// Begin.
union() {
union() {
intersection() {
rotate([0, -90, 0])
translate([0, -1.16959, 1.11723])
rotate([0, 90, 0])
cylinder(h = 36.4, r1 = 5.47377, r2 = 5.47377, center = true, $fn = 12);

union() {
union() {
translate([-1.18516, -1.13425, -4.58668])
rotate([0, -89.2383, 14.5067])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.72367, 0, 0])
circle(r = 0.45794, $fn = 12);

translate([-1.1528, -1.19327, 4.61079])
rotate([0, -88.8582, -4.28842])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.69708, 0, 0])
circle(r = 0.46273, $fn = 12);
}

rotate([0, -0, 0])
translate([8.53174, 0.282255, 0])
cube(size = [19.3365, 2.83957, 9.09212], center = true);
}
}

intersection() {
union() {
difference() {
rotate([0, -90, 0])
translate([0, -1.16959, 1.11723])
rotate([0, 90, 0])
cylinder(h = 9.09212, r1 = 5.47377, r2 = 5.47377, center = true, $fn = 12);

rotate([0, -0, 0])
translate([-9.66826, 0, -1.81843])
cube(size = [17.0635, 36.4, 5.45527], center = true);
}

translate([-1.0849, -1.18142, -2.74757])
rotate([0, 89.5037, 0])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.79388, 0, 0])
circle(r = 0.48087, $fn = 12);
}

union() {
difference() {
rotate([0, -90, 0])
translate([-0.909215, -1.16959, 1.11723])
rotate([0, 90, 0])
cylinder(h = 3.63685, r1 = 5.47377, r2 = 5.47377, center = true, $fn = 12);

rotate([0, -0, 0])
translate([8.53174, 0, -0.909215])
cube(size = [19.3365, 36.4, 3.63685], center = true);
}

union() {
rotate([0, -0, 0])
translate([0, 8.53124, -1.81842])
cube(size = [36.4, 19.3375, 1.81843], center = true);

translate([-1.18024, -1.19717, 2.62551])
rotate([0, -88.0517, 40.0365])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.67204, 0, 0])
circle(r = 0.45579, $fn = 12);
}
}
}
}

union() {
union() {
translate([-1.0849, -1.18142, -2.74757])
rotate([0, 89.5037, 0])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.79388, 0, 0])
circle(r = 0.48087, $fn = 12);

translate([-1.21492, -1.13981, 0.98564])
rotate([0, 88.3286, -8.9747])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.64713, 0, 0])
circle(r = 0.45473, $fn = 12);
}

union() {
translate([-1.07073, -1.20264, -0.91725])
rotate([0, 89.5751, 0])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([2.7395, 0, 0])
circle(r = 0.48215, $fn = 12);

intersection() {
rotate([0, -90, 0])
translate([0, -1.16959, 1.11723])
rotate([0, 90, 0])
cylinder(h = 9.09212, r1 = 5.47377, r2 = 5.47377, center = true, $fn = 12);

union() {
rotate([0, -0, 0])
translate([0.283265, 8.53124, 0])
cube(size = [2.83957, 19.3375, 9.09212], center = true);

rotate([0, -0, 0])
translate([8.53174, 8.53124, 1.81842])
cube(size = [19.3365, 19.3375, 1.81843], center = true);
}
}
}
}
}
// End.
}
}
