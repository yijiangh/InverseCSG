translate([-0.000000, -0.000000, -2.115384])
union() {
  cube(size = [9.230769, 4.615385, 0.769231], center = true);
  cylinder(h = 4.615385, r1 = 0.384615, r2 = 0.384615, center = false, $fn = 60);
  translate([3.076923, 0.000000, 0.000000])
  cylinder(h = 4.615385, r1 = 0.384615, r2 = 0.384615, center = false, $fn = 60);
  translate([-3.076923, 0.000000, 0.000000])
  cylinder(h = 4.615385, r1 = 0.384615, r2 = 0.384615, center = false, $fn = 60);
  cylinder(h = 1.153846, r1 = 1.153846, r2 = 1.153846, center = false, $fn = 60);
  translate([0.000000, 0.000000, 0.769231])
  cylinder(h = 1.153846, r1 = 0.769231, r2 = 0.769231, center = false, $fn = 60);
  translate([3.076923, 0.000000, 0.000000])
  cylinder(h = 1.153846, r1 = 1.153846, r2 = 1.153846, center = false, $fn = 60);

  translate([4.615385, 2.307692, 0.000000])
  sphere(r = 0.384615, $fn = 60);
  translate([-4.615385, 2.307692, 0.000000])
  sphere(r = 0.384615, $fn = 60);
  translate([4.615385, -2.307692, 0.000000])
  sphere(r = 0.384615, $fn = 60);
  translate([-4.615385, -2.307692, 0.000000])
  sphere(r = 0.384615, $fn = 60);

  translate([0.000000, 2.307692, 0.000000])
  rotate([0, 90, 0])
  cylinder(h = 9.230769, r1 = 0.384615, r2 = 0.384615, center = true, $fn = 60);

  translate([0.000000, -2.307692, 0.000000])
  rotate([0, 90, 0])
  cylinder(h = 9.230769, r1 = 0.384615, r2 = 0.384615, center = true, $fn = 60);

  translate([4.615385, 0.000000, 0.000000])
  rotate([90, 0, 0])
  cylinder(h = 4.615385, r1 = 0.384615, r2 = 0.384615, center = true, $fn = 60);

  translate([-4.615385, 0.000000, 0.000000])
  rotate([90, 0, 0])
  cylinder(h = 4.615385, r1 = 0.384615, r2 = 0.384615, center = true, $fn = 60);
}