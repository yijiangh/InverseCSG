intersection() {
  translate([0, -0.0005, -0.0005])
  cube(size = [11.998, 11.491, 4.723], center = true);

  union() {
    intersection() {
      translate([-0.114434, 0.0238884, 1.48277])
      rotate([-0, 89, -89])
      cylinder(h = 36.198, r1 = 2.733, r2 = 2.733, center = true, $fn = 12);
    
      translate([7.196, -3.6645, -1.2855])
      cube(size = [21.806, 1.451, 0.371], center = true);
    }
  
    difference() {
      difference() {
        translate([3.8915, -0.7205, 8.0655])
        cube(size = [2.215, 8.135, 20.067], center = true);
      
        translate([3.2455, -3.052, 0.2365])
        cube(size = [0.924, 2.677, 2.67], center = true);
      }
    
      difference() {
        difference() {
          difference() {
            translate([1.1085, 6.6555, 8.0655])
            cube(size = [7.782, 22.888, 20.068], center = true);
          
            translate([-7.196, -3.052, -1.0995])
            cube(size = [21.808, 2.678, 1.739], center = true);
          }
        
          union() {
            translate([4.171, -4.554, 0.0495])
            cylinder(h = 3.043, r1 = 0.228, r2 = 0.228, center = true, $fn = 12);
          
            translate([3.452, -4.528, -8.2645])
            cylinder(h = 19.671, r1 = 0.261, r2 = 0.261, center = true, $fn = 12);
          }
        }
      
        union() {
          translate([4.148, -1.694, 0.0495])
          cylinder(h = 3.043, r1 = 0.256, r2 = 0.256, center = true, $fn = 12);
        
          translate([3.9295, -3.1145, 0.6705])
          cube(size = [0.443, 3.349, 1.801], center = true);
        
          translate([11.4135, -0.702, 1.515])
          rotate([180, 90, 180])
          cylinder(h = 13.373, r1 = 0.453, r2 = 0.453, center = true, $fn = 12);
        
          translate([3.8085, -3.1145, -0.851])
          cube(size = [0.687, 3.349, 1.242], center = true);
        }
      }
    }
  
    translate([-3.47, -4.552, -1.534])
    cylinder(h = 0.868, r1 = 0.233, r2 = 0.233, center = true, $fn = 12);
  
    intersection() {
      union() {
        translate([0.3405, 3.3105, -1.7205])
        cube(size = [6.245, 0.669, 0.495], center = true);
      
        translate([3.8085, -7.376, 8.0655])
        cube(size = [0.685, 21.446, 20.067], center = true);
      }
    
      union() {
        translate([3.5865, 1.9595, -9.5995])
        cube(size = [0.241, 3.371, 16.999], center = true);
      
        translate([0.4625, 3.3105, -9.165])
        cube(size = [6.489, 0.669, 17.868], center = true);
      }
    }
  
    difference() {
      translate([-3.2455, -3.8635, -1.534])
      cube(size = [0.923, 1.849, 0.868], center = true);
    
      translate([-3.572, -11.327, -1.7205])
      cube(size = [0.271, 13.545, 0.496], center = true);
    }
  
    translate([-4.056, -3.746, 0.0495])
    cube(size = [0.694, 1.614, 3.041], center = true);
  
    translate([-3.469, -4.59, 0.0495])
    cube(size = [1.372, 0.396, 3.041], center = true);
  
    difference() {
      union() {
        translate([-4.2805, -1.577, -1.348])
        cube(size = [0.245, 0.272, 1.24], center = true);
      
        translate([-3.458, 3.397, -1.534])
        cylinder(h = 0.868, r1 = 0.249, r2 = 0.249, center = true, $fn = 12);
      
        translate([-3.1095, 1.103, -1.534])
        cube(size = [0.651, 5.084, 0.868], center = true);
      
        intersection() {
          union() {
            translate([7.196, -1.3325, 8.0655])
            cube(size = [21.806, 3.209, 20.067], center = true);
          
            translate([-11.1285, 0.0185, 8.935])
            cube(size = [13.941, 5.911, 18.328], center = true);
          }
        
          union() {
            translate([-4.8635, -0.702, 1.515])
            rotate([180, 90, 180])
            cylinder(h = 0.271, r1 = 0.453, r2 = 0.453, center = true, $fn = 12);
          
            translate([-3.602, -0.701, -1.0995])
            rotate([180, 0, 180])
            cylinder(h = 1.737, r1 = 0.992, r2 = 0.992, center = true, $fn = 12);
          }
        }
      
        translate([-3.7955, 3.497, 0.0495])
        cube(size = [0.719, 0.296, 3.041], center = true);
      }
    
      union() {
        difference() {
          difference() {
            translate([-3.92, -0.7205, -1.348])
            cube(size = [0.967, 1.986, 1.241], center = true);
          
            translate([-3.436, -1.714, -1.7205])
            cylinder(h = 0.497, r1 = 0.285, r2 = 0.285, center = true, $fn = 12);
          }
        
          union() {
            translate([-3.7955, -0.7205, 0.0495])
            cube(size = [0.721, 1.987, 3.043], center = true);
          
            translate([-4.157, -1.687, 8.314])
            cylinder(h = 19.572, r1 = 0.246, r2 = 0.246, center = true, $fn = 12);
          }
        }
      
        translate([-3.606, -0.701, -1.0995])
        rotate([180, 0, 180])
        cylinder(h = 1.738, r1 = 0.747, r2 = 0.747, center = true, $fn = 12);
      }
    }
  
    intersection() {
      union() {
        translate([3.45, 0.294, -1.7205])
        cylinder(h = 0.495, r1 = 0.264, r2 = 0.264, center = true, $fn = 12);
      
        translate([4.151, 0.293, 0.0495])
        cylinder(h = 3.041, r1 = 0.257, r2 = 0.257, center = true, $fn = 12);
      
        difference() {
          translate([0.684, 4.068, 0.0495])
          cube(size = [6.932, 1.438, 3.041], center = true);
        
          translate([0.002, -6.656, 1.56])
          rotate([180, 90, -90])
          cylinder(h = 22.887, r1 = 1.483, r2 = 1.483, center = true, $fn = 12);
        }
      }
    
      union() {
        translate([-6.848, 1.841, -9.165])
        cube(size = [22.502, 3.608, 17.868], center = true);
      
        intersection() {
          translate([-0.001, 4.068, 1.568])
          rotate([180, 90, -90])
          cylinder(h = 1.438, r1 = 2.107, r2 = 2.107, center = true, $fn = 12);
        
          translate([0.004, 3.07, 1.571])
          sphere(r = 2.611, $fn = 12);
        }
      
        translate([-0.004, 1.418, 1.584])
        sphere(r = 3.429, $fn = 12);
      }
    }
  
    intersection() {
      union() {
        translate([0.684, -8.9135, -1.0995])
        cube(size = [6.932, 18.371, 1.737], center = true);
      
        translate([3.465, 3.397, -9.786])
        cylinder(h = 16.626, r1 = 0.244, r2 = 0.244, center = true, $fn = 12);
      }
    
      union() {
        translate([10.7825, 0.1545, 0.0495])
        cube(size = [14.633, 0.235, 3.041], center = true);
      
        translate([-7.196, 1.9595, -0.199])
        cube(size = [21.806, 3.371, 3.538], center = true);
      }
    }
  
    difference() {
      union() {
        translate([-3.2455, 0.0185, -1.534])
        cube(size = [0.923, 5.911, 0.868], center = true);
      
        translate([-3.606, -0.701, 0.422])
        rotate([180, 0, 180])
        cylinder(h = 2.296, r1 = 0.747, r2 = 0.747, center = true, $fn = 12);
      
        translate([-3.469, 3.3105, -0.199])
        cube(size = [1.372, 0.669, 3.538], center = true);
      
        translate([-4.156, 3.396, 0.0495])
        rotate([180, 0, 180])
        cylinder(h = 3.041, r1 = 0.248, r2 = 0.248, center = true, $fn = 12);
      
        translate([-4.056, 0.205, 0.0495])
        cube(size = [0.694, 6.284, 3.041], center = true);
      
        translate([-4.354, -0.702, 1.125])
        rotate([180, 90, 180])
        cylinder(h = 1.29, r1 = 0.448, r2 = 0.448, center = true, $fn = 12);
      }
    
      union() {
        difference() {
          translate([-3.2455, -0.5835, -1.348])
          cube(size = [0.924, 1.712, 1.241], center = true);
        
          translate([-3.451, 0.286, -9.5995])
          cylinder(h = 17.001, r1 = 0.257, r2 = 0.257, center = true, $fn = 12);
        }
      
        translate([-3.604, -0.702, 8.6865])
        rotate([180, 0, 180])
        cylinder(h = 18.826, r1 = 0.428, r2 = 0.428, center = true, $fn = 12);
      
        translate([-10.904, -0.702, -1.348])
        cube(size = [14.391, 1.475, 1.241], center = true);
      
        difference() {
          union() {
            translate([-4.2805, -0.7205, -1.348])
            cube(size = [0.246, 1.986, 1.241], center = true);
          
            translate([-3.92, 8.193, -1.7205])
            cube(size = [0.967, 19.813, 0.496], center = true);
          }
        
          union() {
            translate([-3.2455, 1.692, -1.534])
            cube(size = [0.925, 3.312, 0.87], center = true);
          
            translate([-4.162, 0.273, -1.348])
            cylinder(h = 1.242, r1 = 0.237, r2 = 0.237, center = true, $fn = 12);
          }
        }
      }
    }
  
    difference() {
      union() {
        difference() {
          translate([0.3405, 1.841, 0.0495])
          cube(size = [6.245, 3.608, 3.041], center = true);
        
          translate([0.001, 2.412, 1.561])
          rotate([180, 90, -90])
          cylinder(h = 4.751, r1 = 1.958, r2 = 1.958, center = true, $fn = 12);
        }
      
        translate([3.8085, 3.3105, 0.0495])
        cube(size = [0.685, 0.669, 3.041], center = true);
      
        translate([4.164, 3.407, 0.0495])
        cylinder(h = 3.041, r1 = 0.236, r2 = 0.236, center = true, $fn = 12);
      
        translate([4.056, 1.8105, 0.0495])
        cube(size = [0.694, 3.073, 3.041], center = true);
      }
    
      translate([0.3405, 1.5055, 0.0495])
      cube(size = [6.246, 2.938, 3.042], center = true);
    }
  
    difference() {
      union() {
        translate([4.056, -0.603, 0.0495])
        cube(size = [0.694, 7.9, 3.041], center = true);
      
        translate([4.2325, -0.702, 1.125])
        rotate([180, 90, 180])
        cylinder(h = 1.533, r1 = 0.448, r2 = 0.448, center = true, $fn = 12);
      
        difference() {
          translate([0.3405, -3.8635, -0.199])
          cube(size = [6.245, 1.849, 3.538], center = true);
        
          translate([-7.196, -3.6645, -0.664])
          cube(size = [21.807, 1.452, 0.869], center = true);
        }
      
        translate([0.4625, -0.7205, 0.6705])
        cube(size = [6.489, 8.135, 1.799], center = true);
      
        translate([3.5935, 0.817, -1.534])
        cube(size = [1.619, 5.06, 0.868], center = true);
      
        translate([3.603, -0.704, -1.0995])
        rotate([180, 0, 180])
        cylinder(h = 1.737, r1 = 0.994, r2 = 0.994, center = true, $fn = 12);
      }
    
      union() {
        difference() {
          translate([10.7825, 0.817, -9.4135])
          cube(size = [14.634, 5.061, 17.372], center = true);
        
          translate([3.451, -1.694, 8.0655])
          cylinder(h = 20.069, r1 = 0.26, r2 = 0.26, center = true, $fn = 12);
        }
      
        translate([3.605, -0.703, -9.4135])
        cylinder(h = 17.372, r1 = 0.747, r2 = 0.747, center = true, $fn = 12);
      
        difference() {
          translate([-7.196, 6.8545, 8.935])
          cube(size = [21.807, 22.49, 18.329], center = true);
        
          translate([3.605, -0.703, 0.422])
          cylinder(h = 2.298, r1 = 0.747, r2 = 0.747, center = true, $fn = 12);
        }
      
        translate([-0.114434, 0.0238884, 1.48277])
        rotate([-0, 89, -89])
        cylinder(h = 36.199, r1 = 2.733, r2 = 2.733, center = true, $fn = 12);
      
        translate([3.603, -0.701, -8.2645])
        rotate([180, 0, 180])
        cylinder(h = 19.67, r1 = 0.428, r2 = 0.428, center = true, $fn = 12);
      
        translate([11.252, -0.5215, -1.0995])
        cube(size = [13.695, 7.738, 1.738], center = true);
      }
    }
  
    translate([-4.139, -4.525, 0.0495])
    rotate([180, 0, 180])
    cylinder(h = 3.041, r1 = 0.269, r2 = 0.269, center = true, $fn = 12);
  }
}
