
$fn = 1000;

module roundTop_cylinder(D, H, R) {
	difference() {
		minkowski() {
			cylinder(h=(H-R), d=(D-(R*2)), center=false);
			sphere(r=R);
		}
		translate([0,0,-R])
			cylinder(h=R, d=D);
	}
}

roundTop_cylinder(100, 13.5, 3);
