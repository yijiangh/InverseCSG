intersection() {
translate([-6.000000, -6.000000, -2.998512])
cube(size = [12.000000, 12.000000, 5.997024], center = false);
union() {
// Begin.
union() {
difference() {
difference() {
union() {
difference() {
rotate([0, -89.9328, 0])
translate([7.85062, 0.0154, -0.00714])
rotate([0, 90, 0])
cylinder(h = 20.6988, r1 = 3.22461, r2 = 3.22461, center = true, $fn = 12);

rotate([0, -90, 0])
translate([7.85062, -1.81934, -1.82635])
rotate([0, 90, 0])
cylinder(h = 20.6988, r1 = 0.48464, r2 = 0.48464, center = true, $fn = 12);
}

union() {
translate([-3.24024, -0.04313, 0.71347])
rotate([0, 1.09555, 89.9123])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.31773, 0, 0])
circle(r = 0.47897, $fn = 12);

translate([0.00221, -3.18163, 0.74525])
rotate([0, 0.882985, -0.735792])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.33467, 0, 0])
circle(r = 0.48182, $fn = 12);
}
}

union() {
union() {
rotate([0, -89.9328, 0])
translate([9.46353, 0.0154, -0.00714])
rotate([0, 90, 0])
cylinder(h = 17.4729, r1 = 3.22461, r2 = 3.22461, center = true, $fn = 12);

rotate([0, -90, 0])
translate([-0.885855, -1.82696, 1.82913])
rotate([0, 90, 0])
cylinder(h = 3.22581, r1 = 0.48159, r2 = 0.48159, center = true, $fn = 12);
}

union() {
rotate([0, -90, 0])
translate([0.081885, -1.81934, -1.82635])
rotate([0, 90, 0])
cylinder(h = 1.29033, r1 = 0.48464, r2 = 0.48464, center = true, $fn = 12);

translate([0.00864, 3.14694, 0.82208])
rotate([0, -0.824486, -0.0315127])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.1759, 0, 0])
circle(r = 0.49148, $fn = 12);
}
}
}

union() {
union() {
union() {
rotate([0, -90, 0])
translate([0, -0.00318, -0.0122])
rotate([0, 90, 0])
cylinder(h = 36.4, r1 = 0.49578, r2 = 0.49578, center = true, $fn = 12);

rotate([0, -90, 0])
translate([8.81836, 0.01725, 0.00475])
rotate([0, 90, 0])
cylinder(h = 18.7633, r1 = 0.95977, r2 = 0.95977, center = true, $fn = 12);
}

rotate([0, -90, 0])
translate([-8.73647, 1.82755, -1.81901])
rotate([0, 90, 0])
cylinder(h = 18.9271, r1 = 0.46457, r2 = 0.46457, center = true, $fn = 12);
}

rotate([0, -90, 0])
translate([-8.73647, 1.81374, 1.82206])
rotate([0, 90, 0])
cylinder(h = 18.9271, r1 = 0.46805, r2 = 0.46805, center = true, $fn = 12);
}
}

union() {
difference() {
union() {
union() {
translate([3.20983, 0.04481, 0.73007])
rotate([0, -0.608481, 89.27])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.27447, 0, 0])
circle(r = 0.47981, $fn = 12);

translate([-3.24024, -0.04313, 0.71347])
rotate([0, 1.09555, 89.9123])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.31773, 0, 0])
circle(r = 0.47897, $fn = 12);
}

intersection() {
translate([0.00221, -3.18163, 0.74525])
rotate([0, 0.882985, -0.735792])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.33467, 0, 0])
circle(r = 0.48182, $fn = 12);

translate([3.20983, 0.04481, 0.73007])
rotate([0, -0.608481, 89.27])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.27447, 0, 0])
circle(r = 0.47981, $fn = 12);
}
}

rotate([0, -90, 0])
translate([-10.3494, 1.81374, 1.82206])
rotate([0, 90, 0])
cylinder(h = 15.7012, r1 = 0.46805, r2 = 0.46805, center = true, $fn = 12);
}

union() {
translate([0.00221, -3.18163, 0.74525])
rotate([0, 0.882985, -0.735792])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.33467, 0, 0])
circle(r = 0.48182, $fn = 12);

translate([0.00864, 3.14694, 0.82208])
rotate([0, -0.824486, -0.0315127])
rotate([0, 90, 0])
rotate_extrude($fn = 12)
translate([1.1759, 0, 0])
circle(r = 0.49148, $fn = 12);
}
}
}
// End.
}
}
