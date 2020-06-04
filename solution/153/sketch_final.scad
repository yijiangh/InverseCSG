intersection() {
  translate([-0.0005, 0, 0])
  cube(size = [11.254, 11.997, 8.111], center = true);

  union() {
    difference() {
      translate([-3.119, -2.857, 1.572])
      cube(size = [2.949, 0.473, 1.521], center = true);
    
      translate([-4.238, -10.4095, 1.381])
      rotate([180, 90, -90])
      cylinder(h = 15.579, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
    }
  
    intersection() {
      union() {
        translate([1.1905, 0, -2.2855])
        cube(size = [0.33, 36.397, 1.426], center = true);
      
        translate([-1.67543, -8.695, 10.7921])
        rotate([90, 30, 0])
        cube(size = [22.703, 19.38, 19.007], center = true);
      
        difference() {
          translate([9.612, -0.9045, -2.1195])
          cube(size = [17.173, 3.426, 1.568], center = true);
        
          translate([1.79075, -2.381, -3.10167])
          rotate([-90, -30, 0])
          cube(size = [36.398, 1.605, 0.474], center = true);
        }
      }
    
      union() {
        translate([1.1905, -2.857, -9.7665])
        cube(size = [0.33, 0.473, 16.864], center = true);
      
        difference() {
          union() {
            translate([2.4045, -3.553, -0.835])
            rotate([180, 90, 180])
            cylinder(h = 2.092, r1 = 0.502, r2 = 0.502, center = true, $fn = 12);
          
            translate([-6.755, -2.381, -2.1665])
            cube(size = [22.887, 0.473, 1.664], center = true);
          }
        
          translate([10.1835, 7.7905, -10.195])
          cube(size = [16.031, 20.817, 16.008], center = true);
        }
      }
    }
  
    difference() {
      union() {
        translate([2.4765, -1.1425, 0.6195])
        cube(size = [4.426, 3.902, 3.902], center = true);
      
        translate([1.5955, -2.619, 1.024])
        cube(size = [1.14, 0.949, 4.711], center = true);
      
        intersection() {
          translate([-7.374, -3.324, 1.4285])
          cube(size = [21.649, 0.455, 0.568], center = true);
        
          translate([-0.16, -2.848, 0.277128])
          rotate([-90, -30, 0])
          cube(size = [36.397, 2.383, 1.407], center = true);
        }
      
        intersection() {
          difference() {
            translate([1.47925, -1.6185, 2.56214])
            rotate([90, 30, 0])
            cube(size = [36.397, 3.508, 4.854], center = true);
          
            translate([-8.969, 8.0285, 1.8575])
            cube(size = [18.46, 20.341, 1.427], center = true);
          }
        
          union() {
            translate([-6.755, -2.857, 1.262])
            cube(size = [22.887, 0.473, 4.045], center = true);
          
            translate([-7.374, -3.567, 1.237])
            rotate([180, 90, 180])
            cylinder(h = 21.649, r1 = 0.477, r2 = 0.477, center = true, $fn = 12);
          }
        }
      }
    
      intersection() {
        translate([0, 7.3235, 10.076])
        cube(size = [36.398, 21.751, 16.246], center = true);
      
        union() {
          translate([-8.969, -2.857, 2.976])
          cube(size = [18.46, 0.474, 0.808], center = true);
        
          intersection() {
            translate([-4.79863, -2.619, 7.28653])
            rotate([90, 30, 0])
            cube(size = [20.8, 1.604, 0.95], center = true);
          
            translate([1.595, -2.619, 2.976])
            cube(size = [0.474, 0.95, 0.808], center = true);
          }
        
          translate([13.8583, -0.9045, 3.20125])
          rotate([90, 30, 0])
          cube(size = [15.596, 16.995, 3.427], center = true);
        }
      }
    }
  
    difference() {
      union() {
        translate([0.1665, 3.0975, 0.9765])
        cube(size = [3.33, 0.954, 4.616], center = true);
      
        translate([0.1665, 2.429, 0.9045])
        cube(size = [3.33, 3.235, 3.33], center = true);
      
        translate([-1.119, 4.286, 0.19])
        rotate([180, 90, -90])
        cylinder(h = 0.235, r1 = 1.907, r2 = 1.907, center = true, $fn = 12);
      }
    
      union() {
        translate([0, 3.3355, 2.4995])
        cube(size = [36.398, 0.479, 1.579], center = true);
      
        translate([1.595, 10.4095, 2.929])
        rotate([180, 90, -90])
        cylinder(h = 15.579, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
      
        difference() {
          translate([0.1665, 3.8715, 9.6715])
          cube(size = [3.331, 0.599, 17.055], center = true);
        
          translate([0.1665, 3.576, 1.242])
          rotate([180, 90, 180])
          cylinder(h = 3.332, r1 = 0.468, r2 = 0.468, center = true, $fn = 12);
        }
      }
    }
  
    intersection() {
      union() {
        difference() {
          translate([1.762, 3.0955, 7.6])
          cube(size = [0.807, 1.902, 21.197], center = true);
        
          translate([1.595, 8.5285, -2.547])
          rotate([180, 90, -90])
          cylinder(h = 19.341, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
        }
      
        translate([2.81, 3.3335, 7.6475])
        cube(size = [1.273, 1.426, 21.102], center = true);
      
        intersection() {
          union() {
            translate([4.213, -7.312, -1.715])
            rotate([180, 90, -90])
            cylinder(h = 21.773, r1 = 0.474, r2 = 0.474, center = true, $fn = 12);
          
            translate([-10.1789, 0, -3.93642])
            rotate([90, 30, 0])
            cube(size = [22.703, 19.4, 36.397], center = true);
          }
        
          union() {
            translate([1.595, 0.238, 8.005])
            cube(size = [6.187, 4.759, 20.387], center = true);
          
            translate([0.4045, 0, 7.5285])
            cube(size = [4.568, 2.283, 21.34], center = true);
          }
        }
      
        translate([1.1905, 2.619, -1.881])
        cube(size = [0.33, 0.949, 2.235], center = true);
      }
    
      union() {
        difference() {
          translate([-4.24925, 2.3595, -7.35992])
          rotate([90, 30, 0])
          cube(size = [36.397, 19.4, 2.43], center = true);
        
          translate([2.4045, 2.3595, -2.238])
          cube(size = [2.093, 2.431, 1.808], center = true);
        }
      
        difference() {
          translate([1.3145, 8.0285, -2.27678])
          rotate([-90, -30, 0])
          cube(size = [36.397, 3.509, 20.34], center = true);
        
          difference() {
            translate([0.976, 1.452, -1.881])
            cube(size = [4.95, 5.198, 2.236], center = true);
          
            translate([-7.374, 3.575, -0.858])
            rotate([180, 90, 180])
            cylinder(h = 21.651, r1 = 0.471, r2 = 0.471, center = true, $fn = 12);
          }
        }
      
        translate([2.6425, 0.976, -2.595])
        cube(size = [1.616, 4.235, 0.807], center = true);
      }
    }
  
    intersection() {
      translate([-8.16388, -1.6185, 1.45774])
      rotate([90, 30, 0])
      cube(size = [20.799, 3.27, 4.854], center = true);
    
      union() {
        difference() {
          translate([-3.5475, -2.857, 7.6475])
          cube(size = [2.092, 0.473, 21.102], center = true);
        
          translate([-4.238, 0, -1])
          rotate([180, 90, -90])
          cylinder(h = 36.398, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
        }
      
        translate([-3.595, -2.619, -0.5955])
        cube(size = [2.187, 0.949, 0.33], center = true);
      
        translate([7.7785, -3.572, 8.719])
        cube(size = [20.84, 0.949, 18.959], center = true);
      
        translate([7.7785, -3.553, -0.835])
        rotate([180, 90, 180])
        cylinder(h = 20.84, r1 = 0.502, r2 = 0.502, center = true, $fn = 12);
      
        translate([-2.643, -2.619, -1.7145])
        cube(size = [0.283, 0.949, 2.568], center = true);
      
        translate([-3.413, -1.1425, -1.72])
        rotate([180, 90, -90])
        cylinder(h = 3.902, r1 = 0.464, r2 = 0.464, center = true, $fn = 12);
      
        translate([-1.8095, -2.619, -2.595])
        cube(size = [0.33, 0.949, 0.807], center = true);
      }
    }
  
    difference() {
      union() {
        translate([-3.5475, -1.1425, 2.095])
        cube(size = [2.092, 3.902, 0.949], center = true);
      
        translate([-3.5475, -2.857, 2.4525])
        cube(size = [2.092, 0.473, 1.664], center = true);
      }
    
      union() {
        translate([-5.41709, -0.9045, 12.9523])
        rotate([90, 30, 0])
        cube(size = [14.063, 19.381, 3.427], center = true);
      
        translate([0.941814, -2.857, 13.8147])
        rotate([-90, -30, 0])
        cube(size = [20.952, 13.412, 0.474], center = true);
      }
    }
  
    intersection() {
      union() {
        translate([7.1595, -1.929, 8.005])
        cube(size = [22.078, 5.473, 20.387], center = true);
      
        intersection() {
          union() {
            translate([0, -2.619, -0.9995])
            cube(size = [36.397, 0.949, 1.14], center = true);
          
            translate([-2.143, -3.405, 7.6475])
            cube(size = [0.997, 2.521, 21.102], center = true);
          }
        
          translate([3.436, -1.928, 5.95133])
          rotate([90, 30, 0])
          cube(size = [36.397, 22.653, 5.473], center = true);
        }
      }
    
      union() {
        difference() {
          translate([-8.16388, 7.076, 1.45774])
          rotate([90, 30, 0])
          cube(size = [20.799, 3.27, 22.245], center = true);
        
          translate([6.8025, -3.572, 7.6475])
          cube(size = [22.793, 0.95, 21.103], center = true);
        }
      
        translate([7.7785, -1.3715, -0.8805])
        cube(size = [20.84, 4.36, 0.902], center = true);
      
        translate([-1.12, -4.536, 0.189])
        rotate([180, 90, -90])
        cylinder(h = 0.259, r1 = 0.711, r2 = 0.711, center = true, $fn = 12);
      }
    
      union() {
        translate([1.84171, -1.929, 11.0671])
        rotate([-90, -30, 0])
        cube(size = [22.142, 19.07, 5.473], center = true);
      
        translate([3.62991, -1.1425, 6.62919])
        rotate([90, 30, 0])
        cube(size = [5.543, 21.285, 3.902], center = true);
      
        translate([-3.166, -1.1425, -1.4045])
        cube(size = [3.045, 3.902, 0.33], center = true);
      }
    }
  
    translate([0.1665, 3.575, -0.858])
    rotate([180, 90, 180])
    cylinder(h = 3.33, r1 = 0.471, r2 = 0.471, center = true, $fn = 12);
  
    difference() {
      union() {
        translate([-7.374, -1.6195, 0.1905])
        cube(size = [21.649, 4.854, 1.902], center = true);
      
        translate([-1.119, -1.1425, 0.19])
        rotate([180, 90, -90])
        cylinder(h = 3.902, r1 = 1.907, r2 = 1.907, center = true, $fn = 12);
      
        translate([1.857, -3.0955, 2.2145])
        cube(size = [3.187, 1.902, 2.14], center = true);
      
        translate([-1.119, -4.286, 0.19])
        rotate([180, 90, -90])
        cylinder(h = 0.235, r1 = 1.907, r2 = 1.907, center = true, $fn = 12);
      
        translate([4.213, -1.3715, 2.094])
        rotate([180, 90, -90])
        cylinder(h = 4.36, r1 = 0.475, r2 = 0.475, center = true, $fn = 12);
      
        translate([-8.1835, -3.553, -0.835])
        rotate([180, 90, 180])
        cylinder(h = 20.03, r1 = 0.502, r2 = 0.502, center = true, $fn = 12);
      
        difference() {
          translate([-8.588, -3.324, 0.191])
          cube(size = [19.221, 0.455, 3.045], center = true);
        
          translate([-8.588, -3.567, 1.237])
          rotate([180, 90, 180])
          cylinder(h = 19.222, r1 = 0.477, r2 = 0.477, center = true, $fn = 12);
        }
      }
    
      union() {
        difference() {
          translate([-4.33175, -1.679, 7.50281])
          rotate([-90, -30, 0])
          cube(size = [36.398, 19.071, 4.974], center = true);
        
          translate([0.88275, 7.076, 1.52897])
          rotate([90, 30, 0])
          cube(size = [36.399, 5.896, 22.247], center = true);
        }
      
        difference() {
          union() {
            translate([-4.92825, -1.679, 8.53598])
            rotate([-90, -30, 0])
            cube(size = [36.398, 16.685, 4.974], center = true);
          
            translate([3.2615, -2.381, 2.928])
            cube(size = [2.855, 0.474, 0.712], center = true);
          }
        
          difference() {
            translate([-8.0165, -3.086, 2.2145])
            cube(size = [20.366, 0.933, 2.142], center = true);
          
            translate([1.595, 0, 2.929])
            rotate([180, 90, -90])
            cylinder(h = 36.4, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
          }
        }
      
        difference() {
          translate([-6.755, -3.6315, 2.2145])
          cube(size = [22.888, 1.079, 2.141], center = true);
        
          translate([-1.119, -3.572, 0.19])
          rotate([180, 90, -90])
          cylinder(h = 0.951, r1 = 1.907, r2 = 1.907, center = true, $fn = 12);
        }
      }
    }
  
    intersection() {
      translate([-3.1905, 9.505, 2.2615])
      cube(size = [1.378, 17.387, 0.616], center = true);
    
      translate([6.09032, 1.4765, -3.51625])
      rotate([90, 30, 0])
      cube(size = [22.332, 36.397, 1.33], center = true);
    }
  
    intersection() {
      union() {
        translate([6.09532, -3.5715, -3.50759])
        rotate([90, 30, 0])
        cube(size = [22.332, 2.383, 2.854], center = true);
      
        translate([-3.414, -0.9045, 2.106])
        rotate([180, 90, -90])
        cylinder(h = 3.426, r1 = 0.461, r2 = 0.461, center = true, $fn = 12);
      }
    
      union() {
        translate([7.7785, -3.567, 1.237])
        rotate([180, 90, 180])
        cylinder(h = 20.84, r1 = 0.477, r2 = 0.477, center = true, $fn = 12);
      
        translate([-3.5475, 7.5525, -7.8145])
        cube(size = [2.092, 21.292, 20.768], center = true);
      }
    }
  
    translate([-1.8095, -2.619, 2.0955])
    cube(size = [0.33, 0.949, 2.568], center = true);
  
    intersection() {
      union() {
        intersection() {
          difference() {
            translate([-0.16, 2.8595, 0.277128])
            rotate([-90, -30, 0])
            cube(size = [36.397, 2.383, 1.43], center = true);
          
            translate([2.6425, 3.0955, 9.957])
            cube(size = [1.617, 1.903, 16.484], center = true);
          }
        
          union() {
            translate([4.213, 2.619, 2.094])
            rotate([180, 90, -90])
            cylinder(h = 0.949, r1 = 0.475, r2 = 0.475, center = true, $fn = 12);
          
            translate([2.6425, 2.8595, -7.457])
            cube(size = [1.616, 1.43, 21.483], center = true);
          }
        }
      
        difference() {
          union() {
            translate([3.429, 1.953, 2.2145])
            cube(size = [2.521, 2.283, 2.14], center = true);
          
            translate([1.5955, 2.619, 2.262])
            cube(size = [1.14, 0.949, 2.235], center = true);
          }
        
          translate([3.429, 2.381, 2.6185])
          cube(size = [2.522, 0.474, 1.331], center = true);
        }
      }
    
      union() {
        difference() {
          translate([2.2385, 2.8595, -7.4095])
          cube(size = [2.426, 1.43, 21.578], center = true);
        
          translate([1.595, 2.8595, 9.6715])
          cube(size = [0.474, 1.431, 17.055], center = true);
        }
      
        translate([3.2615, 2.193, 1.548])
        cube(size = [2.854, 2.763, 0.807], center = true);
      
        translate([3.0235, 2.857, 1.8575])
        cube(size = [3.33, 0.473, 1.426], center = true);
      
        intersection() {
          translate([-0.16, 1.953, 0.277128])
          rotate([-90, -30, 0])
          cube(size = [36.397, 2.383, 2.283], center = true);
        
          translate([-3.3715, 2.619, -5.83961])
          rotate([90, 30, 0])
          cube(size = [36.397, 22.911, 0.949], center = true);
        }
      
        translate([4.213, -7.5525, 2.094])
        rotate([180, 90, -90])
        cylinder(h = 21.292, r1 = 0.475, r2 = 0.475, center = true, $fn = 12);
      
        translate([-3.773, 2.381, -6.53503])
        rotate([90, 30, 0])
        cube(size = [36.397, 21.305, 0.473], center = true);
      }
    }
  
    intersection() {
      difference() {
        difference() {
          translate([3.778, 1.4765, 6.54369])
          rotate([90, 30, 0])
          cube(size = [36.397, 21.285, 1.33], center = true);
        
          translate([7.85, 9.505, -8.124])
          cube(size = [20.698, 17.388, 20.15], center = true);
        }
      
        translate([-9.67134, -8.0285, 5.58375])
        rotate([90, 30, 0])
        cube(size = [14.063, 36.398, 20.341], center = true);
      }
    
      translate([7.1595, 0, -8.124])
      cube(size = [22.078, 36.397, 20.149], center = true);
    }
  
    translate([-2.143, -2.848, 1.2625])
    cube(size = [0.997, 1.407, 0.902], center = true);
  
    intersection() {
      union() {
        translate([-1.12, 4.536, 0.189])
        rotate([180, 90, -90])
        cylinder(h = 0.259, r1 = 0.711, r2 = 0.711, center = true, $fn = 12);
      
        translate([-2.143, 2.619, 1.3095])
        cube(size = [1.283, 0.949, 4.14], center = true);
      
        difference() {
          translate([-3.0475, -7.7905, 1.4285])
          cube(size = [3.092, 20.816, 0.568], center = true);
        
          translate([-3.619, 1.786, 1.8575])
          cube(size = [1.95, 0.712, 1.427], center = true);
        }
      }
    
      difference() {
        union() {
          translate([-3.1905, 2.619, 9.957])
          cube(size = [1.378, 0.949, 16.483], center = true);
        
          translate([1.84107, 3.048, -10.8762])
          rotate([90, 30, 0])
          cube(size = [22.332, 19.4, 3.235], center = true);
        }
      
        translate([-2.6905, 2.5025, 1.833])
        cube(size = [2.379, 2.145, 0.236], center = true);
      }
    }
  
    translate([-2.643, -2.619, 2.976])
    cube(size = [0.283, 0.949, 0.807], center = true);
  
    translate([-3.595, -2.619, 0.9765])
    cube(size = [2.187, 0.949, 0.33], center = true);
  
    difference() {
      union() {
        translate([-9.85, 3.0955, 0.1905])
        cube(size = [16.697, 1.902, 1.902], center = true);
      
        translate([-3.2855, 3.0975, 1.548])
        cube(size = [2.616, 0.954, 0.807], center = true);
      
        translate([-1.119, 3.2145, 0.19])
        rotate([180, 90, -90])
        cylinder(h = 3.568, r1 = 0.19, r2 = 0.19, center = true, $fn = 12);
      
        translate([1.84107, 3.0975, -10.8762])
        rotate([90, 30, 0])
        cube(size = [22.332, 19.4, 0.954], center = true);
      
        translate([-2.143, 3.576, 1.242])
        rotate([180, 90, 180])
        cylinder(h = 1.283, r1 = 0.468, r2 = 0.468, center = true, $fn = 12);
      
        translate([10.3843, 2.619, -2.54016])
        rotate([-90, -30, 0])
        cube(size = [20.951, 21.615, 0.949], center = true);
      
        translate([-3.262, 2.7385, 0.595])
        cube(size = [1.235, 2.616, 2.711], center = true);
      }
    
      union() {
        difference() {
          translate([0, 2.5025, 0])
          cube(size = [36.398, 2.145, 36.398], center = true);
        
          union() {
            translate([-2.6905, 2.7385, 0.476])
            cube(size = [2.38, 2.618, 2.475], center = true);
          
            translate([-3.333, 2.2625, 2.048])
            cube(size = [2.713, 1.666, 2.475], center = true);
          }
        }
      
        translate([-4.238, -6.8975, 1.381])
        rotate([180, 90, -90])
        cylinder(h = 22.603, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
      
        translate([-10.4215, 3.571, -7.8145])
        cube(size = [15.555, 0.951, 20.769], center = true);
      }
    }
  
    translate([-3.3335, 2.857, -1.714])
    cube(size = [1.092, 0.473, 0.949], center = true);
  
    translate([-2.3095, 3.575, -0.858])
    rotate([180, 90, 180])
    cylinder(h = 0.664, r1 = 0.471, r2 = 0.471, center = true, $fn = 12);
  
    difference() {
      union() {
        difference() {
          translate([0.7855, 2.2625, -2.1665])
          cube(size = [5.33, 1.664, 1.664], center = true);
        
          union() {
            translate([2.429, 2.619, -2.595])
            cube(size = [0.522, 0.95, 0.808], center = true);
          
            translate([9.612, 0.3565, -2.786])
            cube(size = [17.174, 3.569, 1.188], center = true);
          }
        }
      
        intersection() {
          union() {
            translate([3.5005, 2.3595, 7.6475])
            cube(size = [2.378, 2.43, 21.102], center = true);
          
            translate([1.595, -0.0005, 7.4095])
            cube(size = [6.187, 2.854, 21.578], center = true);
          }
        
          union() {
            translate([1.3145, 0.476, -2.27678])
            rotate([-90, -30, 0])
            cube(size = [36.397, 3.509, 5.235], center = true);
          
            translate([-10.1789, -7.7905, -3.93642])
            rotate([90, 30, 0])
            cube(size = [22.703, 19.4, 20.816], center = true);
          }
        }
      }
    
      union() {
        translate([2.6425, 2.857, -2.786])
        cube(size = [1.617, 0.474, 1.188], center = true);
      
        translate([1.595, 10.4095, -2.547])
        rotate([180, 90, -90])
        cylinder(h = 15.579, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
      
        translate([-8.1835, 2.5025, -3.024])
        cube(size = [20.031, 2.145, 0.236], center = true);
      
        translate([4.071, 0.238, -2.2855])
        cube(size = [1.236, 4.76, 1.427], center = true);
      
        intersection() {
          translate([5.2445, -7.5525, -9.08374])
          rotate([-90, -30, 0])
          cube(size = [36.398, 15.42, 21.293], center = true);
        
          translate([-4.84575, 2.381, -8.39309])
          rotate([90, 30, 0])
          cube(size = [36.398, 17.015, 0.474], center = true);
        }
      
        translate([-8.4215, 2.024, -2.667])
        cube(size = [19.555, 1.188, 0.95], center = true);
      
        translate([3.5005, 0.238, -2.786])
        cube(size = [2.379, 4.76, 1.188], center = true);
      }
    }
  
    intersection() {
      translate([-4.92825, 1.4765, 8.53598])
      rotate([-90, -30, 0])
      cube(size = [36.397, 16.684, 1.33], center = true);
    
      translate([7.85, 0, -7.8145])
      cube(size = [20.697, 36.397, 20.768], center = true);
    }
  
    translate([-3.414, 1.4765, 2.106])
    rotate([180, 90, -90])
    cylinder(h = 1.33, r1 = 0.461, r2 = 0.461, center = true, $fn = 12);
  
    translate([-1.119, 1.715, 0.19])
    rotate([180, 90, -90])
    cylinder(h = 1.807, r1 = 1.907, r2 = 1.907, center = true, $fn = 12);
  
    difference() {
      union() {
        translate([2.4045, 3.576, 1.242])
        rotate([180, 90, 180])
        cylinder(h = 2.092, r1 = 0.468, r2 = 0.468, center = true, $fn = 12);
      
        translate([10.0165, 1.953, -7.8145])
        cube(size = [16.364, 2.283, 20.768], center = true);
      
        difference() {
          translate([2.6425, 3.812, -8.5285])
          cube(size = [1.616, 0.469, 19.34], center = true);
        
          translate([4.76825, 3.0955, -8.25885])
          rotate([-90, -30, 0])
          cube(size = [36.398, 17.325, 1.903], center = true);
        }
      }
    
      translate([9.00753, 9.505, -5.2005])
      rotate([90, 30, 0])
      cube(size = [15.596, 36.398, 17.388], center = true);
    }
  
    difference() {
      union() {
        translate([-3.095, 2.2625, 2.095])
        cube(size = [3.187, 1.664, 0.949], center = true);
      
        translate([-1.8095, 2.619, 2.6665])
        cube(size = [0.33, 0.949, 1.426], center = true);
      }
    
      difference() {
        translate([-13.9206, 2.2615, -1.77617])
        rotate([90, 30, 0])
        cube(size = [14.063, 19.401, 1.665], center = true);
      
        translate([-4.285, 2.8595, 0.595])
        cube(size = [0.809, 1.432, 2.713], center = true);
      }
    }
  
    difference() {
      union() {
        difference() {
          translate([7.7785, -10.076, -7.8145])
          cube(size = [20.84, 16.245, 20.768], center = true);
        
          translate([7.7785, -10.6475, 1.8575])
          cube(size = [20.841, 15.103, 1.427], center = true);
        }
      
        difference() {
          translate([6.755, -2.619, 2.4525])
          cube(size = [22.887, 0.949, 1.664], center = true);
        
          translate([7.16807, -2.2855, -1.64953])
          rotate([90, 30, 0])
          cube(size = [22.333, 1.903, 0.665], center = true);
        }
      
        translate([10.3843, -2.381, -2.54016])
        rotate([-90, -30, 0])
        cube(size = [20.951, 21.615, 0.473], center = true);
      
        translate([7.1595, -1.1425, -7.9335])
        cube(size = [22.078, 3.882, 20.53], center = true);
      }
    
      union() {
        translate([-3.595, -2.7525, 2.6185])
        cube(size = [2.188, 1.599, 1.431], center = true);
      
        translate([8.2785, -1.6195, -8.695])
        cube(size = [19.841, 4.855, 19.008], center = true);
      
        translate([-2.214, -3.3335, 2.929])
        rotate([180, 90, -90])
        cylinder(h = 1.427, r1 = 0.144, r2 = 0.144, center = true, $fn = 12);
      
        translate([8.112, -2.381, 10.3855])
        cube(size = [20.174, 0.474, 15.627], center = true);
      
        difference() {
          union() {
            translate([7.1595, -8.695, -8.2905])
            cube(size = [22.079, 19.008, 19.817], center = true);
          
            translate([5.327, -2.095, 9.22663])
            rotate([90, 30, 0])
            cube(size = [36.398, 15.09, 5.808], center = true);
          }
        
          union() {
            translate([6.09532, -1.6185, -3.50759])
            rotate([90, 30, 0])
            cube(size = [22.334, 2.385, 4.856], center = true);
          
            translate([-1.119, -4.0475, 0.19])
            rotate([180, 90, -90])
            cylinder(h = 1.904, r1 = 0.19, r2 = 0.19, center = true, $fn = 12);
          }
        }
      }
    }
  
    difference() {
      translate([7.1595, 1.4765, -8.124])
      cube(size = [22.078, 1.33, 20.149], center = true);
    
      translate([6.09032, 0, -3.51625])
      rotate([90, 30, 0])
      cube(size = [22.333, 36.398, 36.398], center = true);
    }
  
    intersection() {
      union() {
        difference() {
          translate([1.79075, 0, -3.10167])
          rotate([-90, -30, 0])
          cube(size = [36.397, 1.604, 36.397], center = true);
        
          translate([-7.374, 0, 0])
          cube(size = [21.65, 36.398, 36.398], center = true);
        }
      
        intersection() {
          translate([2.2385, -10.4095, 8.4335])
          cube(size = [2.426, 15.578, 19.53], center = true);
        
          translate([2.8575, -10.1715, 7.6])
          cube(size = [3.664, 16.054, 21.197], center = true);
        }
      
        difference() {
          union() {
            translate([1.9995, -2.619, 7.6])
            cube(size = [0.33, 0.949, 21.197], center = true);
          
            translate([-7.374, -2.857, -2.1195])
            cube(size = [21.649, 0.473, 1.568], center = true);
          }
        
          union() {
            translate([-2.214, -10.4095, -2.548])
            rotate([180, 90, -90])
            cylinder(h = 15.579, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
          
            translate([-4.33175, -1.1425, 7.50281])
            rotate([-90, -30, 0])
            cube(size = [36.398, 19.071, 3.903], center = true);
          }
        }
      }
    
      union() {
        difference() {
          translate([-6.755, -2.857, -2.2385])
          cube(size = [22.887, 0.473, 1.33], center = true);
        
          translate([1.595, -10.1715, -2.547])
          rotate([180, 90, -90])
          cylinder(h = 16.055, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
        }
      
        translate([2.6425, 7.5525, -2.9525])
        cube(size = [1.616, 21.292, 0.092], center = true);
      
        translate([-6.755, -1.1425, -1.452])
        cube(size = [22.887, 3.902, 0.235], center = true);
      
        translate([4.213, -2.381, -1.715])
        rotate([180, 90, -90])
        cylinder(h = 0.473, r1 = 0.474, r2 = 0.474, center = true, $fn = 12);
      
        translate([1.9995, 7.7905, -10.195])
        cube(size = [0.33, 20.816, 16.007], center = true);
      
        translate([0.91275, -3.086, -1.58093])
        rotate([-90, -30, 0])
        cube(size = [36.397, 1.902, 0.931], center = true);
      }
    }
  
    intersection() {
      union() {
        translate([5.53872, -7.7905, -5.66365])
        rotate([90, 30, 0])
        cube(size = [21.142, 1.902, 20.816], center = true);
      
        translate([-4.285, 2.619, -1.4045])
        cube(size = [0.807, 0.949, 0.33], center = true);
      }
    
      translate([-4.33175, 2.619, 7.50281])
      rotate([-90, -30, 0])
      cube(size = [36.397, 19.07, 0.949], center = true);
    }
  
    translate([-4.285, 2.619, -0.5955])
    cube(size = [0.807, 0.949, 0.33], center = true);
  
    difference() {
      union() {
        translate([-3.0475, 2.857, 2.4525])
        cube(size = [3.092, 0.473, 1.664], center = true);
      
        translate([-3.414, 2.2625, 2.106])
        rotate([180, 90, -90])
        cylinder(h = 1.664, r1 = 0.461, r2 = 0.461, center = true, $fn = 12);
      }
    
      union() {
        translate([-2.214, 0, 2.929])
        rotate([180, 90, -90])
        cylinder(h = 36.398, r1 = 0.144, r2 = 0.144, center = true, $fn = 12);
      
        translate([0.941814, 3.512, 13.8147])
        rotate([-90, -30, 0])
        cube(size = [20.952, 13.412, 1.784], center = true);
      }
    }
  
    intersection() {
      union() {
        translate([-3.619, 2.619, 7.6475])
        cube(size = [1.949, 0.949, 21.102], center = true);
      
        translate([7.7785, 3.0975, 8.4335])
        cube(size = [20.84, 0.954, 19.53], center = true);
      
        difference() {
          translate([-2.762, -7.5525, -1.667])
          cube(size = [2.235, 21.292, 2.473], center = true);
        
          translate([-2.214, -7.312, -2.548])
          rotate([180, 90, -90])
          cylinder(h = 21.774, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
        }
      }
    
      difference() {
        union() {
          translate([-1.40975, 10.4095, -2.44176])
          rotate([90, 30, 0])
          cube(size = [36.397, 3.27, 15.578], center = true);
        
          translate([-3.1905, 2.193, -1.309])
          cube(size = [1.378, 2.763, 1.759], center = true);
        }
      
        union() {
          translate([-4.238, -7.5525, -1])
          rotate([180, 90, -90])
          cylinder(h = 21.293, r1 = 0.142, r2 = 0.142, center = true, $fn = 12);
        
          translate([-3.3335, -7.5525, -1.8805])
          cube(size = [1.093, 21.293, 0.617], center = true);
        }
      }
    }
  
    difference() {
      union() {
        translate([7.7785, 3.0975, -1.7145])
        cube(size = [20.84, 0.954, 2.568], center = true);
      
        intersection() {
          union() {
            translate([-4.238, 2.619, -1.667])
            cube(size = [0.711, 0.949, 2.473], center = true);
          
            translate([7.1595, 9.505, -9.481])
            cube(size = [22.078, 17.387, 17.435], center = true);
          }
        
          union() {
            translate([6.17346, 9.505, 3.56425])
            rotate([-90, -30, 0])
            cube(size = [22.142, 36.397, 17.387], center = true);
          
            translate([-3.413, 0, -1.72])
            rotate([180, 90, -90])
            cylinder(h = 36.397, r1 = 0.464, r2 = 0.464, center = true, $fn = 12);
          }
        }
      }
    
      union() {
        difference() {
          difference() {
            translate([7.1595, 9.505, -9.481])
            cube(size = [22.079, 17.388, 17.436], center = true);
          
            translate([7.7785, 3.575, -0.858])
            rotate([180, 90, 180])
            cylinder(h = 20.842, r1 = 0.471, r2 = 0.471, center = true, $fn = 12);
          }
        
          union() {
            translate([7.1595, 1.953, -1.714])
            cube(size = [22.08, 2.285, 0.951], center = true);
          
            translate([-2.2145, 2.619, -1.7145])
            cube(size = [1.142, 0.951, 2.57], center = true);
          }
        }
      
        intersection() {
          difference() {
            translate([10.9417, 9.505, -4.6946])
            rotate([-90, -30, 0])
            cube(size = [22.143, 17.325, 17.388], center = true);
          
            translate([5.53872, 2.619, -5.66365])
            rotate([90, 30, 0])
            cube(size = [21.144, 1.904, 0.951], center = true);
          }
        
          union() {
            translate([10.8607, 0, 3.55433])
            rotate([90, 30, 0])
            cube(size = [21.143, 19.381, 36.398], center = true);
          
            translate([-2.238, 2.619, -9.7665])
            cube(size = [0.522, 0.95, 16.865], center = true);
          }
        }
      }
    }
  }
}
