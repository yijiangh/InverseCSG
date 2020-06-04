difference() {
union() {
translate([0, 2.5, 1])
cube(size = [6, 5, 2], center = true);

difference() {
translate([0, 0, -1])
cube(size = [6, 10, 2], center = true);

union() {
translate([1.5, -3, 0])
union() {
cylinder(h = 10, r1 = 0.4, r2 = 0.4, center = true, $fn = 60);
cylinder(h = 2, r1 = 0.6, r2 = 0.6, center = true, $fn = 60);
}

translate([-1.5, -3, 0])
union() {
cylinder(h = 10, r1 = 0.4, r2 = 0.4, center = true, $fn = 60);
cylinder(h = 2, r1 = 0.6, r2 = 0.6, center = true, $fn = 60);
}
}
}
}

union() {
translate([-2.5, 0.5, 0])
cylinder(h = 10, r1 = 0.2, r2 = 0.2, center = true, $fn = 60);
translate([2.5, 0.5, 0])
cylinder(h = 10, r1 = 0.2, r2 = 0.2, center = true, $fn = 60);
translate([2.5, 4.5, 0])
cylinder(h = 10, r1 = 0.2, r2 = 0.2, center = true, $fn = 60);
translate([-2.5, 4.5, 0])
cylinder(h = 10, r1 = 0.2, r2 = 0.2, center = true, $fn = 60);

translate([0, 1.75, 2])
union() {
cube(size = [4, 1.5, 2], center = true);
cube(size = [3, 2.5, 2], center = true);
translate([1.5, 0.75, 0])
cylinder(h = 2, r1 = 0.5, r2 = 0.5, center = true, $fn = 60);
translate([-1.5, 0.75, 0])
cylinder(h = 2, r1 = 0.5, r2 = 0.5, center = true, $fn = 60);
translate([1.5, -0.75, 0])
cylinder(h = 2, r1 = 0.5, r2 = 0.5, center = true, $fn = 60);
translate([-1.5, -0.75, 0])
cylinder(h = 2, r1 = 0.5, r2 = 0.5, center = true, $fn = 60);
}

translate([0, 3.5, 2])
union() {
cube(size = [2, 1, 1], center = true);
cube(size = [1, 2, 1], center = true);
translate([0.5, 0.5, 0])
cylinder(h = 1, r1 = 0.5, r2 = 0.5, center = true, $fn = 60);
translate([-0.5, 0.5, 0])
cylinder(h = 1, r1 = 0.5, r2 = 0.5, center = true, $fn = 60);
}

}
}