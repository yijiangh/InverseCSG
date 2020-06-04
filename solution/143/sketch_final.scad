intersection() {
  translate([0, 0, 0.0005])
  cube(size = [11.997, 4.085, 7.814], center = true);

  union() {
    difference() {
      intersection() {
        union() {
          translate([9.3435, 0.451, 2.919])
          rotate([-90, 0, 0])
          cube(size = [17.51, 0.673, 1.695], center = true);
        
          translate([2.2335, -9.249, 2.7165])
          rotate([-90, 0, 0])
          cube(size = [3.29, 0.554, 17.699], center = true);
        
          difference() {
            translate([3.2635, -0.02, 2.7875])
            rotate([-90, 0, 0])
            cube(size = [0.26, 0.412, 2.639], center = true);
          
            translate([3.2635, -1.393, 2.68])
            rotate([0, 90, 0])
            cylinder(h = 0.261, r1 = 0.328, r2 = 0.328, center = true, $fn = 12);
          }
        }
      
        union() {
          translate([-7.3525, -6.15069, -4.63488])
          rotate([37, 0, 0])
          cube(size = [21.492, 20.794, 36.197], center = true);
        
          translate([3.558, 0.315, 2.8475])
          cylinder(h = 0.816, r1 = 0.736, r2 = 0.736, center = true, $fn = 12);
        }
      
        translate([0, 8.3795, 10.3405])
        rotate([-90, 0, 0])
        cube(size = [36.197, 15.516, 19.438], center = true);
      }
    
      union() {
        translate([1.185, 0.322, -7.4215])
        rotate([180, 0, 180])
        cylinder(h = 21.355, r1 = 0.097, r2 = 0.097, center = true, $fn = 12);
      
        translate([3.441, 0.322, 10.3405])
        cylinder(h = 15.517, r1 = 0.188, r2 = 0.188, center = true, $fn = 12);
      
        translate([0.698, 0.323, 10.269])
        cylinder(h = 15.66, r1 = 0.188, r2 = 0.188, center = true, $fn = 12);
      
        translate([3.132, -9.7205, 2.196])
        rotate([180, 90, -90])
        cylinder(h = 16.757, r1 = 0.377, r2 = 0.377, center = true, $fn = 12);
      
        intersection() {
          translate([-7.3525, -1.24048, -11.1509])
          rotate([37, 0, 0])
          cube(size = [21.493, 20.795, 19.88], center = true);
        
          translate([-7.484, -0.02, 3.126])
          rotate([-90, 0, 0])
          cube(size = [21.23, 0.26, 2.64], center = true);
        }
      
        translate([2.071, 0.324, -7.4215])
        cylinder(h = 21.355, r1 = 0.189, r2 = 0.189, center = true, $fn = 12);
      
        translate([2.955, 0.323, 0])
        cylinder(h = 36.198, r1 = 0.098, r2 = 0.098, center = true, $fn = 12);
      }
    }
  
    intersection() {
      difference() {
        union() {
          translate([-1.783, -0.157, -10.4685])
          cube(size = [4.191, 3.089, 15.26], center = true);
        
          translate([-3.926, -1.286, -3.047])
          cylinder(h = 0.417, r1 = 0.418, r2 = 0.418, center = true, $fn = 12);
        
          translate([-4.038, 0.024, -10.2245])
          cube(size = [0.611, 2.727, 15.748], center = true);
        }
      
        union() {
          difference() {
            translate([-4.146, -0.157, -2.9835])
            cube(size = [0.396, 3.09, 0.545], center = true);
          
            translate([-3.93, -0.157, -2.84])
            rotate([180, 90, -90])
            cylinder(h = 3.091, r1 = 0.416, r2 = 0.416, center = true, $fn = 12);
          }
        
          translate([-3.6255, 0.719, 7.6315])
          cube(size = [0.209, 1.338, 20.935], center = true);
        }
      }
    
      difference() {
        union() {
          translate([-8.893, -0.3665, -2.9835])
          cube(size = [18.411, 2.67, 0.544], center = true);
        
          translate([0, 1.121, -2.937])
          rotate([0, 90, 0])
          cylinder(h = 36.197, r1 = 0.318, r2 = 0.318, center = true, $fn = 12);
        
          translate([-10.99, -0.157, -1.771])
          cube(size = [14.217, 3.089, 2.129], center = true);
        }
      
        union() {
          difference() {
            translate([-2.0155, -1.522, -1.981])
            cube(size = [4.657, 0.36, 2.55], center = true);
          
            translate([6.8775, -1.278, -2.831])
            rotate([180, 90, 180])
            cylinder(h = 22.444, r1 = 0.429, r2 = 0.429, center = true, $fn = 12);
          }
        
          translate([-3.731, 8.3795, -2.682])
          rotate([180, 90, -90])
          cylinder(h = 19.439, r1 = 0.158, r2 = 0.158, center = true, $fn = 12);
        }
      }
    }
  
    difference() {
      difference() {
        translate([0.587, 0.323, 2.919])
        cylinder(h = 0.673, r1 = 0.738, r2 = 0.738, center = true, $fn = 12);
      
        translate([0.698, 0.323, 0])
        cylinder(h = 36.198, r1 = 0.188, r2 = 0.188, center = true, $fn = 12);
      }
    
      union() {
        translate([1.822, 8.30461, 6.25797])
        rotate([37, 0, 0])
        cube(size = [2.62, 15.401, 36.198], center = true);
      
        translate([1.185, 0.322, 2.9515])
        rotate([180, 0, 180])
        cylinder(h = 0.609, r1 = 0.097, r2 = 0.097, center = true, $fn = 12);
      }
    }
  
    intersection() {
      difference() {
        difference() {
          union() {
            translate([1.202, -1.522, -2.803])
            cube(size = [3.859, 0.359, 0.905], center = true);
          
            translate([8.8795, 0.024, -3.047])
            cube(size = [18.438, 2.727, 0.417], center = true);
          }
        
          translate([-0.729, -1.522, -2.447])
          rotate([180, 90, -90])
          cylinder(h = 0.36, r1 = 0.386, r2 = 0.386, center = true, $fn = 12);
        }
      
        translate([0.717, -9.7205, -2.431])
        rotate([180, 90, -90])
        cylinder(h = 16.757, r1 = 0.406, r2 = 0.406, center = true, $fn = 12);
      }
    
      union() {
        translate([0.587, 0.323, -3.047])
        cylinder(h = 0.417, r1 = 0.738, r2 = 0.738, center = true, $fn = 12);
      
        translate([-0.207, -9.7205, -2.593])
        cube(size = [1.041, 16.756, 0.485], center = true);
      
        translate([0.4505, -1.278, -2.831])
        rotate([180, 90, 180])
        cylinder(h = 0.27, r1 = 0.429, r2 = 0.429, center = true, $fn = 12);
      
        translate([1.822, 0.87, -2.889])
        rotate([180, 90, 180])
        cylinder(h = 2.619, r1 = 0.43, r2 = 0.43, center = true, $fn = 12);
      
        translate([0.4505, -0.646, -3.047])
        cube(size = [0.27, 1.387, 0.417], center = true);
      
        translate([0.4125, 1.121, -2.937])
        rotate([0, 90, 0])
        cylinder(h = 0.194, r1 = 0.318, r2 = 0.318, center = true, $fn = 12);
      }
    }
  
    translate([-0.0135, -1.522, -1.427])
    cube(size = [0.652, 0.359, 1.841], center = true);
  
    difference() {
      union() {
        difference() {
          translate([-3.4375, 0.719, 2.7165])
          rotate([-90, 0, 0])
          cube(size = [0.882, 0.554, 1.337], center = true);
        
          translate([-2.618, 0.024, -7.7595])
          rotate([-90, 0, 0])
          cube(size = [2.522, 20.679, 2.728], center = true);
        }
      
        intersection() {
          translate([-4.038, -9.7205, -7.5525])
          rotate([-90, 0, 0])
          cube(size = [0.611, 21.092, 16.756], center = true);
        
          translate([-3.926, -1.286, -7.5525])
          cylinder(h = 21.092, r1 = 0.418, r2 = 0.418, center = true, $fn = 12);
        }
      
        translate([-2.1755, -0.827, 2.6135])
        rotate([-90, 0, 0])
        cube(size = [1.636, 0.062, 1.749], center = true);
      
        difference() {
          translate([-3.935, 0.024, 2.583])
          rotate([180, 90, -90])
          cylinder(h = 2.727, r1 = 0.415, r2 = 0.415, center = true, $fn = 12);
        
          translate([-3.7, -0.157, 2.4275])
          rotate([-90, 0, 0])
          cube(size = [0.358, 0.435, 3.09], center = true);
        }
      
        translate([-2.438, 0.719, 2.8205])
        rotate([-90, 0, 0])
        cube(size = [2.161, 0.346, 1.337], center = true);
      }
    
      union() {
        difference() {
          translate([-2.851, 1.1795, 10.373])
          rotate([-90, 0, 0])
          cube(size = [2.986, 15.452, 0.417], center = true);
        
          translate([-2.851, 1.111, 2.664])
          rotate([180, 90, 180])
          cylinder(h = 2.987, r1 = 0.332, r2 = 0.332, center = true, $fn = 12);
        }
      
        difference() {
          translate([-3.6705, -1.522, 2.8205])
          rotate([-90, 0, 0])
          cube(size = [1.347, 0.347, 0.36], center = true);
        
          intersection() {
            translate([-4.1125, -1.393, 2.68])
            rotate([0, 90, 0])
            cylinder(h = 0.464, r1 = 0.328, r2 = 0.328, center = true, $fn = 12);
          
            translate([-3.935, -1.522, 2.583])
            rotate([180, 90, -90])
            cylinder(h = 0.361, r1 = 0.415, r2 = 0.415, center = true, $fn = 12);
          }
        }
      
        translate([-2.21011, -0.00662302, 0.0258994])
        rotate([0, 1, 48])
        cylinder(h = 36.198, r1 = 0.826, r2 = 0.826, center = true, $fn = 12);
      
        translate([-10.9155, 6.4954, -6.72619])
        rotate([44, 0, 0])
        cube(size = [14.367, 36.198, 17.497], center = true);
      }
    }
  
    intersection() {
      translate([1.202, 8.1985, 2.8205])
      rotate([-90, 0, 0])
      cube(size = [3.859, 0.346, 19.8], center = true);
    
      union() {
        translate([8.8795, -1.393, 2.68])
        rotate([0, 90, 0])
        cylinder(h = 18.438, r1 = 0.328, r2 = 0.328, center = true, $fn = 12);
      
        translate([-0.5345, 8.3795, 0.9705])
        rotate([-90, 0, 0])
        cube(size = [0.386, 3.348, 19.438], center = true);
      }
    }
  
    intersection() {
      union() {
        translate([1.8595, -0.3665, -3.047])
        cube(size = [2.542, 2.67, 0.417], center = true);
      
        difference() {
          translate([3.937, 8.3795, -2.846])
          rotate([180, 90, -90])
          cylinder(h = 19.438, r1 = 0.405, r2 = 0.405, center = true, $fn = 12);
        
          translate([3.741, 8.1985, -2.71])
          rotate([0, 90, 90])
          cylinder(h = 19.801, r1 = 0.136, r2 = 0.136, center = true, $fn = 12);
        }
      
        translate([3.5055, -0.1855, -3.047])
        cube(size = [0.744, 2.308, 0.417], center = true);
      
        translate([3.924, -1.282, -0.136])
        cylinder(h = 5.145, r1 = 0.422, r2 = 0.422, center = true, $fn = 12);
      }
    
      difference() {
        union() {
          translate([1.8595, -1.278, -2.831])
          rotate([180, 90, 180])
          cylinder(h = 2.542, r1 = 0.429, r2 = 0.429, center = true, $fn = 12);
        
          translate([2.7935, 0.024, -10.405])
          cube(size = [4.41, 2.727, 15.387], center = true);
        
          translate([2.7935, -1.522, 7.6315])
          cube(size = [4.41, 0.359, 20.934], center = true);
        }
      
        difference() {
          union() {
            translate([10.616, 1.1795, 0])
            cube(size = [14.966, 0.417, 36.198], center = true);
          
            translate([3.6275, -0.3665, -0.1995])
            cube(size = [0.227, 2.671, 5.273], center = true);
          }
        
          difference() {
            translate([0, 1.121, -2.937])
            rotate([0, 90, 0])
            cylinder(h = 36.199, r1 = 0.318, r2 = 0.318, center = true, $fn = 12);
          
            translate([3.6275, 8.3795, -2.7735])
            cube(size = [0.229, 19.441, 0.127], center = true);
          }
        }
      }
    }
    difference() {
      union() {
        translate([-3.93, -0.1855, -2.84])
        rotate([180, 90, -90])
        cylinder(h = 2.308, r1 = 0.416, r2 = 0.416, center = true, $fn = 12);
      
        translate([-3.4715, -0.827, -1.771])
        cube(size = [0.948, 1.749, 2.129], center = true);
      
        translate([-4.146, 0.024, -1.771])
        cube(size = [0.395, 2.727, 2.129], center = true);
      
        translate([-3.926, -1.286, -1.771])
        cylinder(h = 2.129, r1 = 0.418, r2 = 0.418, center = true, $fn = 12);
      }
    
      union() {
        translate([-3.05773, -0.0248745, -2.51055])
        rotate([180, 87, -92])
        cylinder(h = 36.198, r1 = 0.419, r2 = 0.419, center = true, $fn = 12);
      
        translate([0, 0.049, -1.543])
        rotate([-180, 90, -180])
        cylinder(h = 36.198, r1 = 0.827, r2 = 0.827, center = true, $fn = 12);
      
        translate([-3.2575, -9.0255, 7.8755])
        cube(size = [0.523, 18.147, 20.447], center = true);
      
        translate([-1.783, 8.3795, -9.4025])
        cube(size = [4.192, 19.439, 17.393], center = true);
      }
    }
  
    intersection() {
      translate([0, -8.3555, 8.6975])
      cube(size = [36.197, 19.486, 18.802], center = true);
    
      union() {
        intersection() {
          union() {
            translate([6.55, -0.137, -0.129])
            rotate([180, 90, 180])
            cylinder(h = 23.097, r1 = 0.589, r2 = 0.589, center = true, $fn = 12);
          
            translate([-4.706, 9.0745, -0.111])
            cube(size = [0.193, 18.048, 0.783], center = true);
          }
        
          difference() {
            translate([-4.6725, -6.07791, 6.29386])
            rotate([44, 0, 0])
            cube(size = [0.652, 36.197, 18.698], center = true);
          
            translate([0, -0.136, -0.135])
            rotate([180, 90, 180])
            cylinder(h = 36.198, r1 = 0.172, r2 = 0.172, center = true, $fn = 12);
          }
        }
      
        translate([-4.1125, 6.4954, -6.72619])
        rotate([44, 0, 0])
        cube(size = [0.462, 36.197, 17.496], center = true);
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([-0.109, 0, 0])
          rotate([37, 0, 0])
          cube(size = [1.237, 36.197, 36.197], center = true);
        
          translate([-0.732, 8.1985, 2.186])
          rotate([180, 90, -90])
          cylinder(h = 19.801, r1 = 0.392, r2 = 0.392, center = true, $fn = 12);
        }
      
        translate([-1.0425, -9.7205, 2.7875])
        rotate([-90, 0, 0])
        cube(size = [0.624, 0.412, 16.756], center = true);
      }
    
      difference() {
        intersection() {
          translate([-0.4225, -1.393, 2.68])
          rotate([0, 90, 0])
          cylinder(h = 1.864, r1 = 0.328, r2 = 0.328, center = true, $fn = 12);
        
          sphere(r = 54.297, $fn = 108);
        }
      
        union() {
          translate([-0.109, 0.024, 1.145])
          rotate([-90, 0, 0])
          cube(size = [1.238, 3.698, 2.728], center = true);
        
          translate([0.713, -9.7205, 2.179])
          rotate([180, 90, -90])
          cylinder(h = 16.757, r1 = 0.401, r2 = 0.401, center = true, $fn = 12);
        }
      }
    }
    intersection() {
      difference() {
        difference() {
          translate([0.069, 0.024, 2.7875])
          rotate([-90, 0, 0])
          cube(size = [6.125, 0.412, 2.727], center = true);
        
          translate([-1.03387, -0.702298, -0.00928468])
          rotate([-0, 1, -81])
          cylinder(h = 36.198, r1 = 0.358, r2 = 0.358, center = true, $fn = 12);
        }
      
        union() {
          translate([-0.109, -9.7205, 2.8205])
          rotate([-90, 0, 0])
          cube(size = [1.238, 0.347, 16.757], center = true);
        
          translate([-2.21011, -0.00662302, 0.0258994])
          rotate([0, 1, 48])
          cylinder(h = 36.198, r1 = 0.826, r2 = 0.826, center = true, $fn = 12);
        }
      }
    
      union() {
        difference() {
          translate([-8.7945, -6.15069, -4.63488])
          rotate([37, 0, 0])
          cube(size = [18.608, 20.794, 36.197], center = true);
        
          translate([-2.1755, 8.1985, 0.9705])
          rotate([-90, 0, 0])
          cube(size = [1.637, 3.349, 19.801], center = true);
        }
      
        translate([-0.4225, 1.111, 2.664])
        rotate([180, 90, 180])
        cylinder(h = 1.864, r1 = 0.332, r2 = 0.332, center = true, $fn = 12);
      }
    }
    difference() {
      union() {
        difference() {
          difference() {
            translate([-4.8035, 0, 0])
            rotate([44, 0, 0])
            cube(size = [0.39, 36.197, 36.197], center = true);
          
            translate([-4.7715, 1.31, -0.124])
            rotate([180, 90, 180])
            cylinder(h = 0.325, r1 = 0.066, r2 = 0.066, center = true, $fn = 12);
          }
        
          union() {
            translate([-4.706, 9.7445, 8.798])
            cube(size = [0.194, 16.709, 18.602], center = true);
          
            translate([-4.902, 6.4954, -6.72619])
            rotate([44, 0, 0])
            cube(size = [0.194, 36.198, 17.497], center = true);
          }
        }
      
        difference() {
          translate([-4.706, 1.306, -0.112])
          rotate([180, 90, 180])
          cylinder(h = 0.193, r1 = 0.398, r2 = 0.398, center = true, $fn = 12);
        
          translate([0, 1.31, -0.124])
          rotate([180, 90, 180])
          cylinder(h = 36.198, r1 = 0.066, r2 = 0.066, center = true, $fn = 12);
        }
      
        translate([-4.476, -6.07791, 6.29386])
        rotate([44, 0, 0])
        cube(size = [0.259, 36.197, 18.698], center = true);
      
        translate([-4.8035, -8.3555, -9.4025])
        cube(size = [0.39, 19.486, 17.392], center = true);
      }
    
      difference() {
        union() {
          difference() {
            translate([-11.2225, 9.535, 0])
            cube(size = [13.753, 17.128, 36.198], center = true);
          
            translate([-4.706, 9.535, -0.111])
            cube(size = [0.185, 17.129, 0.775], center = true);
          }
        
          translate([-4.6725, -8.565, 0])
          cube(size = [0.653, 19.078, 36.198], center = true);
        }
      
        translate([-4.64, 0.5095, -0.111])
        cube(size = [0.589, 0.92, 0.785], center = true);
      }
    }
    intersection() {
      difference() {
        difference() {
          sphere(r = 54.297, $fn = 108);
        
          translate([0, -0.136, -0.135])
          rotate([180, 90, 180])
          cylinder(h = 36.198, r1 = 0.172, r2 = 0.172, center = true, $fn = 12);
        }
      
        union() {
          translate([1.921, -0.157, 0.769])
          rotate([180, 90, -90])
          cylinder(h = 3.09, r1 = 1.733, r2 = 1.733, center = true, $fn = 12);
        
          translate([3.5055, 0.024, -0.1995])
          cube(size = [0.745, 2.728, 5.273], center = true);
        }
      }
    
      union() {
        translate([4.44, 0.024, -0.1995])
        cube(size = [1.117, 2.727, 5.272], center = true);
      
        intersection() {
          translate([3.924, -1.282, -0.4095])
          cylinder(h = 5.692, r1 = 0.422, r2 = 0.422, center = true, $fn = 12);
        
          translate([3.937, -0.3665, -2.846])
          rotate([180, 90, -90])
          cylinder(h = 2.67, r1 = 0.405, r2 = 0.405, center = true, $fn = 12);
        }
      
        translate([2.164, -0.157, -0.4095])
        cube(size = [3.151, 3.089, 5.692], center = true);
      }
    
      union() {
        translate([10.616, -0.137, -0.129])
        rotate([180, 90, 180])
        cylinder(h = 14.965, r1 = 0.589, r2 = 0.589, center = true, $fn = 12);
      
        difference() {
          translate([3.7385, -1.278, -2.831])
          rotate([180, 90, 180])
          cylinder(h = 1.21, r1 = 0.429, r2 = 0.429, center = true, $fn = 12);
        
          translate([3.118, -8.565, -2.44])
          rotate([180, 90, -90])
          cylinder(h = 19.068, r1 = 0.395, r2 = 0.395, center = true, $fn = 12);
        }
      
        translate([3.6375, 1.121, -2.937])
        rotate([0, 90, 0])
        cylinder(h = 0.482, r1 = 0.318, r2 = 0.318, center = true, $fn = 12);
      
        translate([3.322, 0.87, -2.889])
        rotate([180, 90, 180])
        cylinder(h = 0.377, r1 = 0.43, r2 = 0.43, center = true, $fn = 12);
      
        difference() {
          translate([3.929, -0.157, 7.695])
          cube(size = [0.829, 3.089, 20.807], center = true);
        
          translate([0, -0.481, 1.031])
          rotate([180, 90, -180])
          cylinder(h = 36.198, r1 = 0.444, r2 = 0.444, center = true, $fn = 12);
        }
      }
    }
    difference() {
      difference() {
        union() {
          translate([1.822, 0.024, 2.8205])
          rotate([-90, 0, 0])
          cube(size = [2.619, 0.346, 2.727], center = true);
        
          translate([-0.0135, -1.522, 0.9705])
          rotate([-90, 0, 0])
          cube(size = [0.652, 3.348, 0.359], center = true);
        }
      
        union() {
          translate([3.558, 0.315, 0])
          cylinder(h = 36.198, r1 = 0.736, r2 = 0.736, center = true, $fn = 12);
        
          translate([0.587, 0.323, 1.145])
          cylinder(h = 3.698, r1 = 0.738, r2 = 0.738, center = true, $fn = 12);
        }
      }
    
      union() {
        translate([9.3055, 8.30461, 6.25797])
        rotate([37, 0, 0])
        cube(size = [17.587, 15.401, 36.198], center = true);
      
        translate([2.071, 0.324, 0])
        cylinder(h = 36.198, r1 = 0.189, r2 = 0.189, center = true, $fn = 12);
      
        translate([1.921, -0.157, 0.769])
        rotate([180, 90, -90])
        cylinder(h = 3.09, r1 = 1.733, r2 = 1.733, center = true, $fn = 12);
      }
    }
  
    intersection() {
      union() {
        translate([3.87, -0.02, -7.7595])
        rotate([-90, 0, 0])
        cube(size = [0.947, 20.678, 2.639], center = true);
      
        translate([3.87, -0.02, 2.7875])
        rotate([-90, 0, 0])
        cube(size = [0.947, 0.412, 2.639], center = true);
      
        translate([-6.8775, -1.393, 2.68])
        rotate([0, 90, 0])
        cylinder(h = 22.442, r1 = 0.328, r2 = 0.328, center = true, $fn = 12);
      
        translate([10.7475, 1.111, 2.664])
        rotate([180, 90, 180])
        cylinder(h = 14.702, r1 = 0.332, r2 = 0.332, center = true, $fn = 12);
      }
    
      union() {
        difference() {
          translate([3.5055, -9.7205, -7.7595])
          rotate([-90, 0, 0])
          cube(size = [0.744, 20.678, 16.756], center = true);
        
          translate([3.132, -9.7205, 2.196])
          rotate([180, 90, -90])
          cylinder(h = 16.757, r1 = 0.377, r2 = 0.377, center = true, $fn = 12);
        }
      
        intersection() {
          translate([3.5055, 1.111, 2.664])
          rotate([180, 90, 180])
          cylinder(h = 0.744, r1 = 0.332, r2 = 0.332, center = true, $fn = 12);
        
          translate([2.466, 8.851, 2.919])
          rotate([-90, 0, 0])
          cube(size = [3.755, 0.673, 18.495], center = true);
        }
      
        translate([2.2335, -9.249, 2.7875])
        rotate([-90, 0, 0])
        cube(size = [3.29, 0.412, 17.699], center = true);
      
        translate([4.1125, 8.3795, 2.5095])
        rotate([-90, 0, 0])
        cube(size = [0.462, 0.14, 19.438], center = true);
      
        difference() {
          translate([3.967, 0, 2.622])
          rotate([180, 90, -90])
          cylinder(h = 36.197, r1 = 0.368, r2 = 0.368, center = true, $fn = 12);
        
          translate([3.677, 8.3795, 2.392])
          rotate([-0, 90, -90])
          cylinder(h = 19.439, r1 = 0.221, r2 = 0.221, center = true, $fn = 12);
        }
      }
    
      union() {
        difference() {
          sphere(r = 54.297, $fn = 108);
        
          translate([4.1125, -9.7205, 2.7875])
          rotate([-90, 0, 0])
          cube(size = [0.463, 0.413, 16.757], center = true);
        }
      
        translate([3.924, -1.282, 0])
        cylinder(h = 36.197, r1 = 0.422, r2 = 0.422, center = true, $fn = 12);
      }
    }
  
    difference() {
      union() {
        translate([-3.4375, -0.646, 2.7165])
        rotate([-90, 0, 0])
        cube(size = [0.882, 0.554, 1.387], center = true);
      
        translate([-2.1755, -1.393, 2.68])
        rotate([0, 90, 0])
        cylinder(h = 1.636, r1 = 0.328, r2 = 0.328, center = true, $fn = 12);
      
        difference() {
          translate([-4.1125, 0.024, -7.727])
          rotate([-90, 0, 0])
          cube(size = [0.462, 20.743, 2.727], center = true);
        
          translate([-10.81, 0.049, -1.543])
          rotate([-180, 90, -180])
          cylinder(h = 14.578, r1 = 0.827, r2 = 0.827, center = true, $fn = 12);
        }
      
        translate([-3.8055, 0.719, 2.542])
        rotate([-90, 0, 0])
        cube(size = [0.146, 0.205, 1.337], center = true);
      
        translate([-3.4375, -1.522, -7.831])
        rotate([-90, 0, 0])
        cube(size = [0.882, 20.535, 0.359], center = true);
      
        translate([-3.4375, -1.393, 2.68])
        rotate([0, 90, 0])
        cylinder(h = 0.882, r1 = 0.328, r2 = 0.328, center = true, $fn = 12);
      }
    
      union() {
        translate([-3.2575, -1.522, -7.9455])
        rotate([-90, 0, 0])
        cube(size = [0.533, 20.307, 0.36], center = true);
      
        translate([-3.9325, 6.4954, -6.72619])
        rotate([44, 0, 0])
        cube(size = [0.823, 36.198, 17.497], center = true);
      
        translate([-3.363, -0.646, 2.5095])
        rotate([-90, 0, 0])
        cube(size = [0.734, 0.141, 1.388], center = true);
      
        translate([-3.144, -0.0385524, 2.20866])
        rotate([180, 89, 90])
        cylinder(h = 36.198, r1 = 0.378, r2 = 0.378, center = true, $fn = 12);
      
        translate([-3.24196, -0.769116, 0.0571566])
        rotate([1.20742e-06, 1, 24])
        cylinder(h = 36.198, r1 = 0.206, r2 = 0.206, center = true, $fn = 12);
      
        translate([0, -0.136, -0.135])
        rotate([180, 90, 180])
        cylinder(h = 36.198, r1 = 0.172, r2 = 0.172, center = true, $fn = 12);
      
        translate([-3.727, 0.024, 2.438])
        rotate([0, 90, 90])
        cylinder(h = 2.728, r1 = 0.148, r2 = 0.148, center = true, $fn = 12);
      
        translate([-2.1755, 8.1985, 2.395])
        rotate([-90, 0, 0])
        cube(size = [1.637, 0.37, 19.801], center = true);
      }
    }
  }
}
