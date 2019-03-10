
bolt_rad = 2.55;
driver_rad = 7.5;
base_height = 5;
full_height = 30;

module bothole(x, y) {
    union() {
        translate([x, y, -5])
            cylinder(r=bolt_rad, h=(full_height + 20));
        translate([x, y, 3])
            cylinder(r1=bolt_rad, r2=driver_rad, h=9);
        translate([x, y, 11.98])
            cylinder(r=driver_rad, h=50);
    }
}

module tophole(x, y) {
    translate([0, 0, full_height])
        mirror([0,0,1])
            bothole(x, y);
}

module hole2(dx, dy) {
    translate([dx*20.86, dy*20.86, -5])
        cylinder(r=2.55, h=(full_height + 10));
    translate([dx*32, dy*32, base_height])
        cylinder(r=22, h=(full_height + 10));
}

difference() {
    cylinder(r=40, h=full_height);
    tophole(29.5, 0);
    tophole(-29.5, 0);
    tophole(0, 29.5);
    tophole(0, -29.5);
    hole2(-1, 1);
    hole2(1, 1);
    hole2(1, -1);
    hole2(-1, -1);
}

