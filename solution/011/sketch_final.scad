intersection() {
translate([-0.504, -0.504, -6]) cube(size = [1.008, 1.009, 12], center = false);
union() {
difference() {
translate([-0.002, 0.001, 4.488])
cylinder(h = 0.512, r1 = 0.42, r2 = 0.42, center = false, $fn = 12);
translate([-0.001, 0, -18.1])
cylinder(h = 36.2, r1 = 0.261, r2 = 0.261, center = false, $fn = 12);
}
translate([-0.001, 0, -5])
cylinder(h = 9.756, r1 = 0.261, r2 = 0.261, center = false, $fn = 12);
}
}
