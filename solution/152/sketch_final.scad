intersection() {
translate([-1.646, -6, -0.911]) cube(size = [3.291, 12, 1.823], center = false);
union() {
difference() {
translate([-0.534, -2.416, -0.759]) cube(size = [0.253, 0.833, 1.013], center = false);
translate([-0.534, -2.247, -0.253]) cube(size = [0.253, 0.665, 0.506], center = false);
}
translate([-0.534, -3.249, -0.253]) cube(size = [0.253, 0.169, 0.506], center = false);
translate([-0.534, -4.082, -0.253]) cube(size = [0.253, 0.169, 1.013], center = false);
difference() {
union() {
intersection() {
difference() {
translate([-0.534, -1.582, -0.759]) cube(size = [18.634, 19.682, 18.86], center = false);
translate([1.369, 0.002, -0.759])
cylinder(h = 18.86, r1 = 0.886, r2 = 0.886, center = false, $fn = 12);
}
union() {
translate([-0.015, -1.582, -0.759]) cube(size = [1.386, 3.998, 1.519], center = false);
rotate([0, 0, -30])
translate([-18.1, 0.847, -0.759]) cube(size = [19.835, 17.253, 0.506], center = false);
}
}
intersection() {
difference() {
translate([-0.534, -2.247, -18.1]) cube(size = [0.696, 3.829, 18.86], center = false);
rotate([0, 0, -30])
translate([-18.1, -1.096, -18.1]) cube(size = [36.2, 19.196, 17.53], center = false);
}
difference() {
rotate([-180, 0, 30])
translate([-18.1, -18.1, -0.759]) cube(size = [36.2, 18.947, 1.519], center = false);
rotate([0, 0, -30])
translate([-18.1, -1.096, -0.57]) cube(size = [19.835, 1.943, 1.329], center = false);
}
}
}
union() {
intersection() {
difference() {
rotate([0, 0, -30])
translate([-18.1, -18.1, -0.759]) cube(size = [36.2, 36.2, 1.519], center = false);
rotate([0, 0, -30])
translate([-18.1, -18.1, -0.095]) cube(size = [19.835, 36.2, 0.19], center = false);
}
union() {
rotate([0, 0, -23])
translate([-18.1, 1.352, -18.1]) cube(size = [36.2, 16.748, 18.86], center = false);
translate([0.162, -18.1, -0.57]) cube(size = [17.938, 19.682, 1.139], center = false);
}
}
rotate([0, 0, -23])
translate([-18.1, 1.352, -0.095]) cube(size = [36.2, 16.748, 0.348], center = false);
rotate([-180, 0, 23])
translate([-18.1, 1.352, -0.759]) cube(size = [36.2, 16.748, 1.519], center = false);
}
}
translate([-1.262, -4.81, -0.759])
cylinder(h = 1.519, r1 = 0.126, r2 = 0.126, center = false, $fn = 12);
intersection() {
difference() {
translate([0.162, -1.582, -0.759]) cube(size = [1.209, 3.165, 1.519], center = false);
translate([1.378, 0, -0.759])
cylinder(h = 18.86, r1 = 0.708, r2 = 0.708, center = false, $fn = 12);
}
union() {
rotate([-180, 0, 30])
translate([-18.1, -1.096, -18.1]) cube(size = [36.2, 1.943, 17.341], center = false);
translate([1.369, 0.002, -18.1])
cylinder(h = 18.86, r1 = 0.886, r2 = 0.886, center = false, $fn = 12);
}
}
intersection() {
translate([-0.534, -18.1, 0.253]) cube(size = [0.253, 16.518, 0.506], center = false);
rotate([0, 0, -30])
translate([-18.1, -18.1, 0.253]) cube(size = [19.835, 17.004, 0.506], center = false);
}
intersection() {
difference() {
translate([-18.1, -5, -18.1]) cube(size = [17.819, 23.1, 36.2], center = false);
translate([-0.666, -4.616, -18.1])
cylinder(h = 18.86, r1 = 0.132, r2 = 0.132, center = false, $fn = 12);
}
union() {
rotate([0, 0, -30])
translate([1.735, -18.1, -0.57]) cube(size = [16.365, 36.2, 0.316], center = false);
rotate([0, 0, -30])
translate([1.735, -18.1, 0.253]) cube(size = [16.365, 36.2, 0.506], center = false);
}
}
translate([-0.534, -4.747, -0.759]) cube(size = [0.253, 2.331, 0.506], center = false);
intersection() {
union() {
rotate([0, 0, -30])
translate([-18.1, 0.625, -0.759]) cube(size = [19.835, 0.222, 1.519], center = false);
rotate([0, 0, -30])
translate([-18.1, 0.847, -18.1]) cube(size = [19.835, 17.253, 17.341], center = false);
translate([-0.534, -1.582, 0.253]) cube(size = [0.253, 3.998, 17.847], center = false);
rotate([-180, 0, 30])
translate([-18.1, 0.847, -0.759]) cube(size = [36.2, 17.253, 1.519], center = false);
}
difference() {
union() {
translate([-0.534, -1.582, -0.759]) cube(size = [0.519, 19.682, 1.519], center = false);
translate([-0.534, -2.247, -0.759]) cube(size = [0.253, 4.662, 0.506], center = false);
}
union() {
rotate([-180, 0, 30])
translate([-18.1, -1.096, -0.759]) cube(size = [36.2, 1.943, 1.519], center = false);
rotate([-180, 0, 23])
translate([-18.1, 1.352, -0.759]) cube(size = [36.2, 16.748, 18.86], center = false);
}
}
}
translate([-1.371, -5, -0.759]) cube(size = [1.091, 0.253, 1.519], center = false);
difference() {
intersection() {
difference() {
difference() {
translate([-0.534, 2.247, -18.1]) cube(size = [18.634, 2.753, 36.2], center = false);
translate([-0.534, 3.249, -0.253]) cube(size = [18.634, 1.498, 0.506], center = false);
}
union() {
rotate([0, 0, -30])
translate([-2.886, 3.665, -0.253]) cube(size = [20.986, 14.435, 18.353], center = false);
translate([-0.534, 2.416, -18.1]) cube(size = [18.634, 0.665, 18.353], center = false);
}
}
translate([-1.371, 2.247, -0.759]) cube(size = [1.091, 15.853, 1.519], center = false);
}
intersection() {
union() {
difference() {
translate([-0.534, 3.249, -18.1]) cube(size = [0.253, 0.665, 36.2], center = false);
rotate([0, 0, -30])
translate([-2.886, -18.1, -18.1]) cube(size = [20.986, 21.765, 36.2], center = false);
}
translate([-1.371, 4.082, 0.253]) cube(size = [1.091, 0.665, 0.506], center = false);
}
union() {
difference() {
translate([0, 0, 0]) sphere(r = 54.3, $fn = 12);
rotate([0, 0, -30])
translate([-18.1, -18.1, -0.253]) cube(size = [15.214, 21.765, 1.013], center = false);
}
translate([-1.261, 4.81, -18.1])
cylinder(h = 18.86, r1 = 0.126, r2 = 0.126, center = false, $fn = 12);
}
}
}
intersection() {
difference() {
intersection() {
translate([-1.371, -18.1, -0.759]) cube(size = [1.091, 23.1, 1.519], center = false);
union() {
rotate([0, 0, -30])
translate([-18.1, -18.1, -0.759]) cube(size = [36.2, 36.2, 0.506], center = false);
translate([-1.371, 3.914, -0.253]) cube(size = [1.091, 1.087, 1.013], center = false);
}
}
union() {
rotate([0, 0, -23])
translate([-18.1, -18.1, -0.759]) cube(size = [36.2, 19.452, 0.506], center = false);
translate([-0.663, 4.617, -18.1])
cylinder(h = 18.86, r1 = 0.13, r2 = 0.13, center = false, $fn = 12);
}
}
union() {
rotate([0, 0, -30])
translate([-2.886, 3.665, 0.253]) cube(size = [20.986, 14.435, 17.847], center = false);
translate([-0.534, -18.1, -0.759]) cube(size = [0.253, 22.182, 1.013], center = false);
rotate([0, 0, -30])
translate([-2.886, 3.665, -0.759]) cube(size = [20.986, 14.435, 0.506], center = false);
translate([-0.534, 4.082, 0.253]) cube(size = [18.634, 0.918, 17.847], center = false);
translate([-1.261, 4.81, -18.1])
cylinder(h = 18.86, r1 = 0.126, r2 = 0.126, center = false, $fn = 12);
translate([-0.534, 2.247, -18.1]) cube(size = [18.634, 15.853, 17.847], center = false);
translate([-1.371, 4.747, -18.1]) cube(size = [19.471, 0.253, 36.2], center = false);
}
}
}
}
