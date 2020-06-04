intersection() {
union() {
intersection() {
union() {
rotate([0, 0, 0])
translate([-0.001, 1.573, -2.047])
cylinder(h = 20.147, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
rotate([90, 30, 0])
translate([1.554, -18.1, -18.1]) cube(size = [16.546, 36.2, 18.221], center = false);
}
union() {
rotate([180, 90, -90])
translate([0.001, 4.011, -18.1])
cylinder(h = 16.294, r1 = 0.988, r2 = 0.988, center = false, $fn = 12);
rotate([0, 0, 0])
translate([-1.82, 0.342, -18.1])
cylinder(h = 14.247, r1 = 0.458, r2 = 0.458, center = false, $fn = 12);
}
}
intersection() {
union() {
rotate([0, 0, 0])
translate([1.793, 0.368, -3.251])
cylinder(h = 21.351, r1 = 0.495, r2 = 0.495, center = false, $fn = 12);
intersection() {
difference() {
rotate([90, 30, 0])
translate([1.554, -18.1, 0.602]) cube(size = [16.546, 36.2, 17.498], center = false);
rotate([90, 40, 0])
translate([4.049, -18.1, -1.806]) cube(size = [14.051, 36.2, 3.612], center = false);
}
rotate([180, 90, -90])
translate([-1.858, 0.001, -18.1])
cylinder(h = 36.2, r1 = 5.971, r2 = 5.971, center = false, $fn = 12);
translate([-18.1, -1.806, -3.853]) cube(size = [36.2, 1.204, 21.953], center = false);
}
translate([-18.1, -0.602, -3.251]) cube(size = [20.388, 0.481, 1.204], center = false);
rotate([-90, -40, 0])
translate([-18.1, -18.1, -0.121]) cube(size = [36.2, 20.584, 18.221], center = false);
rotate([0, 0, 0])
translate([1.793, 0.368, -3.251])
cylinder(h = 1.204, r1 = 0.495, r2 = 0.495, center = false, $fn = 12);
}
union() {
intersection() {
difference() {
rotate([90, 30, 0])
translate([1.554, -18.1, -1.806]) cube(size = [16.546, 36.2, 3.612], center = false);
translate([-18.1, -0.602, -3.251]) cube(size = [20.388, 0.481, 21.351], center = false);
}
difference() {
rotate([90, 30, 0])
translate([1.554, -18.1, -1.806]) cube(size = [16.546, 17.444, 19.906], center = false);
rotate([0, 0, 0])
translate([-0.001, 1.573, -18.1])
cylinder(h = 36.2, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
}
}
difference() {
union() {
translate([-18.1, -0.602, -3.853]) cube(size = [36.2, 0.481, 0.602], center = false);
rotate([90, 30, 0])
translate([1.554, -18.1, 0.121]) cube(size = [16.546, 36.2, 0.481], center = false);
}
union() {
rotate([0, 0, 0])
translate([-0.001, 1.573, -3.853])
cylinder(h = 1.806, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
rotate([180, 0, 180])
translate([-1.376, 0.77, -18.1])
cylinder(h = 20.147, r1 = 0.9, r2 = 0.9, center = false, $fn = 12);
}
}
}
}
difference() {
union() {
difference() {
rotate([-90, -30, 0])
translate([-2.711, -18.1, -1.806]) cube(size = [6.247, 36.2, 1.204], center = false);
translate([-2.287, -1.806, -18.1]) cube(size = [20.387, 1.204, 36.2], center = false);
}
difference() {
union() {
rotate([180, 90, -90])
translate([2.335, 0.003, -1.806])
cylinder(h = 1.204, r1 = 3.884, r2 = 3.884, center = false, $fn = 12);
translate([-2.287, -1.806, -0.626]) cube(size = [20.387, 3.612, 3.877], center = false);
}
union() {
rotate([-90, -40, 0])
translate([-18.1, -0.001, -1.806]) cube(size = [36.2, 18.101, 3.612], center = false);
rotate([0, 0, 0])
translate([-0.001, 1.573, -0.626])
cylinder(h = 3.877, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
}
}
difference() {
translate([-2.287, -1.806, 2.047]) cube(size = [20.387, 1.204, 1.805], center = false);
rotate([180, 90, -90])
translate([-2.937, 1.617, -0.602])
cylinder(h = 0.481, r1 = 0.914, r2 = 0.914, center = false, $fn = 12);
}
}
union() {
difference() {
translate([-2.287, -0.602, 0.626]) cube(size = [20.387, 2.408, 1.421], center = false);
rotate([0, 0, 0])
translate([-1.82, 0.342, 0.626])
cylinder(h = 1.421, r1 = 0.458, r2 = 0.458, center = false, $fn = 12);
}
difference() {
union() {
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 17.979, 21.952], center = false);
translate([-18.1, -0.121, 2.047]) cube(size = [36.2, 1.927, 1.204], center = false);
}
intersection() {
rotate([90, 30, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [18.099, 36.2, 3.612], center = false);
rotate([-90, -30, 0])
translate([-3.962, -18.1, -18.1]) cube(size = [7.498, 36.2, 19.906], center = false);
}
}
difference() {
rotate([90, 30, 0])
translate([-18.1, -18.1, 0.602]) cube(size = [14.627, 36.2, 17.498], center = false);
rotate([180, 90, -90])
translate([-2.937, 1.617, -1.806])
cylinder(h = 1.204, r1 = 0.914, r2 = 0.914, center = false, $fn = 12);
}
}
}
difference() {
union() {
rotate([180, 0, 180])
translate([-1.376, 0.77, -18.1])
cylinder(h = 18.943, r1 = 0.9, r2 = 0.9, center = false, $fn = 12);
rotate([90, 30, 0])
translate([-18.1, 1.609, -1.806]) cube(size = [18.099, 16.491, 1.927], center = false);
rotate([0, 0, 0])
translate([1.793, 0.368, -18.1])
cylinder(h = 36.2, r1 = 0.495, r2 = 0.495, center = false, $fn = 12);
rotate([90, 30, 0])
translate([-0.001, -18.1, -1.806]) cube(size = [18.101, 19.709, 1.927], center = false);
difference() {
union() {
rotate([0, 0, 0])
translate([-0.001, 1.573, 0.843])
cylinder(h = 17.257, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
rotate([90, 30, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [36.2, 20.142, 1.927], center = false);
}
union() {
rotate([-90, -40, 0])
translate([-18.1, -0.001, -1.806]) cube(size = [22.149, 2.485, 19.906], center = false);
rotate([90, 30, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [18.099, 20.142, 18.702], center = false);
}
}
}
union() {
rotate([90, 30, 0])
translate([-18.1, -18.1, 0.121]) cube(size = [36.2, 19.709, 1.685], center = false);
translate([-18.1, -0.121, -18.1]) cube(size = [36.2, 1.927, 18.943], center = false);
rotate([0, 0, 0])
translate([-0.001, 1.573, -18.1])
cylinder(h = 36.2, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
translate([-18.1, -0.121, 2.047]) cube(size = [36.2, 1.927, 16.053], center = false);
}
}
intersection() {
union() {
difference() {
rotate([90, 40, 0])
translate([-4.049, -18.1, 0.121]) cube(size = [22.149, 36.2, 17.979], center = false);
rotate([180, 90, -90])
translate([-0.001, 3.853, -1.806])
cylinder(h = 19.906, r1 = 0.361, r2 = 0.361, center = false, $fn = 12);
}
intersection() {
translate([-1.313, 0.721, 0.626])
cylinder(h = 2.625, r1 = 0.978, r2 = 0.978, center = false, $fn = 12);
translate([-2.287, -1.084, -0.626]) cube(size = [20.387, 2.89, 3.877], center = false);
}
}
difference() {
difference() {
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 36.2, 21.952], center = false);
rotate([0, 0, 0])
translate([-0.001, 1.573, 0.626])
cylinder(h = 2.625, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
}
difference() {
rotate([90, 30, 0])
translate([-3.962, -18.1, 0.121]) cube(size = [22.062, 36.2, 0.963], center = false);
translate([-18.1, -1.084, 0.626]) cube(size = [15.813, 0.963, 2.625], center = false);
}
}
union() {
translate([-2.287, -1.084, 0.626]) cube(size = [20.387, 2.89, 3.227], center = false);
intersection() {
union() {
rotate([180, 90, -90])
translate([0.001, 4.011, -1.806])
cylinder(h = 1.204, r1 = 0.988, r2 = 0.988, center = false, $fn = 12);
translate([-18.1, -1.806, 0.626]) cube(size = [15.813, 3.612, 3.227], center = false);
}
union() {
rotate([-90, -30, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [21.636, 36.2, 17.498], center = false);
rotate([90, 30, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [18.099, 36.2, 1.927], center = false);
}
}
}
}
difference() {
difference() {
rotate([180, 90, -90])
translate([-0.001, -4.082, -1.806])
cylinder(h = 1.204, r1 = 0.919, r2 = 0.919, center = false, $fn = 12);
rotate([180, 90, -90])
translate([0, -3.852, -1.806])
cylinder(h = 19.906, r1 = 0.361, r2 = 0.361, center = false, $fn = 12);
}
difference() {
rotate([90, 30, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [22.062, 36.2, 19.184], center = false);
rotate([180, 90, -90])
translate([2.335, 0.003, -1.084])
cylinder(h = 19.184, r1 = 3.884, r2 = 3.884, center = false, $fn = 12);
}
}
difference() {
union() {
translate([-2.287, -1.806, -3.251]) cube(size = [20.387, 3.612, 1.204], center = false);
translate([-1.313, 0.721, -3.251])
cylinder(h = 4.094, r1 = 0.978, r2 = 0.978, center = false, $fn = 12);
intersection() {
rotate([180, 90, -90])
translate([-1.858, 0.001, -1.806])
cylinder(h = 1.685, r1 = 5.971, r2 = 5.971, center = false, $fn = 12);
translate([-18.1, -18.1, -3.853]) cube(size = [36.2, 17.498, 3.228], center = false);
}
translate([-2.287, -1.806, -0.843]) cube(size = [20.387, 3.612, 1.686], center = false);
}
union() {
rotate([0, 0, 0])
translate([-0.001, 1.573, -18.1])
cylinder(h = 36.2, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
translate([-18.1, -0.602, -2.047]) cube(size = [36.2, 0.481, 1.204], center = false);
rotate([90, 30, 0])
translate([1.554, -18.1, -18.1]) cube(size = [16.546, 36.2, 36.2], center = false);
rotate([-90, -40, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [14.051, 36.2, 1.685], center = false);
}
}
difference() {
union() {
rotate([180, 90, -90])
translate([-2.931, -1.62, -1.806])
cylinder(h = 1.204, r1 = 0.916, r2 = 0.916, center = false, $fn = 12);
intersection() {
difference() {
rotate([-90, -40, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [22.149, 20.584, 3.612], center = false);
rotate([90, 30, 0])
translate([-18.1, 1.609, -1.806]) cube(size = [18.099, 0.433, 2.408], center = false);
}
union() {
translate([-18.1, -0.602, 2.047]) cube(size = [20.388, 18.702, 1.204], center = false);
translate([-18.1, -18.1, -0.843]) cube(size = [36.2, 17.498, 4.094], center = false);
}
}
translate([-18.1, -0.602, -0.843]) cube(size = [20.388, 0.481, 1.686], center = false);
translate([-18.1, -0.121, -0.843]) cube(size = [20.388, 1.927, 1.686], center = false);
rotate([180, 0, 180])
translate([-1.376, 0.77, 0.843])
cylinder(h = 17.257, r1 = 0.9, r2 = 0.9, center = false, $fn = 12);
}
intersection() {
union() {
rotate([0, 0, 0])
translate([-0.001, 1.573, -18.1])
cylinder(h = 36.2, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
rotate([-90, -40, 0])
translate([-18.1, 2.484, -0.121]) cube(size = [22.149, 15.616, 18.221], center = false);
rotate([90, 30, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [18.099, 19.709, 3.612], center = false);
translate([2.288, -1.806, -18.1]) cube(size = [15.812, 19.906, 18.943], center = false);
}
union() {
difference() {
translate([-18.1, -1.806, -18.1]) cube(size = [20.388, 3.612, 21.351], center = false);
rotate([90, 30, 0])
translate([-0.001, 1.609, -18.1]) cube(size = [18.101, 0.433, 36.2], center = false);
}
rotate([-90, -40, 0])
translate([-18.1, 2.484, -1.806]) cube(size = [22.149, 15.616, 3.612], center = false);
rotate([180, 90, -90])
translate([-0.001, -4.082, -1.806])
cylinder(h = 19.906, r1 = 0.919, r2 = 0.919, center = false, $fn = 12);
}
}
}
difference() {
intersection() {
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 17.498, 18.726], center = false);
rotate([90, 30, 0])
translate([-18.1, -0.656, -18.1]) cube(size = [20.811, 18.756, 19.906], center = false);
}
difference() {
rotate([90, 30, 0])
translate([2.711, -18.1, 0.602]) cube(size = [1.251, 36.2, 1.204], center = false);
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 17.498, 17.474], center = false);
}
}
difference() {
intersection() {
rotate([90, 30, 0])
translate([2.711, -0.656, 0.602]) cube(size = [1.251, 18.756, 17.498], center = false);
rotate([-90, -40, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [22.149, 36.2, 19.906], center = false);
}
intersection() {
rotate([180, 90, -90])
translate([-0.001, -4.082, -1.806])
cylinder(h = 19.906, r1 = 0.919, r2 = 0.919, center = false, $fn = 12);
rotate([-90, -30, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [22.062, 36.2, 19.906], center = false);
}
}
difference() {
rotate([90, 30, 0])
translate([2.711, -0.656, 0.602]) cube(size = [15.389, 18.756, 1.204], center = false);
intersection() {
union() {
translate([-18.1, -1.806, -0.626]) cube(size = [36.2, 0.722, 1.251], center = false);
translate([-18.1, -1.084, -0.626]) cube(size = [36.2, 19.184, 1.251], center = false);
rotate([90, 40, 0])
translate([4.049, -18.1, -18.1]) cube(size = [14.051, 36.2, 36.2], center = false);
translate([-18.1, -18.1, 0.626]) cube(size = [36.2, 36.2, 17.474], center = false);
}
union() {
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
rotate([180, 90, -90])
translate([-0.001, -4.082, -0.602])
cylinder(h = 18.702, r1 = 0.919, r2 = 0.919, center = false, $fn = 12);
}
}
}
intersection() {
difference() {
translate([-18.1, -1.084, 0.626]) cube(size = [36.2, 0.482, 17.474], center = false);
rotate([90, 30, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [36.2, 17.444, 19.184], center = false);
}
rotate([180, 90, -90])
translate([-0.001, -4.082, -1.806])
cylinder(h = 19.906, r1 = 0.919, r2 = 0.919, center = false, $fn = 12);
}
intersection() {
rotate([-90, -30, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [14.138, 36.2, 36.2], center = false);
translate([-18.1, -1.806, -2.047]) cube(size = [15.813, 1.204, 2.89], center = false);
rotate([180, 90, -90])
translate([0.001, 4.011, -1.806])
cylinder(h = 1.204, r1 = 0.988, r2 = 0.988, center = false, $fn = 12);
translate([-18.1, -18.1, -2.047]) cube(size = [36.2, 36.2, 2.89], center = false);
}
intersection() {
rotate([90, 30, 0])
translate([-18.1, -18.1, -1.806]) cube(size = [19.654, 36.2, 19.906], center = false);
union() {
rotate([90, 30, 0])
translate([-0.001, -18.1, -18.1]) cube(size = [1.556, 36.2, 18.221], center = false);
rotate([0, 0, 0])
translate([-1.82, 0.342, -2.047])
cylinder(h = 1.204, r1 = 0.458, r2 = 0.458, center = false, $fn = 12);
}
difference() {
difference() {
translate([-2.287, -0.121, -2.047]) cube(size = [20.387, 1.927, 1.204], center = false);
rotate([0, 0, 0])
translate([-0.001, 1.573, -2.047])
cylinder(h = 1.421, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
}
rotate([90, 30, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [18.099, 36.2, 16.294], center = false);
}
}
difference() {
union() {
rotate([180, 0, 180])
translate([-1.376, 0.77, -18.1])
cylinder(h = 21.351, r1 = 0.9, r2 = 0.9, center = false, $fn = 12);
translate([-18.1, -0.121, -3.251]) cube(size = [20.388, 1.927, 1.204], center = false);
rotate([0, 0, 0])
translate([1.793, 0.368, -2.047])
cylinder(h = 20.147, r1 = 0.495, r2 = 0.495, center = false, $fn = 12);
}
union() {
rotate([0, 0, 0])
translate([-0.001, 1.573, -18.1])
cylinder(h = 36.2, r1 = 1.81, r2 = 1.81, center = false, $fn = 12);
rotate([90, 30, 0])
translate([-18.1, -18.1, -18.1]) cube(size = [19.654, 36.2, 18.702], center = false);
rotate([90, 40, 0])
translate([-18.1, -18.1, 0.121]) cube(size = [36.2, 36.2, 17.979], center = false);
}
}
}
translate([-6, -2.167, -4.623]) cube(size = [12, 4.334, 9.247], center = false);
}
