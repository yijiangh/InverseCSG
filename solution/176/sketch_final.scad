intersection() {
translate([-6.000000, -5.189184, -2.918916])
cube(size = [12.000000, 10.378368, 5.837832], center = false);
union() {
// Begin.
union() {
difference() {
difference() {
difference() {
difference() {
rotate([0, -0, 0])
translate([-0.675675, 0, 0])
cube(size = [8.64865, 8.64864, 4.86486], center = true);

rotate([0, -0, 0])
translate([0.405405, 0.20101, 2.65962])
rotate([0, 90, 0])
cylinder(h = 1.24325, r1 = 3.79973, r2 = 3.79973, center = true, $fn = 12);
}

union() {
rotate([0, -0, 0])
translate([-3.37838, 0.108975, 0])
cube(size = [1.24324, 0.18407, 4.86486], center = true);

rotate([0, -0, 0])
translate([-3.37838, 0.20101, 2.65962])
rotate([0, 90, 0])
cylinder(h = 1.24324, r1 = 3.79973, r2 = 3.79973, center = true, $fn = 12);
}
}

intersection() {
rotate([0, -0, 0])
translate([-0.675675, -2.15369, 7.88379])
cube(size = [8.64865, 4.34126, 20.6324], center = true);

rotate([0, -0, 0])
translate([-7.27568, 0.01694, 2.67473])
rotate([0, 90, 0])
cylinder(h = 21.8486, r1 = 3.72531, r2 = 3.72531, center = true, $fn = 12);
}
}

rotate([0, -0, 0])
translate([-7.27568, 0.05763, 2.42156])
rotate([0, 90, 0])
cylinder(h = 21.8486, r1 = 3.43817, r2 = 3.43817, center = true, $fn = 12);
}

difference() {
difference() {
rotate([0, -0, 0])
translate([0, 0, 0])
cube(size = [10, 8.64864, 4.86486], center = true);

union() {
union() {
rotate([0, -0, 0])
translate([0.405405, 0.01694, 2.67473])
rotate([0, 90, 0])
cylinder(h = 1.24325, r1 = 3.72531, r2 = 3.72531, center = true, $fn = 12);

rotate([0, -0, 0])
translate([-3.37838, 6.93784, 0])
cube(size = [1.24324, 22.5243, 4.86486], center = true);
}

rotate([0, -0, 0])
translate([-6.6, -0.02106, 2.46531])
rotate([0, 90, 0])
cylinder(h = 23.2, r1 = 1.3925, r2 = 1.3925, center = true, $fn = 12);
}
}

rotate([0, -0, 0])
translate([-7.27568, 0.20101, 2.65962])
rotate([0, 90, 0])
cylinder(h = 21.8486, r1 = 3.79973, r2 = 3.79973, center = true, $fn = 12);
}
}
// End.
}
}
