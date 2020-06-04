translate([-0.000000, -0.000000, 4.513889])
union() {
  cylinder(h = 0.462963, r1 = 5.000000, r2 = 5.000000, center = true, $fn = 60);
  translate([0.000000, 0.000000, -4.629630])
  difference() {
    intersection() {
      cylinder(h = 9.259259, r1 = 4.629630, r2 = 4.629630, center = true, $fn = 60);
      translate([0.000000, -2.777778, 0.000000])
      cube(size = [9.259259, 9.259259, 9.259259], center = true);
    }
    translate([0.000000, 1.388889, -2.314815])
    union() {
      // Door 1.
      union() {
        translate([0.000000, 0.000000, 2.314815])
        rotate([90, 0, 0])
        cylinder(h = 0.935926, r1 = 2.314815, r2 = 2.314815, center = true, $fn = 60);
        cube(size = [4.629630, 0.935926, 4.629630], center = true);
      }
      // Door 2.
      translate([0.000000, -0.555556, 0.000000])
      union() {
        translate([0.000000, 0.000000, 2.314815])
        rotate([90, 0, 0])
        cylinder(h = 1.851852, r1 = 1.851852, r2 = 1.851852, center = true, $fn = 60);
        cube(size = [3.703704, 1.851852, 4.629630], center = true);
      }
    }
  }
}
