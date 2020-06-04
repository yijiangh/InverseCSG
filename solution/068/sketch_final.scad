intersection() {
  translate([-0.0005, 0, 0])
  cube(size = [9.071, 11.998, 3.144], center = true);

  union() {
    difference() {
      intersection() {
        union() {
          difference() {
            translate([-1.868, -3.23547, -9.4005])
            rotate([0, 0, -30])
            cube(size = [36.198, 0.736, 17.397], center = true);
          
            translate([-10.146, 6.55, 0])
            cube(size = [15.907, 23.099, 36.199], center = true);
          }
        
          difference() {
            translate([7.1605, 6.55, 0])
            cube(size = [21.879, 23.098, 36.198], center = true);
          
            translate([-1.067, -4.236, -9.5225])
            cylinder(h = 17.254, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
          }
        }
      
        union() {
          difference() {
            translate([-3.938, 6.82082, -1.006])
            rotate([-180, 0, 30])
            cube(size = [36.198, 20.446, 0.608], center = true);
          
            translate([3.69975, 6.40815, 0])
            rotate([0, 0, -30])
            cube(size = [36.199, 21.4, 36.199], center = true);
          }
        
          translate([-5.55125, -9.61505, -1.006])
          rotate([0, 0, -30])
          cube(size = [36.198, 13.993, 0.608], center = true);
        }
      }
    
      union() {
        translate([5.112, -8.85424, -0.823])
        rotate([-180, 0, 30])
        cube(size = [36.199, 15.751, 0.243], center = true);
      
        translate([-1.066, -3.994, -1.128])
        cylinder(h = 0.365, r1 = 0.275, r2 = 0.275, center = true, $fn = 12);
      
        intersection() {
          translate([-2.866, 0, -9.4005])
          cube(size = [1.347, 36.199, 17.398], center = true);
        
          union() {
            translate([-4.139, 7.16896, -1.006])
            rotate([-180, 0, 30])
            cube(size = [36.199, 19.643, 0.609], center = true);
          
            translate([-2.575, -4.46003, 8.3945])
            rotate([0, 0, -30])
            cube(size = [36.199, 0.737, 19.41], center = true);
          }
        
          translate([0.7885, -1.36572, -9.4005])
          rotate([-180, 0, 30])
          cube(size = [36.199, 1.541, 17.398], center = true);
        }
      
        translate([-3.2455, 6.55, -9.7055])
        cube(size = [0.588, 23.099, 16.788], center = true);
      }
    }
  
    intersection() {
      translate([-1.067, -1.335, 0])
      cylinder(h = 36.198, r1 = 0.275, r2 = 0.275, center = true, $fn = 12);
    
      translate([0, 0, -9.4005])
      rotate([0, 0, -30])
      cube(size = [36.198, 36.198, 17.397], center = true);
    
      union() {
        sphere(r = 54.298, $fn = 108);
      
        translate([-1.067, -1.334, 0])
        cylinder(h = 36.198, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
      }
    
      translate([-1.069, -1.094, 8.6995])
      cylinder(h = 18.799, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
    }
  
    intersection() {
      difference() {
        translate([-7.547, 3.262, 8.623])
        cube(size = [21.104, 0.608, 18.952], center = true);
      
        translate([-7.5003, 4.15748, 8.623])
        rotate([0, 0, -29])
        cube(size = [19.048, 36.199, 18.953], center = true);
      }
    
      translate([3.007, 4.378, -1.128])
      cylinder(h = 0.364, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
    
      translate([3.007, 1.463, 8.6995])
      cylinder(h = 18.799, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
    
      sphere(r = 54.298, $fn = 108);
    }
  
    difference() {
      intersection() {
        union() {
          translate([4.3235, 7.48852, -1.006])
          rotate([0, 0, -30])
          cube(size = [36.198, 18.904, 0.608], center = true);
        
          translate([5.55125, -9.61505, -9.5225])
          rotate([-180, 0, 30])
          cube(size = [36.198, 13.993, 17.153], center = true);
        
          difference() {
            translate([2.986, 6.55, -0.823])
            cube(size = [1.586, 23.098, 0.242], center = true);
          
            translate([3.171, -4.117, 0])
            cylinder(h = 36.199, r1 = 0.183, r2 = 0.183, center = true, $fn = 12);
          }
        }
      
        translate([2.986, 6.55, 8.3945])
        cube(size = [1.586, 23.098, 19.409], center = true);
      
        translate([5.16575, -8.94734, -1.006])
        rotate([-180, 0, 30])
        cube(size = [36.198, 15.535, 0.608], center = true);
      }
    
      intersection() {
        translate([2.866, 0, -1.006])
        cube(size = [1.347, 36.199, 0.609], center = true);
      
        union() {
          translate([2.2215, -3.84775, 0])
          rotate([-180, 0, 30])
          cube(size = [36.199, 2.151, 36.199], center = true);
        
          translate([0.1195, 0.20698, 0])
          rotate([0, 0, -30])
          cube(size = [36.199, 0.737, 36.199], center = true);
        }
      
        union() {
          translate([3.17, -1.554, 0])
          cylinder(h = 36.199, r1 = 0.182, r2 = 0.182, center = true, $fn = 12);
        
          translate([2.561, -2.836, 0])
          cylinder(h = 36.199, r1 = 0.183, r2 = 0.183, center = true, $fn = 12);
        
          difference() {
            translate([3.938, 6.82082, -9.5225])
            rotate([0, 0, -30])
            cube(size = [36.199, 20.447, 17.154], center = true);
          
            translate([2.0205, -3.49961, -1.128])
            rotate([-180, 0, 30])
            cube(size = [36.2, 1.48, 0.366], center = true);
          }
        }
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([-5.35025, -9.2669, 8.3945])
          rotate([0, 0, -30])
          cube(size = [36.198, 14.797, 19.409], center = true);
        
          translate([4.911, -8.5061, -9.4005])
          rotate([-180, 0, 30])
          cube(size = [36.199, 16.555, 17.398], center = true);
        }
      
        difference() {
          difference() {
            translate([4.911, -8.5061, 8.3945])
            rotate([-180, 0, 30])
            cube(size = [36.198, 16.554, 19.409], center = true);
          
            translate([-3.171, -4.116, 0])
            cylinder(h = 36.199, r1 = 0.183, r2 = 0.183, center = true, $fn = 12);
          }
        
          union() {
            translate([-2.876, 6.55, -1.128])
            cube(size = [0.147, 23.099, 0.365], center = true);
          
            translate([7.954, 0, 8.5775])
            cube(size = [20.291, 36.199, 19.144], center = true);
          }
        }
      }
    
      union() {
        difference() {
          difference() {
            translate([7.575, 6.55, -1.006])
            cube(size = [21.048, 23.098, 0.608], center = true);
          
            translate([7.954, 6.55, -1.128])
            cube(size = [20.291, 23.099, 0.365], center = true);
          }
        
          union() {
            translate([-2.561, -2.835, 8.3945])
            cylinder(h = 19.41, r1 = 0.182, r2 = 0.182, center = true, $fn = 12);
          
            translate([-1.868, -3.23547, -9.5225])
            rotate([0, 0, -30])
            cube(size = [36.199, 0.737, 17.154], center = true);
          }
        }
      
        difference() {
          translate([-3.365, 6.55, -1.006])
          cube(size = [0.828, 23.098, 0.608], center = true);
        
          difference() {
            translate([-3.365, 6.55, -1.128])
            cube(size = [0.829, 23.099, 0.365], center = true);
          
            translate([0.604, -1.04616, -1.128])
            rotate([-180, 0, 30])
            cube(size = [36.2, 0.804, 0.366], center = true);
          }
        }
      }
    }
  
    difference() {
      union() {
        translate([-13.6914, 3.73522, -0.884])
        rotate([-180, 0, 30])
        cube(size = [16.219, 16.037, 0.364], center = true);
      
        translate([7.806, -9.212, -0.823])
        cube(size = [20.586, 17.774, 0.242], center = true);
      
        translate([-9.13366, -4.15904, -1.006])
        rotate([-180, 0, 30])
        cube(size = [16.219, 0.712, 0.608], center = true);
      
        translate([-3.006, 1.463, -1.128])
        cylinder(h = 0.364, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      }
    
      union() {
        translate([4.373, -7.57426, -0.823])
        rotate([-180, 0, 30])
        cube(size = [36.199, 18.707, 0.243], center = true);
      
        translate([-3.006, 1.463, 8.5775])
        cylinder(h = 19.044, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      
        translate([-3.007, 1.464, 0])
        cylinder(h = 36.199, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
      
        translate([-10.9405, 0, -1.006])
        cube(size = [14.318, 36.199, 0.609], center = true);
      }
    }
  
    intersection() {
      translate([-7.42771, 4.11725, 0])
      rotate([0, 0, -29])
      cube(size = [19.213, 36.198, 36.198], center = true);
    
      difference() {
        difference() {
          intersection() {
            translate([5.112, -8.85424, -0.823])
            rotate([-180, 0, 30])
            cube(size = [36.198, 15.75, 0.242], center = true);
          
            sphere(r = 54.298, $fn = 108);
          }
        
          union() {
            translate([-1.066, -4.237, 8.5775])
            cylinder(h = 19.044, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
          
            translate([0, -11.55, 8.3945])
            cube(size = [36.199, 13.099, 19.41], center = true);
          }
        }
      
        translate([-1.069, -3.994, -9.4005])
        cylinder(h = 17.398, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
      }
    }
  
    difference() {
      difference() {
        difference() {
          difference() {
            translate([7.1605, -6.55, -1.006])
            cube(size = [21.879, 23.098, 0.608], center = true);
          
            translate([-3.007, 1.464, -9.477])
            cylinder(h = 17.245, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
          }
        
          union() {
            translate([7.1605, -7.5715, -0.823])
            cube(size = [21.88, 21.056, 0.343], center = true);
          
            translate([-3.365, 3.262, -0.9305])
            cube(size = [0.829, 0.609, 0.456], center = true);
          }
        }
      
        union() {
          translate([-3.006, 4.38, -1.0825])
          cylinder(h = 0.456, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
        
          translate([0.823, 4.38, -0.823])
          cylinder(h = 0.243, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
        
          translate([-0.824, 4.378, -9.5225])
          cylinder(h = 17.154, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
        }
      }
    
      union() {
        translate([-4.5575, -7.89382, -1.128])
        rotate([0, 0, -30])
        cube(size = [36.199, 17.969, 0.365], center = true);
      
        translate([-3.007, 4.378, -0.823])
        cylinder(h = 0.243, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
      
        translate([0.825, 1.466, -9.5225])
        cylinder(h = 17.154, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      
        translate([-0.823, 4.377, -0.823])
        cylinder(h = 0.253, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
      
        translate([0.823, 4.378, -1.006])
        cylinder(h = 0.609, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
      
        translate([3.006, 4.378, 0])
        cylinder(h = 36.199, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      
        translate([-0.823, 1.463, -1.128])
        cylinder(h = 0.365, r1 = 0.273, r2 = 0.273, center = true, $fn = 12);
      
        translate([8.33032, -4.61757, -9.4005])
        rotate([0, 0, -29])
        cube(size = [17.15, 36.199, 17.398], center = true);
      }
    }
  
    difference() {
      intersection() {
        union() {
          difference() {
            translate([0.67325, -1.1661, 8.3945])
            rotate([-180, 0, 30])
            cube(size = [36.198, 2.431, 19.409], center = true);
          
            translate([-1.067, -1.334, -0.823])
            cylinder(h = 0.243, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
          }
        
          intersection() {
            translate([-1.067, -1.335, 0])
            cylinder(h = 36.198, r1 = 0.275, r2 = 0.275, center = true, $fn = 12);
          
            translate([1.068, -1.094, -1.128])
            cylinder(h = 0.364, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
          }
        }
      
        union() {
          translate([1.067, -1.334, -0.823])
          cylinder(h = 0.242, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
        
          difference() {
            translate([-0.85775, -1.48567, -1.006])
            rotate([0, 0, -30])
            cube(size = [36.198, 3.169, 0.608], center = true);
          
            translate([1.067, -1.092, -0.823])
            cylinder(h = 0.243, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
          }
        }
      }
    
      union() {
        translate([1.067, -1.334, -9.4005])
        cylinder(h = 17.398, r1 = 0.273, r2 = 0.273, center = true, $fn = 12);
      
        translate([-1.069, -1.094, -9.4005])
        cylinder(h = 17.398, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
      
        translate([1.067, -1.334, 8.5775])
        cylinder(h = 19.044, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
      
        translate([-1.067, -1.335, 0])
        cylinder(h = 36.199, r1 = 0.275, r2 = 0.275, center = true, $fn = 12);
      
        translate([-4.4925, 7.78124, 8.6995])
        rotate([-180, 0, 30])
        cube(size = [36.199, 18.229, 18.8], center = true);
      
        intersection() {
          translate([-1.063, -1.089, 8.5775])
          cylinder(h = 19.044, r1 = 0.406, r2 = 0.406, center = true, $fn = 12);
        
          sphere(r = 54.299, $fn = 108);
        }
      
        translate([1.068, -1.094, -9.4005])
        cylinder(h = 17.398, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
      }
    }
  
    difference() {
      difference() {
        union() {
          difference() {
            translate([7.806, -9.37, -1.128])
            cube(size = [20.586, 17.458, 0.364], center = true);
          
            translate([4.75998, -7.92194, 8.3945])
            rotate([-180, 0, 31])
            cube(size = [36.199, 17.715, 19.41], center = true);
          }
        
          translate([7.806, -0.454, 0.305])
          cube(size = [20.586, 0.37, 2.01], center = true);
        
          translate([7.806, 8.73, -1.006])
          cube(size = [20.586, 18.738, 0.608], center = true);
        }
      
        union() {
          translate([0.011, 8.73, 1.309])
          rotate([180, 90, -90])
          cylinder(h = 18.739, r1 = 0.974, r2 = 0.974, center = true, $fn = 12);
        
          translate([2.92717, 12.065, -9.4005])
          rotate([-180, 0, 30])
          cube(size = [19.064, 18.229, 17.398], center = true);
        
          translate([-1.069, -1.094, 0])
          cylinder(h = 36.199, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
        
          translate([7.806, -0.025, -9.4005])
          cube(size = [20.587, 1.229, 17.398], center = true);
        }
      }
    
      intersection() {
        difference() {
          difference() {
            translate([7.806, 8.73, 0])
            cube(size = [20.587, 18.739, 36.199], center = true);
          
            translate([0.011, 0.722, 1.309])
            rotate([180, 90, -90])
            cylinder(h = 0.264, r1 = 0.974, r2 = 0.974, center = true, $fn = 12);
          }
        
          union() {
            translate([3.32644, -8.60457, -8.791])
            rotate([-180, 0, 30])
            cube(size = [0.915, 17.97, 18.618], center = true);
          
            translate([-4.56221, 7.59279, 9.309])
            rotate([-180, 0, 31])
            cube(size = [36.2, 18.484, 17.582], center = true);
          }
        }
      
        difference() {
          union() {
            translate([7.806, 9.477, -9.5225])
            cube(size = [20.587, 17.245, 17.154], center = true);
          
            translate([7.0239, 4.05525, 8.3945])
            rotate([-180, 0, 30])
            cube(size = [19.978, 36.199, 19.41], center = true);
          }
        
          translate([-8.70052, 5.02325, 8.3945])
          rotate([0, 0, -30])
          cube(size = [16.107, 36.2, 19.411], center = true);
        }
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([-1.103, -1.91045, -0.823])
          rotate([0, 0, -30])
          cube(size = [36.198, 2.188, 0.242], center = true);
        
          translate([-3.171, -1.555, 0])
          cylinder(h = 36.199, r1 = 0.182, r2 = 0.182, center = true, $fn = 12);
        }
      
        translate([-3.6595, 0, -1.128])
        cube(size = [0.239, 36.198, 0.364], center = true);
      
        translate([-3.2905, 8.73, -9.5835])
        cube(size = [0.977, 18.738, 17.031], center = true);
      }
    
      difference() {
        union() {
          translate([-1.103, -1.91045, -1.128])
          rotate([0, 0, -30])
          cube(size = [36.198, 2.188, 0.364], center = true);
        
          translate([-2.986, 0, -0.823])
          cube(size = [1.586, 36.198, 0.242], center = true);
        }
      
        union() {
          translate([7.28, 8.888, 8.5775])
          cube(size = [21.639, 18.423, 19.044], center = true);
        
          translate([-3.171, 0.122, -1.128])
          cylinder(h = 0.365, r1 = 0.183, r2 = 0.183, center = true, $fn = 12);
        }
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([0.7135, -1.23582, -0.3965])
          rotate([-180, 0, 30])
          cube(size = [36.198, 0.736, 1.827], center = true);
        
          translate([1.067, -1.092, -8.791])
          cylinder(h = 18.617, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
        }
      
        intersection() {
          translate([8.73045, -4.83937, -1.006])
          rotate([0, 0, -29])
          cube(size = [16.234, 36.198, 0.608], center = true);
        
          translate([-3.88425, 6.72772, -9.4005])
          rotate([-180, 0, 30])
          cube(size = [36.198, 20.661, 17.397], center = true);
        }
      }
    
      union() {
        translate([-7.794, -0.454, -0.091])
        cube(size = [20.61, 0.37, 1.218], center = true);
      
        translate([-4.2605, 7.3794, -9.4005])
        rotate([-180, 0, 30])
        cube(size = [36.198, 19.156, 17.397], center = true);
      
        translate([-7.794, -0.454, -1.006])
        cube(size = [20.61, 0.37, 0.608], center = true);
      
        translate([1.08975, -1.8875, -0.3965])
        rotate([-180, 0, 30])
        cube(size = [36.198, 0.765, 1.827], center = true);
      
        difference() {
          union() {
            translate([-3.88425, 6.72772, -0.884])
            rotate([-180, 0, 30])
            cube(size = [36.198, 20.661, 0.364], center = true);
          
            translate([-6.8942, -4.14245, -1.006])
            rotate([-180, 0, 31])
            cube(size = [20.112, 36.198, 0.608], center = true);
          }
        
          union() {
            translate([-7.42771, 4.11725, -9.4005])
            rotate([0, 0, -29])
            cube(size = [19.214, 36.199, 17.398], center = true);
          
            translate([-7.28, 0.107, -0.3965])
            cube(size = [21.639, 1.493, 1.828], center = true);
          }
        }
      }
    
      difference() {
        difference() {
          translate([-7.1595, -8.623, -0.3965])
          cube(size = [21.879, 18.952, 1.827], center = true);
        
          translate([1.067, -1.334, 0])
          cylinder(h = 36.199, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
        }
      
        translate([8.62053, 5.17974, -0.092])
        rotate([-180, 0, 31])
        cube(size = [16.085, 36.199, 1.219], center = true);
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([4.75998, -7.92194, 9.309])
          rotate([-180, 0, 31])
          cube(size = [36.198, 17.714, 17.58], center = true);
        
          translate([1.708, 0.183, 0])
          cylinder(h = 36.199, r1 = 0.259, r2 = 0.259, center = true, $fn = 12);
        }
      
        difference() {
          intersection() {
            translate([4.5575, -7.89382, 8.6995])
            rotate([-180, 0, 30])
            cube(size = [36.198, 17.968, 18.799], center = true);
          
            translate([-7.794, -8.623, 8.5165])
            cube(size = [20.61, 18.952, 19.165], center = true);
          }
        
          difference() {
            translate([-7.794, 0.161, 8.5775])
            cube(size = [20.611, 0.857, 19.044], center = true);
          
            translate([-7.5003, 4.15748, -0.091])
            rotate([0, 0, -29])
            cube(size = [19.049, 36.2, 1.22], center = true);
          }
        }
      
        difference() {
          translate([-2.52637, -12.3, -0.3965])
          rotate([-180, 0, 31])
          cube(size = [19.197, 17.714, 1.827], center = true);
        
          translate([1.067, -1.334, 8.3945])
          cylinder(h = 19.41, r1 = 0.273, r2 = 0.273, center = true, $fn = 12);
        }
      }
    
      union() {
        difference() {
          translate([-7.794, 0.293, 0.9145])
          cube(size = [20.61, 1.12, 0.791], center = true);
        
          translate([0.012, 0.161, 1.309])
          rotate([180, 90, -90])
          cylinder(h = 0.857, r1 = 0.73, r2 = 0.73, center = true, $fn = 12);
        }
      
        translate([4.86875, 8.43292, -0.2135])
        rotate([0, 0, -30])
        cube(size = [36.198, 16.723, 1.461], center = true);
      
        difference() {
          union() {
            translate([-7.794, -0.025, 0])
            cube(size = [20.61, 1.228, 2.62], center = true);
          
            translate([1.067, -1.092, -1.128])
            cylinder(h = 0.364, r1 = 0.413, r2 = 0.413, center = true, $fn = 12);
          }
        
          union() {
            translate([0.011, -0.025, 1.309])
            rotate([180, 90, -90])
            cylinder(h = 1.229, r1 = 0.974, r2 = 0.974, center = true, $fn = 12);
          
            translate([1.068, -1.094, 8.3945])
            cylinder(h = 19.41, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
          }
        }
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([-7.1595, 8.916, -8.791])
          cube(size = [21.879, 18.366, 18.616], center = true);
        
          translate([3.17, 0.183, -9.4005])
          cylinder(h = 17.398, r1 = 0.183, r2 = 0.183, center = true, $fn = 12);
        }
      
        translate([-7.794, -8.623, -9.5835])
        cube(size = [20.61, 18.952, 17.031], center = true);
      
        translate([3.146, -9.184, -9.4005])
        cube(size = [1.266, 17.83, 17.397], center = true);
      }
    
      union() {
        difference() {
          translate([8.62053, 5.17974, -8.791])
          rotate([-180, 0, 31])
          cube(size = [16.084, 36.198, 18.616], center = true);
        
          union() {
            translate([3.006, 1.463, 0])
            cylinder(h = 36.199, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
          
            translate([-7.42771, 4.11725, -1.006])
            rotate([0, 0, -29])
            cube(size = [19.214, 36.199, 0.609], center = true);
          }
        }
      
        translate([8.73045, -4.83937, -8.791])
        rotate([0, 0, -29])
        cube(size = [16.234, 36.198, 18.616], center = true);
      }
    
      union() {
        difference() {
          translate([0.7135, -1.23582, -1.006])
          rotate([-180, 0, 30])
          cube(size = [36.198, 0.736, 0.608], center = true);
        
          translate([4.86875, 8.43292, -0.884])
          rotate([0, 0, -30])
          cube(size = [36.199, 16.724, 0.365], center = true);
        }
      
        translate([-7.794, 0.107, -0.091])
        cube(size = [20.61, 1.492, 1.218], center = true);
      
        translate([-7.649, 8.73, -1.006])
        cube(size = [20.9, 18.738, 0.608], center = true);
      }
    }
  
    intersection() {
      difference() {
        translate([-7.1595, 10.5285, -1.006])
        cube(size = [21.879, 15.141, 0.608], center = true);
      
        union() {
          translate([-7.1595, 3.262, 8.47])
          cube(size = [21.88, 0.609, 19.257], center = true);
        
          translate([-7.5003, 4.15748, 8.3945])
          rotate([0, 0, -29])
          cube(size = [19.048, 36.199, 19.41], center = true);
        }
      }
    
      union() {
        sphere(r = 54.298, $fn = 108);
      
        translate([0, 0, 8.5775])
        rotate([0, 0, -30])
        cube(size = [36.198, 36.198, 19.043], center = true);
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([-7.794, 9.345, -1.006])
          cube(size = [20.61, 17.508, 0.608], center = true);
        
          translate([-7.5003, 4.15748, -9.4005])
          rotate([0, 0, -29])
          cube(size = [19.048, 36.199, 17.398], center = true);
        }
      
        difference() {
          translate([0.825, 1.466, -9.5225])
          cylinder(h = 17.153, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
        
          translate([0.823, 1.463, -9.5225])
          cylinder(h = 17.154, r1 = 0.275, r2 = 0.275, center = true, $fn = 12);
        }
      }
    
      difference() {
        intersection() {
          translate([0, 9.345, -1.006])
          cube(size = [36.198, 17.508, 0.608], center = true);
        
          translate([-4.56221, 7.59279, -9.4005])
          rotate([-180, 0, 31])
          cube(size = [36.198, 18.482, 17.397], center = true);
        }
      
        difference() {
          translate([8.35043, -4.62872, -1.189])
          rotate([0, 0, -29])
          cube(size = [17.104, 36.199, 0.243], center = true);
        
          translate([4.86875, 8.43292, -1.189])
          rotate([0, 0, -30])
          cube(size = [36.2, 16.725, 0.244], center = true);
        }
      }
    }
  
    intersection() {
      difference() {
        difference() {
          translate([5.05325, 8.75249, -1.006])
          rotate([0, 0, -30])
          cube(size = [36.198, 15.985, 0.608], center = true);
        
          translate([3.006, 1.463, -0.823])
          cylinder(h = 0.243, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
        }
      
        union() {
          translate([3.189, 3.262, -0.823])
          cube(size = [0.365, 0.609, 0.243], center = true);
        
          translate([3.5765, 3.262, -1.0825])
          cube(size = [0.408, 0.609, 0.456], center = true);
        }
      }
    
      difference() {
        translate([0, 0, 8.3945])
        rotate([0, 0, -29])
        cube(size = [36.198, 36.198, 19.409], center = true);
      
        union() {
          translate([3.189, 3.262, -1.0065])
          cube(size = [0.365, 0.609, 0.304], center = true);
        
          translate([3.007, 1.463, -1.0825])
          cylinder(h = 0.456, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
        }
      }
    
      difference() {
        union() {
          translate([3.006, 4.378, -9.5225])
          cylinder(h = 17.153, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
        
          translate([-7.1595, -7.2665, 8.3945])
          cube(size = [21.879, 21.665, 19.409], center = true);
        }
      
        union() {
          translate([3.007, 4.378, -1.006])
          cylinder(h = 0.609, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
        
          translate([10.9395, -7.2665, -0.823])
          cube(size = [14.318, 21.666, 0.243], center = true);
        }
      }
    }
  
    difference() {
      intersection() {
        union() {
          translate([7.37031, -4.25525, -9.7055])
          rotate([0, 0, -30])
          cube(size = [19.177, 36.198, 16.787], center = true);
        
          translate([7.806, -0.149, -8.791])
          cube(size = [20.586, 0.98, 18.616], center = true);
        
          difference() {
            translate([7.806, 0.293, -8.3945])
            cube(size = [20.586, 1.12, 19.409], center = true);
          
            translate([0.011, 9.22, 1.309])
            rotate([180, 90, -90])
            cylinder(h = 17.767, r1 = 0.974, r2 = 0.974, center = true, $fn = 12);
          }
        }
      
        difference() {
          difference() {
            translate([-4.56221, 7.59279, 1.11022e-15])
            rotate([-180, 0, 31])
            cube(size = [36.198, 18.482, 2.62], center = true);
          
            translate([-1.708, 0.122, 0.305])
            cylinder(h = 2.011, r1 = 0.258, r2 = 0.258, center = true, $fn = 12);
          }
        
          translate([0.012, -8.8795, 1.309])
          rotate([180, 90, -90])
          cylinder(h = 18.44, r1 = 0.73, r2 = 0.73, center = true, $fn = 12);
        }
      }
    
      union() {
        intersection() {
          translate([7.0239, 4.05525, 8.3945])
          rotate([-180, 0, 30])
          cube(size = [19.978, 36.199, 19.41], center = true);
        
          translate([-1.33065, 0.76825, 8.3945])
          rotate([0, 0, -30])
          cube(size = [0.914, 36.199, 19.41], center = true);
        
          difference() {
            translate([0, -8.755, -8.791])
            cube(size = [36.199, 18.689, 18.617], center = true);
          
            translate([7.41967, 4.28375, -8.791])
            rotate([-180, 0, 30])
            cube(size = [19.065, 36.2, 18.618], center = true);
          }
        }
      
        difference() {
          translate([7.806, 0.107, -8.791])
          cube(size = [20.587, 1.493, 18.617], center = true);
        
          union() {
            translate([-4.4925, 7.78124, 8.3945])
            rotate([-180, 0, 30])
            cube(size = [36.2, 18.23, 19.411], center = true);
          
            translate([0, 0.037, -0.091])
            cube(size = [36.2, 0.61, 1.22], center = true);
          }
        }
      }
    }
  
    intersection() {
      translate([-7.794, 0.722, 0.305])
      cube(size = [20.61, 0.262, 2.01], center = true);
    
      difference() {
        translate([8.22838, 4.94411, -0.092])
        rotate([-180, 0, 31])
        cube(size = [16.999, 36.198, 1.218], center = true);
      
        translate([8.40291, -4.65781, -0.091])
        rotate([0, 0, -29])
        cube(size = [16.984, 36.199, 1.219], center = true);
      }
    }
  
    difference() {
      intersection() {
        union() {
          difference() {
            translate([4.4925, 7.78124, 8.5775])
            rotate([0, 0, -30])
            cube(size = [36.198, 18.228, 19.043], center = true);
          
            translate([0.825, 1.466, 0])
            cylinder(h = 36.199, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
          }
        
          translate([4.4925, 7.78124, 8.6995])
          rotate([0, 0, -30])
          cube(size = [36.198, 18.228, 18.799], center = true);
        }
      
        translate([7.1605, -7.2665, -0.9305])
        cube(size = [21.879, 21.665, 0.455], center = true);
      }
    
      union() {
        translate([7.1605, 3.262, -1.0065])
        cube(size = [21.88, 0.609, 0.304], center = true);
      
        translate([-0.823, 1.464, -0.823])
        cylinder(h = 0.243, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      
        translate([8.33032, -4.61757, 8.3945])
        rotate([0, 0, -29])
        cube(size = [17.15, 36.199, 19.41], center = true);
      
        translate([-3.006, 1.463, 8.5775])
        cylinder(h = 19.044, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      
        translate([-3.1425, 10.5285, -0.778])
        cube(size = [0.384, 15.142, 0.151], center = true);
      }
    }
  
    difference() {
      intersection() {
        translate([3.32975, 5.7673, -9.5225])
        rotate([0, 0, -30])
        cube(size = [36.198, 22.879, 17.153], center = true);
      
        union() {
          translate([-1.069, -3.994, -1.128])
          cylinder(h = 0.364, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
        
          intersection() {
            translate([5.112, -8.85424, 0])
            rotate([-180, 0, 30])
            cube(size = [36.198, 15.75, 36.198], center = true);
          
            translate([-7.42771, 4.11725, 8.3945])
            rotate([0, 0, -29])
            cube(size = [19.213, 36.198, 19.409], center = true);
          }
        
          translate([-1.066, -4.237, 8.3945])
          cylinder(h = 19.409, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
        }
      }
    
      union() {
        translate([-1.067, -4.236, -1.006])
        cylinder(h = 0.609, r1 = 0.276, r2 = 0.276, center = true, $fn = 12);
      
        translate([-1.066, -3.994, 8.3945])
        cylinder(h = 19.41, r1 = 0.275, r2 = 0.275, center = true, $fn = 12);
      
        translate([-1.066, -4.237, 8.6995])
        cylinder(h = 18.8, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      }
    }
  
    difference() {
      union() {
        intersection() {
          difference() {
            translate([-7.649, 6.55, -9.4005])
            cube(size = [20.9, 23.098, 17.397], center = true);
          
            translate([1.068, -3.994, 0])
            cylinder(h = 36.199, r1 = 0.274, r2 = 0.274, center = true, $fn = 12);
          }
        
          union() {
            translate([-4.911, -8.5061, 8.3945])
            rotate([0, 0, -30])
            cube(size = [36.198, 16.554, 19.409], center = true);
          
            translate([1.4825, -2.56777, -1.006])
            rotate([-180, 0, 30])
            cube(size = [36.198, 0.802, 0.608], center = true);
          }
        }
      
        intersection() {
          difference() {
            translate([-0.604, -1.04616, -1.006])
            rotate([0, 0, -30])
            cube(size = [36.198, 0.802, 0.608], center = true);
          
            translate([2.561, 6.55, 8.3945])
            cube(size = [0.737, 23.099, 19.41], center = true);
          }
        
          union() {
            translate([1.8515, -3.20689, -1.006])
            rotate([-180, 0, 30])
            cube(size = [36.198, 0.802, 0.608], center = true);
          
            translate([-7.1595, 0, -1.128])
            cube(size = [21.879, 36.198, 0.364], center = true);
          }
        }
      }
    
      union() {
        translate([1.065, -3.994, 8.5775])
        cylinder(h = 19.044, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
      
        translate([1.068, -4.238, -0.823])
        cylinder(h = 0.243, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
      
        translate([-1.069, -3.994, 8.5775])
        cylinder(h = 19.044, r1 = 0.412, r2 = 0.412, center = true, $fn = 12);
      
        translate([-1.066, -4.237, 0])
        cylinder(h = 36.199, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
      
        translate([-7.42771, 4.11725, -1.006])
        rotate([0, 0, -29])
        cube(size = [19.214, 36.199, 0.609], center = true);
      
        translate([1.064, -4.237, -9.4005])
        cylinder(h = 17.398, r1 = 0.273, r2 = 0.273, center = true, $fn = 12);
      
        translate([1.067, -1.334, -9.5225])
        cylinder(h = 17.154, r1 = 0.273, r2 = 0.273, center = true, $fn = 12);
      }
    }
  
    intersection() {
      difference() {
        union() {
          difference() {
            translate([7.806, 8.73, -0.091])
            cube(size = [20.586, 18.738, 1.218], center = true);
          
            translate([0.011, 8.73, 1.309])
            rotate([180, 90, -90])
            cylinder(h = 18.739, r1 = 0.974, r2 = 0.974, center = true, $fn = 12);
          }
        
          difference() {
            translate([7.1605, 0, -1.006])
            cube(size = [21.879, 36.198, 0.608], center = true);
          
            translate([5.05325, 8.75249, -9.4005])
            rotate([0, 0, -30])
            cube(size = [36.199, 15.986, 17.398], center = true);
          }
        }
      
        union() {
          translate([7.954, 8.888, -8.791])
          cube(size = [20.291, 18.423, 18.617], center = true);
        
          translate([4.75998, -7.92194, 8.3945])
          rotate([-180, 0, 31])
          cube(size = [36.199, 17.715, 19.41], center = true);
        
          translate([-3.006, 1.463, 0])
          cylinder(h = 36.199, r1 = 0.411, r2 = 0.411, center = true, $fn = 12);
        }
      }
    
      union() {
        translate([-3.6595, -9.212, -0.2135])
        cube(size = [0.239, 17.774, 1.461], center = true);
      
        difference() {
          translate([7.649, 0, -1.006])
          cube(size = [20.9, 36.198, 0.608], center = true);
        
          translate([-1.063, -1.089, 8.3945])
          cylinder(h = 19.41, r1 = 0.406, r2 = 0.406, center = true, $fn = 12);
        }
      
        translate([-1.103, -1.91045, -9.4005])
        rotate([0, 0, -30])
        cube(size = [36.198, 0.712, 17.397], center = true);
      
        difference() {
          translate([-8.65116, -4.99475, -0.3965])
          rotate([-180, 0, 30])
          cube(size = [16.219, 36.198, 1.827], center = true);
        
          translate([-1.103, -1.91045, -9.4005])
          rotate([0, 0, -30])
          cube(size = [36.199, 2.189, 17.398], center = true);
        }
      
        translate([11.2184, -3.20984, -0.092])
        rotate([-180, 0, 30])
        cube(size = [19.977, 19.42, 1.218], center = true);
      }
    }
  }
}
