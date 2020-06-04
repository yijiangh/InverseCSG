translate([-3.235401, 1.455586, -2.158996])
union() {
  union() {
    rotate([5, 10, 15])
    translate([-0.644892, -1.934676, -1.934676])
    cube(size = [0.644892, 5.159137, 4.836691], center = false);
    rotate([-10, -10, -10])
    difference() {
      cube(size = [2.579568, 2.579568, 2.579568], center = false);
      translate([1.483252, 1.483252, 0.548158])
      rotate([45, 45, 45])
      cube(size = [1.289784, 1.289784, 1.289784], center = false);
    }
  }
  translate([4.514245, 0.000000, 0.000000])
  rotate([0, 10, 5])
  union() {
    cube(size = [3.224460, 3.224460, 3.224460], center = false);
    translate([0.000000, 0.000000, 2.579568])
    rotate([10, 0, 15])
    cube(size = [2.579568, 2.579568, 2.579568], center = false);
    translate([0.000000, 0.000000, 4.514245])
    rotate([0, 10, 20])
    cube(size = [1.934676, 1.934676, 1.934676], center = false);
  }
  translate([0.000000, -6.448921, 0.000000])
  rotate([20, 30, 40])
  union() {
    translate([0.644892, 0.644892, 0.967338])
    cube(size = [1.934676, 1.934676, 1.934676], center = false);
    difference() {
      cube(size = [3.224460, 3.224460, 3.224460], center = false);
      translate([0.322446, 0.322446, 0.322446])
      cube(size = [2.579568, 2.579568, 3.869353], center = false);
    }
  }
}
