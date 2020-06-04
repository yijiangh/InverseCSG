translate([0.298909, -1.547235, -0.952848])
union() {
  difference() {
    union() {
      sphere(r = 1.429272, $fn = 60);
      translate([0.000000, 1.191060, 0.000000])
      sphere(r = 1.310166, $fn = 60);
    }
    translate([1.191060, 0.000000, 1.191060])
    sphere(r = 0.833742, $fn = 60);
  }
  translate([1.667485, 3.930499, 0.952848])
  sphere(r = 2.620333, $fn = 60);
  translate([-3.930499, -2.501227, -0.119106])
  sphere(r = 0.952848, $fn = 60);
}
