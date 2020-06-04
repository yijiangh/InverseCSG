intersection() {
translate([-6, -6, -5.694]) cube(size = [12, 12, 11.389], center = false);
union() {
difference() {
difference() {
translate([0.002, 0.004, -4.745])
cylinder(h = 9.491, r1 = 4.623, r2 = 4.623, center = false, $fn = 12);
translate([-18.2, 1.852, -4.745]) cube(size = [36.4, 16.348, 9.028], center = false);
}
union() {
rotate([180, 90, -90])
translate([0.129, -0.003, -0.093])
cylinder(h = 1.944, r1 = 1.854, r2 = 1.854, center = false, $fn = 12);
rotate([180, 90, -90])
translate([0.084, -0.005, 0.921])
cylinder(h = 17.279, r1 = 2.289, r2 = 2.289, center = false, $fn = 12);
translate([-2.315, -0.093, -4.745]) cube(size = [4.63, 18.293, 4.662], center = false);
}
}
difference() {
union() {
translate([0.011, 0.001, 4.282])
cylinder(h = 0.463, r1 = 4.987, r2 = 4.987, center = false, $fn = 12);
translate([-2.315, -0.093, -4.745]) cube(size = [4.63, 1.014, 4.662], center = false);
}
translate([-1.852, -18.2, -4.745]) cube(size = [3.704, 36.4, 9.028], center = false);
}
}
}
