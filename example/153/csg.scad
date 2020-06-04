height = 4;
width = 6;
length = 8;
round_height = 0.5;
res = 30;
screw_size = 0.5;

module my_cube(s, c) {
  translate(c)
  cube(s, center = true);
}

module round_cylinder(c) {
  translate(c)
  rotate([90, 0, 0])
  cylinder(h = width, r = round_height, center = true, $fn = res);
}

module screw(c, r = [0, 0, 0]) {
  translate(c)
  rotate(r)
  difference() {
    my_cube([2 * round_height, 2 * round_height, 2 * round_height], [0, 0, 0]);
    
    union() {
      my_cube([round_height, 3 * round_height, round_height], [0, 0, 0.5 * round_height]);
      {
        translate([-0.15 * round_height, -round_height, 0.01])
        rotate([0, 30, 0])
        cube(size = [0.58 * round_height, 2 * round_height, 0.4 * round_height], center = true);
      }
      mirror([1, 0, 0])
      {
        translate([-0.15 * round_height, -round_height, 0.01])
        rotate([0, 30, 0])
        cube(size = [0.58 * round_height, 2 * round_height, 0.4 * round_height], center = true);
      }
    }
  }
}

module outer_board(y_offset) {
  translate([0, y_offset, 0])
  union() {
    my_cube([length * 0.8, round_height * 1, height * 0.8]);
    my_cube([length * 0.8, round_height * 3, height * 0.8 - round_height * 2]);
    
    translate([0, 0.5 * round_height, height * 0.4 - round_height])
    rotate([0, 90, 0])
    cylinder(h = length * 0.8, r = round_height, center = true, $fn = res);

    translate([0, 0.5 * round_height, -height * 0.4 + round_height])
    rotate([0, 90, 0])
    cylinder(h = length * 0.8, r = round_height, center = true, $fn = res);
    
    translate([-length * 0.2, 0, 0])
    union() {
      rotate([90, 0, 0])
      cylinder(h = 7 * round_height, r = round_height * 0.4, center = true, $fn = res);

      translate([0, 2 * round_height, 0])
      rotate([90, 0, 0])
      cylinder(h = 0.5 * round_height, r = 4 * round_height, center = true, $fn = res * 3);
    
      translate([0, 2.5 * round_height, 0])
      rotate([90, 0, 0])
      cylinder(h = 0.6 * round_height, r = 1.5 * round_height, center = true, $fn = res);
    }
  }
}

module board(y_offset, z_offset) {
  translate([-1.5 * round_height, y_offset, z_offset])
  difference() {
    union() {
      my_cube([length + 3.5 * round_height, round_height,   height / 2 + 3 * round_height], [0.75 * round_height, 0, 0]);

      screw([length / 4, -0.5 * round_height, height / 2 - 1.5 * round_height]);
      screw([-length / 4, -0.5 * round_height, height / 2 - 1.5 * round_height]);
      
      screw([-length / 2, -0.5 * round_height, -0.5 * round_height], [0, -90, 0]);
    }

    union() {
      translate([length / 4, 0, height / 2 - 1.25 * round_height])
      rotate([90, 0, 0])
      cylinder(h = 10, r = 0.3 * round_height, center = true, $fn = res);
      
      translate([-length / 4, 0, height / 2 - 1.25 * round_height])
      rotate([90, 0, 0])
      cylinder(h = 10, r = 0.3 * round_height, center = true, $fn = res);
      
      translate([-length / 2 - 0.25 * round_height, -0.5 * round_height, -0.5 * round_height])
      rotate([90, 0, 0])
      cylinder(h = 10, r = 0.3 * round_height, center = true, $fn = res);
      
      translate([length / 2 + 2.5 * round_height, 0, height / 4 + 1.5 * round_height])
      rotate([0, 30, 0])
      cube(size = [height / 2, round_height, height / 4], center = true);
      
      translate([-length / 2 - 1.5 * round_height, 0, height / 4 + 1.5 * round_height])
      rotate([0, -30, 0])
      cube(size = [height / 2, round_height, height / 4], center = true);
    }
  }
}

difference() {
union() {
my_cube([length * 0.6, width * 0.4, 6 * round_height], [0, 0, -height / 2]);
my_cube([length * 0.5, width * 0.5, 7 * round_height], [0, 0, -height / 2]);
  
my_cube([length, width, height], [0, 0, 0]);
  
round_cylinder([length / 2, 0, height / 2]);
round_cylinder([length / 2, 0, -height / 2]);
round_cylinder([-length / 2, 0, height / 2]);
round_cylinder([-length / 2, 0, -height / 2]);

my_cube([length, width, 2 * round_height], [0, 0, height / 2]);
my_cube([length, width, 2 * round_height], [0, 0, -height / 2]);
my_cube([2 * round_height, width, height], [length / 2, 0, 0]);
my_cube([2 * round_height, width, height], [-length / 2, 0, 0]);

board(width / 2, height / 2 - round_height);
mirror([0, 0, 1])
board(width / 2, height / 2 - round_height);
  
mirror([0, 1, 0]){
board(width / 2, height / 2 - round_height);
mirror([0, 0, 1])
board(width / 2, height / 2 - round_height);
}

outer_board(width / 2 + round_height);
mirror([0, 1, 0])
outer_board(width / 2 + round_height);
}

translate([-length * 0.2, -width * 0.1, height / 2 + 1.5 * round_height])
union() {
my_cube([length * 0.3, width * 0.4, round_height * 2], [0, 0, 0]);
translate([length * 0.15, width * 0.2, 0])
cylinder(h = round_height * 2, r = 0.5 * round_height, center = true, $fn = res);
translate([length * 0.15, -width * 0.2, 0])
cylinder(h = round_height * 2, r = 0.5 * round_height, center = true, $fn = res);
translate([-length * 0.15, width * 0.2, 0])
cylinder(h = round_height * 2, r = 0.5 * round_height, center = true, $fn = res);
translate([-length * 0.15, -width * 0.2, 0])
cylinder(h = round_height * 2, r = 0.5 * round_height, center = true, $fn = res);
  
my_cube([round_height, width * 0.4, round_height * 2], [length * 0.15, 0, 0]);
my_cube([round_height, width * 0.4, round_height * 2], [-length * 0.15, 0, 0]);
my_cube([length * 0.3, round_height, round_height * 2], [0, width * 0.2, 0]);
my_cube([length * 0.3, round_height, round_height * 2], [0, -width * 0.2, 0]);
}

}