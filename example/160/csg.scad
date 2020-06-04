translate([-0.043103, 0.517241, -0.431034])
union() {
  translate([0.689655, 0.172414, 1.379310])
  union() {
    translate([0.000000, 0.000000, 0.344828])
    cylinder(h = 0.689655, r1 = 0.103448, r2 = 0.103448, center = true, $fn = 60);
    translate([0.000000, 0.000000, -0.517241])
    cylinder(h = 1.034483, r1 = 0.131034, r2 = 0.131034, center = true, $fn = 60);
    cylinder(h = 0.172414, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
  }
  // Header.
  translate([0.689655, 0.172414, 0.517241])
  cube(size = [0.689655, 0.862069, 0.689655], center = true);

  translate([0.689655, -0.172414, 0.344828])
  union() {
    cube(size = [1.034483, 0.206897, 1.379310], center = true);
    translate([-0.344828, 0.000000, 0.689655])
    rotate([90, 0, 0])
    cylinder(h = 0.206897, r1 = 0.172414, r2 = 0.172414, center = true, $fn = 60);
    translate([0.344828, 0.000000, 0.689655])
    rotate([90, 0, 0])
    cylinder(h = 0.206897, r1 = 0.172414, r2 = 0.172414, center = true, $fn = 60);
    translate([0.000000, 0.000000, 0.689655])
    cube(size = [0.689655, 0.206897, 0.344828], center = true);
    translate([0.000000, -0.344828, 0.000000])
    union() {
      cylinder(h = 0.689655, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
      cylinder(h = 1.379310, r1 = 0.206897, r2 = 0.206897, center = true, $fn = 60);
      translate([0.000000, 0.000000, -0.517241])
      cylinder(h = 1.034483, r1 = 0.086207, r2 = 0.086207, center = true, $fn = 60);
    }
  }
  translate([0.689655, 0.517241, 0.344828])
  union() {
    cube(size = [1.034483, 0.206897, 1.379310], center = true);
    translate([-0.344828, 0.000000, 0.689655])
    rotate([90, 0, 0])
    cylinder(h = 0.206897, r1 = 0.172414, r2 = 0.172414, center = true, $fn = 60);
    translate([0.344828, 0.000000, 0.689655])
    rotate([90, 0, 0])
    cylinder(h = 0.206897, r1 = 0.172414, r2 = 0.172414, center = true, $fn = 60);
    translate([0.000000, 0.000000, 0.689655])
    cube(size = [0.689655, 0.206897, 0.344828], center = true);
  }
  
  translate([0.000000, 0.172414, 0.517241])
  rotate([0, 90, 0])
  cylinder(h = 4.827586, r1 = 0.137931, r2 = 0.137931, center = true, $fn = 60);

  translate([0.000000, 0.172414, -0.862069])
  rotate([0, 90, 0])
  cylinder(h = 4.827586, r1 = 0.137931, r2 = 0.137931, center = true, $fn = 60);

  translate([0.000000, 3.448276, -0.862069])
  rotate([0, 90, 0])
  cylinder(h = 5.862069, r1 = 0.137931, r2 = 0.137931, center = true, $fn = 60);

  translate([0.000000, -3.448276, -0.862069])
  rotate([0, 90, 0])
  cylinder(h = 5.862069, r1 = 0.137931, r2 = 0.137931, center = true, $fn = 60);

  // Left.
  translate([-2.413793, 0.000000, 0.000000])
  union() {
    translate([0.172414, 0.172414, 0.517241])
    rotate([0, 90, 0])
    cylinder(h = 0.517241, r1 = 0.517241, r2 = 0.517241, center = true, $fn = 60);
    difference() {
      cube(size = [0.344828, 1.724138, 2.068966], center = true);
      union() {
        translate([0.000000, -0.862069, 0.000000])
        rotate([0, 90, 0])
        cylinder(h = 0.689655, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
        translate([0.000000, -0.689655, 0.517241])
        cube(size = [0.689655, 0.344828, 1.034483], center = true);
      }
    }
    translate([0.000000, -0.172414, 1.034483])
    rotate([0, 90, 0])
    cylinder(h = 0.344828, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
    translate([0.000000, 0.517241, 1.034483])
    rotate([0, 90, 0])
    cylinder(h = 0.344828, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
    translate([0.000000, 0.172414, 1.206897])
    cube(size = [0.344828, 0.689655, 0.344828], center = true);

    translate([-0.172414, -0.344828, -0.689655])
    union() {
      translate([0.172414, -5.000000, 0.000000])
      cube(size = [0.689655, 0.344828, 1.034483], center = true);
      translate([-0.172414, -4.827586, 0.000000])
      cylinder(h = 1.034483, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
      difference() {
        cube(size = [1.034483, 9.655172, 1.034483], center = true);
        union() {
          translate([0.172414, 1.896552, 0.000000])
          cylinder(h = 1.724138, r1 = 0.172414, r2 = 0.172414, center = true, $fn = 60);
          translate([0.172414, -1.896552, 0.000000])
          cylinder(h = 1.724138, r1 = 0.172414, r2 = 0.172414, center = true, $fn = 60);
          translate([0.172414, -3.793103, 0.000000])
          cylinder(h = 1.724138, r1 = 0.172414, r2 = 0.172414, center = true, $fn = 60);
          translate([0.344828, 0.000000, 0.344828])
          cube(size = [1.034483, 8.965517, 1.034483], center = true);
        }
      }
    }
  }

  // Right.
  translate([2.413793, 0.000000, 0.000000])
  union() {
    translate([0.689655, 0.172414, 0.862069])
    cube(size = [0.172414, 0.689655, 0.689655], center = true);
    translate([0.344828, 0.000000, 0.689655])
    rotate([0, 90, 0])
    cylinder(h = 0.689655, r1 = 0.103448, r2 = 0.103448, center = true, $fn = 60);
    translate([0.344828, 0.344828, 0.689655])
    rotate([0, 90, 0])
    cylinder(h = 0.689655, r1 = 0.103448, r2 = 0.103448, center = true, $fn = 60);
    translate([0.344828, 0.344828, 1.034483])
    rotate([0, 90, 0])
    cylinder(h = 0.689655, r1 = 0.103448, r2 = 0.103448, center = true, $fn = 60);
    translate([0.344828, 0.000000, 1.034483])
    rotate([0, 90, 0])
    cylinder(h = 0.689655, r1 = 0.103448, r2 = 0.103448, center = true, $fn = 60);
    translate([0.000000, 0.172414, 0.172414])
    union() {
      translate([0.172414, 0.000000, 0.172414])
      cube(size = [0.344828, 1.034483, 0.344828], center = true);
      intersection() {
        translate([0.344828, 0.000000, 0.000000])
        cube(size = [0.689655, 1.379310, 1.034483], center = true);
        rotate([90, 0, 0])
        cylinder(h = 1.034483, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
      }
    }

    translate([-0.172414, 0.172414, 0.517241])
    rotate([0, 90, 0])
    cylinder(h = 0.517241, r1 = 0.517241, r2 = 0.517241, center = true, $fn = 60);
    difference() {
      cube(size = [0.344828, 1.724138, 2.068966], center = true);
      union() {
        translate([0.000000, -0.862069, 0.000000])
        rotate([0, 90, 0])
        cylinder(h = 0.689655, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
        translate([0.000000, -0.689655, 0.517241])
        cube(size = [0.689655, 0.344828, 1.034483], center = true);
      }
    }
    translate([0.000000, -0.172414, 1.034483])
    rotate([0, 90, 0])
    cylinder(h = 0.344828, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
    translate([0.000000, 0.517241, 1.034483])
    rotate([0, 90, 0])
    cylinder(h = 0.344828, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
    translate([0.000000, 0.172414, 1.206897])
    cube(size = [0.344828, 0.689655, 0.344828], center = true);

    translate([0.172414, -0.344828, -0.689655])
    union() {
      translate([-0.172414, -5.000000, 0.000000])
      cube(size = [0.689655, 0.344828, 1.034483], center = true);
      translate([0.172414, -4.827586, 0.000000])
      cylinder(h = 1.034483, r1 = 0.344828, r2 = 0.344828, center = true, $fn = 60);
      difference() {
        cube(size = [1.034483, 9.655172, 1.034483], center = true);
        translate([-0.344828, 0.000000, 0.344828])
        cube(size = [1.034483, 8.965517, 1.034483], center = true);
      }
    }
  }
}