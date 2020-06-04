translate([-0.000000, -0.000000, -0.928574])
union() {
  translate([0.000000, 4.285714, 0.000000])
  rotate([0, 90, 0])
  cylinder(h = 5.714286, r1 = 0.714286, r2 = 0.714286, center = true, $fn = 60);
  
  translate([0.000000, -4.285714, 0.000000])
  rotate([0, 90, 0])
  cylinder(h = 5.714286, r1 = 0.714286, r2 = 0.714286, center = true, $fn = 60);
  
  translate([-2.857143, 0.000000, 0.000000])
  rotate([90, 0, 0])
  cylinder(h = 8.571429, r1 = 0.714286, r2 = 0.714286, center = true, $fn = 60);
  
  translate([2.857143, 0.000000, 0.000000])
  rotate([90, 0, 0])
  cylinder(h = 8.571429, r1 = 0.714286, r2 = 0.714286, center = true, $fn = 60);
  
  translate([-2.857143, -4.285714, 0.000000])
  sphere(r = 0.714286, $fn = 60);
  translate([2.857143, -4.285714, 0.000000])
  sphere(r = 0.714286, $fn = 60);
  translate([-2.857143, 4.285714, 0.000000])
  sphere(r = 0.714286, $fn = 60);
  translate([2.857143, 4.285714, 0.000000])
  sphere(r = 0.714286, $fn = 60);
  cube(size = [5.714286, 8.571429, 1.428571], center = true);
  difference() {
    union() {
      difference() {
        translate([0.821429, 0.000000, 1.285714])
        cube(size = [1.642857, 3.285714, 2.571429], center = true);
        translate([0.000000, 0.000000, 2.500000])
        rotate([90, 0, 0])
        cylinder(h = 4.285714, r1 = 1.071429, r2 = 1.071429, center = true, $fn = 60);
      }
      cylinder(h = 1.428571, r1 = 1.642857, r2 = 1.642857, center = false, $fn = 60);
    }
    translate([0.000000, 0.000000, 0.857143])
    cylinder(h = 2.142857, r1 = 1.035714, r2 = 1.035714, center = false, $fn = 60);
  }
}
