translate([-1.243421, -1.435949, -2.565049])
union() {
  difference() {
    sphere(r = 2.438293, $fn = 60);
    translate([-4.876587, -4.876587, 1.219147])
    cube(size = [9.753174, 9.753174, 7.314880], center = false);
  }
  rotate([10, 20, 15])
  cube(size = [2.438293, 4.876587, 7.314880], center = false);
}
