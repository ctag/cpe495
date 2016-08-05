$fn = 200;
use <../torus.scad>
use <../threads.scad>

use <cherry_mx_cap.scad>

use <housing.scad>
use <../keyboards/cherry/switch_mx.scad>

// thickness of the wall.
wall_thickness = 1;


// depth of the plate. official spec says "0.06 +/- 0.006" no unit given.
plate_depth = 1.52;

//%cherry_mx_plunger( d=27, h=5, concave=false, reinforcement=false);

union(){
	housing(d=30, h=17, plunger_d=27, bezel_d=37, bezel_h=5, bezel_bleed=1, use_threads=false, snapin_height=7);

	translate([0,0,1 + 4 + 5.5 + 0.6 + plate_depth/2]){ // switch offset + steam + top + height of tab
		difference(){
			// the circular base
			cylinder(h=plate_depth, r=30/2-0.1, center=true);
			// the hole for the switch TODO: should we bother about space to remove top without removing bottom? nah.. idiotic since the switch is in a tube. easier to remove.
			cube([13.97, 13.97, 10], center=true);
			// space for the clips
			translate([wall_thickness/2,15,0])
				cube([(30/6)*2+wall_thickness,5,20], center=true);
			translate([wall_thickness/2,-15,0])
				cube([(30/6)*2+wall_thickness,5,20], center=true);
		}
	}
}

/* TODO:
// reinforcement
translate([0,0,1 + 4 + 5.5 + 5.5]){ // switch offset + steam + top + height of tab
			cube([(30/6)*2+wall_thickness,5,1], center=true);
}
*/

//%translate([0,0,1]) mirror([0,0,1]) rotate([0,0,90]) cherry_mx_switch();
