translate([0.236883, -0.188650, -2.171123])
difference() {
  difference() {
    union() {
      union() {
        difference() {
          union() {
            sphere(r = 1.132691, $fn = 60);
            translate([0.000000, 0.943909, 0.000000])
            sphere(r = 1.038300, $fn = 60);
          }
          translate([0.943909, 0.000000, 0.943909])
          sphere(r = 0.660736, $fn = 60);
        }
        translate([1.321473, 3.114900, 0.755127])
        sphere(r = 2.076600, $fn = 60);
        translate([-3.114900, -1.982209, -0.094391])
        sphere(r = 0.755127, $fn = 60);
      }
      translate([1.415864, -2.926118, 3.775637])
      sphere(r = 1.887818, $fn = 60);
    }
    translate([1.415864, -1.887818, 3.775637])
    sphere(r = 1.604646, $fn = 60);
  }
  translate([-0.471955, 2.076600, 1.321473])
  sphere(r = 1.510255, $fn = 60);
}
