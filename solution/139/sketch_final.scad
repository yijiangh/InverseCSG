intersection() {
  translate([0, 0, -0.0005])
  cube(size = [11.998, 9.062, 1.849], center = true);

  union() {
    translate([3.192, 0.718, 0.37])
    cube(size = [0.424, 2.072, 0.8], center = true);
  
    translate([-0.0795, 3.245, 0.1595])
    cube(size = [3.243, 0.424, 1.221], center = true);
  
    difference() {
      translate([4.679, 3.46, 0.0005])
      cylinder(h = 1.541, r1 = 0.319, r2 = 0.319, center = true, $fn = 12);
    
      translate([4.681, 3.456, 0])
      rotate([180, 0, 180])
      cylinder(h = 36.199, r1 = 0.148, r2 = 0.148, center = true, $fn = 12);
    }
  
    difference() {
      union() {
        translate([0.346, -1.2215, 0.37])
        cube(size = [2.392, 1.801, 0.8], center = true);
      
        translate([4.468, 1.5695, 0.0005])
        cube(size = [0.424, 3.775, 1.541], center = true);
      
        translate([1.915, -0.57, 0.37])
        cube(size = [0.424, 3.104, 0.8], center = true);
      
        translate([0.346, 1.3565, 0.0005])
        cube(size = [2.392, 3.349, 1.541], center = true);
      
        translate([3.112, 1.9885, -0.4005])
        cube(size = [3.136, 2.935, 0.739], center = true);
      }
    
      union() {
        translate([1.8345, 1.915, -0.4005])
        cube(size = [5.69, 0.637, 0.74], center = true);
      
        translate([3.83, 1.5695, -9.276])
        cube(size = [0.531, 3.776, 17.647], center = true);
      
        translate([2.553, 2.008, 0.0005])
        cube(size = [3.403, 2.047, 1.542], center = true);
      
        translate([1.1965, -1.223, 0.356])
        rotate([180, 90, -180])
        cylinder(h = 4.414, r1 = 0.158, r2 = 0.158, center = true, $fn = 12);
      
        translate([4.681, 3.456, 0])
        rotate([180, 0, 180])
        cylinder(h = 36.199, r1 = 0.148, r2 = 0.148, center = true, $fn = 12);
      
        translate([0, 2.607, 8.6645])
        cylinder(h = 18.87, r1 = 0.148, r2 = 0.148, center = true, $fn = 12);
      
        translate([0.558, -8.1725, 8.6645])
        cube(size = [1.977, 19.854, 18.87], center = true);
      }
    }
  
    difference() {
      union() {
        translate([-3.1915, -0.638, -0.4005])
        cube(size = [2.977, 4.466, 0.739], center = true);
      
        difference() {
          translate([-3.1915, -0.8505, 0.37])
          cube(size = [2.977, 5.211, 0.8], center = true);
        
          translate([6.7095, -1.223, 0.356])
          rotate([180, 90, -180])
          cylinder(h = 22.78, r1 = 0.158, r2 = 0.158, center = true, $fn = 12);
        }
      }
    
      union() {
        translate([-2.5535, -0.5855, -8.6645])
        cube(size = [0.85, 4.68, 18.87], center = true);
      
        translate([-3.8295, -0.5855, 8.6645])
        cube(size = [0.85, 4.68, 18.87], center = true);
      
        translate([-9.821, -0.638, -9.0655])
        cube(size = [16.557, 0.637, 18.068], center = true);
      
        translate([-4.681, -3.457, 9.0345])
        cylinder(h = 18.13, r1 = 0.148, r2 = 0.148, center = true, $fn = 12);
      }
    }
  
    difference() {
      difference() {
        union() {
          translate([1.2765, -1.9145, -0.4005])
          cube(size = [4.253, 1.913, 0.739], center = true);
        
          translate([1.2765, -1.623, 0.37])
          cube(size = [4.253, 2.604, 0.8], center = true);
        }
      
        translate([0.002, -2.5, -0.0005])
        rotate([180, 0, 180])
        cylinder(h = 1.542, r1 = 0.149, r2 = 0.149, center = true, $fn = 12);
      }
    
      union() {
        translate([-0.0005, 7.988, 0.0005])
        cube(size = [0.85, 20.221, 1.542], center = true);
      
        translate([2.5535, 7.3215, 0])
        cube(size = [0.85, 21.556, 36.199], center = true);
      
        translate([-6.9225, -1.223, 0.356])
        rotate([180, 90, -180])
        cylinder(h = 22.354, r1 = 0.158, r2 = 0.158, center = true, $fn = 12);
      
        translate([1.2765, 7.5865, 8.6645])
        cube(size = [0.85, 21.024, 18.87], center = true);
      }
    }
  
    translate([0.639, 1.1375, 0.37])
    cube(size = [0.424, 1.233, 0.8], center = true);
  
    translate([1.915, 1.37, 0.37])
    cube(size = [0.424, 0.77, 0.8], center = true);
  
    difference() {
      union() {
        translate([1.2765, 2.606, 0.37])
        cube(size = [5.955, 1.7, 0.8], center = true);
      
        translate([2.846, 0.7515, 0.1595])
        cube(size = [3.668, 0.461, 1.221], center = true);
      
        translate([-0.0005, 3.245, 0.0005])
        cube(size = [2.019, 0.424, 1.541], center = true);
      
        translate([2.553, 0.6385, -0.4005])
        cube(size = [1.7, 1.913, 0.739], center = true);
      }
    
      union() {
        translate([2.553, 2.606, 0.356])
        rotate([180, 90, -90])
        cylinder(h = 1.701, r1 = 0.153, r2 = 0.153, center = true, $fn = 12);
      
        intersection() {
          translate([2.5535, 0.6385, 0.0005])
          cube(size = [0.85, 1.914, 1.542], center = true);
        
          translate([1.1965, 0.9575, -0.4005])
          cube(size = [4.414, 2.552, 0.74], center = true);
        }
      
        translate([-6.9225, 2.6065, 0.0005])
        cube(size = [22.354, 0.85, 1.542], center = true);
      }
    }
  
    translate([-0.0005, 0.7515, 0.0005])
    cube(size = [2.019, 0.461, 1.541], center = true);
  
    difference() {
      union() {
        difference() {
          translate([-4.679, -3.458, 0.0005])
          cylinder(h = 1.541, r1 = 0.319, r2 = 0.319, center = true, $fn = 12);
        
          translate([-4.681, -3.457, 0])
          cylinder(h = 36.199, r1 = 0.148, r2 = 0.148, center = true, $fn = 12);
        }
      
        translate([-3.1915, 1.968, 0.37])
        cube(size = [2.977, 0.424, 0.8], center = true);
      
        translate([-2.5535, 0.7515, 0.0005])
        cube(size = [2.019, 0.461, 1.541], center = true);
      
        translate([-4.3885, -0.944, 0.0005])
        cube(size = [0.583, 3.854, 1.541], center = true);
      
        translate([-4.468, -0.346, 0.37])
        cube(size = [0.424, 5.158, 0.8], center = true);
      
        translate([-2.261, -1.2365, 0.1595])
        cube(size = [3.668, 4.439, 1.221], center = true);
      
        translate([-4.468, 2.633, 0.0005])
        cube(size = [0.424, 0.796, 1.541], center = true);
      }
    
      union() {
        translate([6.7095, -1.203, 8.6645])
        cube(size = [22.78, 3.445, 18.87], center = true);
      
        translate([0, -1.468, -0.4005])
        cube(size = [36.199, 3.977, 0.74], center = true);
      
        translate([-2.554, 1.8885, 0.356])
        rotate([180, 90, -90])
        cylinder(h = 0.584, r1 = 0.158, r2 = 0.158, center = true, $fn = 12);
      }
    }
  
    difference() {
      union() {
        translate([-4.682, 3.457, 0.0005])
        cylinder(h = 1.541, r1 = 0.318, r2 = 0.318, center = true, $fn = 12);
      
        translate([-3.112, 3.245, 0.0005])
        cube(size = [3.136, 0.424, 1.541], center = true);
      }
    
      union() {
        translate([-3.83, 0.0005, -9.276])
        cube(size = [0.531, 6.914, 17.647], center = true);
      
        translate([-2.554, 9.542, 0.356])
        rotate([180, 90, -90])
        cylinder(h = 17.115, r1 = 0.158, r2 = 0.158, center = true, $fn = 12);
      
        translate([-4.682, 3.457, 8.6645])
        rotate([180, 0, 180])
        cylinder(h = 18.87, r1 = 0.148, r2 = 0.148, center = true, $fn = 12);
      }
    }
  
    difference() {
      difference() {
        union() {
          translate([1.915, -1.888, 0.0005])
          cube(size = [5.53, 3.136, 1.541], center = true);
        
          translate([4.681, -3.458, -0.0005])
          rotate([180, 0, 180])
          cylinder(h = 1.541, r1 = 0.319, r2 = 0.319, center = true, $fn = 12);
        }
      
        union() {
          translate([1.9145, -1.623, 0.0005])
          cube(size = [4.68, 2.615, 1.542], center = true);
        
          translate([0, -1.223, 0.356])
          rotate([180, 90, -180])
          cylinder(h = 36.199, r1 = 0.158, r2 = 0.158, center = true, $fn = 12);
        }
      }
    
      union() {
        translate([4.681, -3.459, 0.0005])
        cylinder(h = 1.542, r1 = 0.149, r2 = 0.149, center = true, $fn = 12);
      
        translate([1.915, -3.1645, -0.4005])
        cube(size = [5.531, 0.584, 0.74], center = true);
      
        translate([1.915, -0.638, -0.4005])
        cube(size = [5.531, 0.637, 0.74], center = true);
      }
    }
  
    translate([0.639, 0.6385, 0.0005])
    cube(size = [0.424, 1.913, 1.541], center = true);
  }
}
