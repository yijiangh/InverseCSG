translate([-2.123638, -5.060162, -1.768424])
rotate([5, 10, 25])
difference() {
  difference() {
    cube(size = [7.062127, 7.062127, 4.237276], center = false);
    translate([-2.118638, -3.531063, -2.118638])
    rotate([30, 0, 15])
    cube(size = [7.062127, 7.062127, 7.062127], center = false);
  }
  translate([8.474552, 0.000000, 2.118638])
  rotate([0, 0, 30])
  rotate([-90, 0, 0])
  cylinder(h = 14.124254, r1 = 0.423728, r2 = 0.423728, center = false, $fn = 60);
}
