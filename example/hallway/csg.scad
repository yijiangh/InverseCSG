translate([-0.000000, -5.000000, 3.055556])
translate([0.000000, 3.703704, -1.111111])
union() {
  cube(size = [5.185185, 7.407407, 0.370370], center = true);
  translate([0.000000, 3.703704, 0.000000])
  intersection() {
    cylinder(h = 0.370370, r1 = 2.592593, r2 = 2.592593, center = true, $fn = 60);
    translate([0.000000, 2.962963, 0.000000])
    cube(size = [5.925926, 5.925926, 0.740741], center = true);
  }
  translate([0.000000, 0.000000, 0.185185])
  rotate([90, 0, 0])
  intersection() {
    union() {
      cylinder(h = 7.407407, r1 = 2.222222, r2 = 2.222222, center = true, $fn = 60);
      translate([0.000000, 0.000000, -3.703704])
      sphere(r = 2.222222, $fn = 60);
    }
    translate([0.000000, 3.703704, 0.000000])
    cube(size = [4.444444, 7.407407, 22.222222], center = true);
  }
  translate([1.851852, -0.740741, -3.111111])
  cylinder(h = 6.370370, r1 = 0.222222, r2 = 0.222222, center = true, $fn = 60);
  translate([1.851852, 2.222222, -3.111111])
  cylinder(h = 6.370370, r1 = 0.222222, r2 = 0.222222, center = true, $fn = 60);
  translate([1.111111, 5.185185, -3.111111])
  cylinder(h = 6.370370, r1 = 0.222222, r2 = 0.222222, center = true, $fn = 60);
  translate([-1.851852, -0.740741, -3.111111])
  cylinder(h = 6.370370, r1 = 0.222222, r2 = 0.222222, center = true, $fn = 60);
  translate([-1.851852, 2.222222, -3.111111])
  cylinder(h = 6.370370, r1 = 0.222222, r2 = 0.222222, center = true, $fn = 60);
  translate([-1.111111, 5.185185, -3.111111])
  cylinder(h = 6.370370, r1 = 0.222222, r2 = 0.222222, center = true, $fn = 60);
}
