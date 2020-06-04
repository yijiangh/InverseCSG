translate([-0.000000, -0.000000, -0.000000])
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
}