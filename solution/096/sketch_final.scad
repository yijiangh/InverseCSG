intersection() {
translate([-6, -6, -6]) cube(size = [12, 12, 12], center = false);
union() {
translate([3.571, -2.143, 3.571]) cube(size = [1.429, 4.286, 1.429], center = false);
translate([-2.143, 0.714, 3.571]) cube(size = [5.714, 1.429, 1.429], center = false);
difference() {
union() {
translate([-5, -2.143, -2.143]) cube(size = [1.429, 7.143, 2.857], center = false);
translate([-5, -3.571, 0.714]) cube(size = [7.143, 8.571, 1.429], center = false);
}
translate([-18.1, -3.571, -0.714]) cube(size = [18.814, 7.143, 2.857], center = false);
}
translate([3.571, -2.143, -0.714]) cube(size = [1.429, 1.429, 4.286], center = false);
translate([-5, -2.143, -2.143]) cube(size = [10, 1.429, 1.429], center = false);
difference() {
union() {
translate([-2.143, -5, -5]) cube(size = [4.286, 1.429, 7.143], center = false);
translate([-2.143, -5, -5]) cube(size = [1.429, 7.143, 10], center = false);
}
translate([-2.143, -5, -3.571]) cube(size = [2.857, 5.714, 8.571], center = false);
}
}
}
