translate([-0.000000, -0.000000, -5.000000])
union() {
  difference() {
    sphere(r = 3.676471, $fn = 60);
    translate([0.000000, 0.000000, -3.676471])
    cube(size = [7.352941, 7.352941, 7.352941], center = true);
  }
  translate([0.000000, 0.000000, 1.911765])
  cylinder(h = 3.529412, r1 = 1.470588, r2 = 1.470588, center = true, $fn = 60);
  translate([-1.102941, 0.000000, 5.514706])
  cylinder(h = 3.750000, r1 = 0.220588, r2 = 0.220588, center = true, $fn = 60);
  translate([1.102941, 0.000000, 5.514706])
  cylinder(h = 3.750000, r1 = 0.220588, r2 = 0.220588, center = true, $fn = 60);
  translate([0.000000, 1.102941, 5.514706])
  cylinder(h = 3.750000, r1 = 0.220588, r2 = 0.220588, center = true, $fn = 60);
  translate([0.000000, -1.102941, 5.514706])
  cylinder(h = 3.750000, r1 = 0.220588, r2 = 0.220588, center = true, $fn = 60);
  translate([0.000000, 0.000000, 7.352941])
  cylinder(h = 0.367647, r1 = 1.470588, r2 = 1.470588, center = true, $fn = 60);
  translate([0.000000, 0.000000, 7.352941])
  difference() {
    sphere(r = 1.176471, $fn = 60);
    translate([0.000000, 0.000000, -1.176471])
    cube(size = [2.352941, 2.352941, 2.352941], center = true);
  }
  translate([0.000000, 0.000000, 9.259706])
  cylinder(h = 1.480588, r1 = 0.220588, r2 = 0.220588, center = true, $fn = 60);
}
