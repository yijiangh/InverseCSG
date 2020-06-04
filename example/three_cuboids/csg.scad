translate([-1.175104, -0.977268, -1.097192])
union() {
  rotate([5, 10, 15])
  translate([-1.207756, -3.623267, -3.623267])
  cube(size = [1.207756, 9.662046, 9.058168], center = false);
  rotate([-10, -10, -10])
  difference() {
    cube(size = [4.831023, 4.831023, 4.831023], center = false);
    translate([2.777838, 2.777838, 1.026592])
    rotate([45, 45, 45])
    cube(size = [2.415511, 2.415511, 2.415511], center = false);
  }
}
