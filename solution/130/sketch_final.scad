intersection() {
translate([-3.5, -6, -1.875]) cube(size = [7, 12, 3.75], center = false);
union() {
difference() {
difference() {
rotate([0, 0, 0])
translate([-0.811, -4.165, -1.562]) cube(size = [1.624, 8.331, 3.125], center = false);
translate([-0.001, 0, -18.1])
cylinder(h = 19.663, r1 = 2.084, r2 = 2.084, center = false, $fn = 12);
}
union() {
translate([-0.002, 4.161, -1.562])
cylinder(h = 19.663, r1 = 0.836, r2 = 0.836, center = false, $fn = 12);
translate([0.001, -4.163, -1.562])
cylinder(h = 19.663, r1 = 0.836, r2 = 0.836, center = false, $fn = 12);
}
}
difference() {
translate([-0.002, 4.161, -1.562])
cylinder(h = 3.125, r1 = 0.836, r2 = 0.836, center = false, $fn = 12);
translate([0, 4.166, -1.562])
cylinder(h = 3.125, r1 = 0.521, r2 = 0.521, center = false, $fn = 12);
}
difference() {
union() {
difference() {
rotate([180, 0, 180])
translate([-0.004, -0.002, -1.562])
cylinder(h = 3.125, r1 = 2.914, r2 = 2.914, center = false, $fn = 12);
translate([0, 0.001, -1.562])
cylinder(h = 19.663, r1 = 1.25, r2 = 1.25, center = false, $fn = 12);
}
difference() {
translate([0.001, -4.163, -1.562])
cylinder(h = 3.125, r1 = 0.836, r2 = 0.836, center = false, $fn = 12);
translate([0.001, -4.165, -18.1])
cylinder(h = 19.663, r1 = 0.519, r2 = 0.519, center = false, $fn = 12);
}
}
difference() {
translate([-0.001, 0, -0.937])
cylinder(h = 19.038, r1 = 2.084, r2 = 2.084, center = false, $fn = 12);
difference() {
rotate([0, 0, 0])
translate([-18.1, -4.165, -0.313]) cube(size = [36.2, 8.331, 1.875], center = false);
rotate([180, 0, 180])
translate([-0.004, -0.002, -0.937])
cylinder(h = 0.625, r1 = 2.914, r2 = 2.914, center = false, $fn = 12);
}
}
}
}
}
