$fn=60;

use <gcb_files/keyboards/cherry/keycap_mount.scad>;
use <gcb_files/cap.scad>;

// thickness of the wall.
wall_thickness = 1;

// diameter of the plunger. ideally in mm
plunger_diameter = 80;
// height of the plunger. ideally in mm
plunger_height = 11;

// concave top? this will only work with diameter==22. ...can't be bothered with math right now.
plunger_concave = false;

// put a cross under the cap for reinforcement. it was done very quick and dirty just so you can add a better one if you need by looking at the code.
plunger_reinforcement = true;

module wall_box() {
	for (R = [0:1]) {
		rotate(90*R) {
			for (F = [-1:2:1]) {
				translate([0,F*21,wall_thickness/2])
					cube([(42)+(wall_thickness*2),wall_thickness*2,wall_thickness], center=true);
			}
		}
	}
}

module mx_mount_stabilizers(solid) {
	for (R = [0:1]) {
			rotate(90*R) {
				for (F = [-1:2:1]) {
					translate([21,F*12,0]) {
						if (solid == true) {
							mx_mount_solid();
						} else {
							mx_mount();
						}
					}
				}
			}
		}
}

module cherry_mx_plunger(d, h, concave, reinforcement){
	// rotate it upside down for 1) print easier, 2) look better on thingverse screen shot
	plunger(d=d, h=h, concave=concave);
	union() {
		mx_mount();
		*difference() {
			wall_box();
			mx_mount_stabilizers(true);
		}
		*mx_mount_stabilizers(false);
		if( true == plunger_reinforcement ) {
			translate([0,0, (wall_thickness/2) ]) {
				for (R = [0:30:179]) {
					rotate([0,0,R]) {
						difference() {
							cube([d+(wall_thickness*2),wall_thickness*3,wall_thickness], center=true);
							mx_mount_solid();
						}
					}
				}
			}
		}
	}
}


cherry_mx_plunger( d=plunger_diameter, h=plunger_height, concave=plunger_concave, reinforcement=plunger_reinforcement);
