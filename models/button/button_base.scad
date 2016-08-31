
/*
 * Includes
 */
use <gcb_files/keyboards/cherry/keycap_mount.scad>;
use <gcb_files/arcade/cap.scad>;

$fn = 60;

base_height = 10;
base_diameter = 100;
bolt_count = 6;
rounding_radius = 3;

// thickness of the wall.
wall_thickness = 1;

// diameter of the plunger. ideally in mm
plunger_diameter = 80;

// height of the plunger. ideally in mm
plunger_height = 6;

// put a cross under the cap for reinforcement. it was done very quick and dirty just so you can add a better one if you need by looking at the code.
plunger_reinforcement = true;

module roundTop_cylinder(D, H, R) {
	//R = rounding_radius;
	difference() {
		minkowski() {
			cylinder(h=(H-R), d=(D-(R*2)), center=false);
			sphere(r=R);
		}
		translate([0,0,-R])
			cylinder(h=R, d=D);
	}
}

module switch_socket(H)
{
	clip_depth = 0.5;
	clip_width = 8;
	clip_height = 2;
	translate([0, 0, (H/2)]) {
		union() {
			cube([14, 14, H], center=true);
			for (r = [0:1]) {
				for (i = [-1:2:1]) {
					rotate([0, 0, r*90])
						translate([(i)*(7+(clip_depth/2)), 0, (H/2)-(clip_height/2)-1.75])
							cube([0.5, 8, 2], center=true);
				}
			}
		}
	}
}

module wire_channel()
{
	channel_length = 60;
	channel_diam = 3.5;
	channel_offset = 0.4;
	translate([(channel_length/2), 0, (channel_diam/2)+channel_offset]) {
		//cube([channel_length, channel_width, channel_diam], center=true);
		rotate([0, 90, 0]) {
			cylinder(h=channel_length, d=channel_diam, center=true);
		}
	}
}

module anti_warp(D, W, H)
{
	extra = (W*2);
	for (x = [-1:0.5:1]) {
		translate([0, x*((D/2)+W), (H/2)]) 
		cube([D+extra, W, H], center=true);
	}
	for (y = [-1:0.5:1]) {
		translate([y*((D/2)+W), 0, (H/2)]) 
		cube([W, D+extra, H], center=true);
	}
}

module bottom_threads(D, H)
{
	rotate([0, 0, 360/(bolt_count*2)]) { // Avoid collision with wire channel
		for (r = [0:(1/bolt_count):1]) { // 0->1 in fractions
			rotate([0, 0, r*360]) { // Spin item around origin
				translate([(base_diameter/2)-5, 0, (H/2)]) { 
					union() { // Join the cylinder and cone
						cylinder(h=H, d=D, center=true); // threads
						translate([0, 0, -((H/2)-2)]) { // cone to fit bolt head in
							cylinder(h=4, d1=(D*4), d2=D, center=true);
						}
					}
				}
			}
		}
	}
}

module button_base()
{
	difference() {
		cylinder(d=base_diameter, h=base_height);
		//roundTop_cylinder(base_diameter, base_height);
		switch_socket(base_height);
		wire_channel();
		anti_warp(base_diameter, 1, 0.4);
		bottom_threads(2.90, base_height);
	}
}

module button_retainer()
{
	_height = 6;
	_width = 9;
	difference() {
		roundTop_cylinder((base_diameter), _height, 2);
		cylinder(d=(base_diameter-(_width*2)), h=_height);
		cylinder(d=(base_diameter-((_width-3)*2)), h=_height-2);
		translate([0, 0, -3])
			bottom_threads(3, base_height);
	}
}




module button_cap(d, h, reinforcement){
	d=plunger_diameter;
	h=plunger_height;
	reinforcement=plunger_reinforcement;
	depth_offset=(plunger_height-2);
	// Overall item
	union() {
		
		// Main plunger body
		difference() {
			plunger(diameter=d, height=h, edge_radius=4);
			translate([0, 0, (-depth_offset)])
				cylinder(d1=30, d2=35, h=depth_offset);
		}
		
		// Lower support bars and mx socket
		*translate([0, 0, (-depth_offset)]) {
			union() {
				mx_mount();
				if( true == plunger_reinforcement ) {
					translate([0,0, (wall_thickness/2) ]) {
						for (R = [0:1]) {
							rotate([0,0,R*90]) {
								difference() {
									cube([35,wall_thickness*4,wall_thickness], center=true);
									mx_mount_solid();
								}
							}
						}
					}
				}
			}
		}
		
		// Upper support bars
		union() {
			if( true == plunger_reinforcement ) {
				translate([0,0, (wall_thickness/2) ]) {
					for (R = [0:1]) {
						rotate([0,0,R*90]) {
							difference() {
								cube([d,wall_thickness*4,wall_thickness], center=true);
								translate([0, 0, -(wall_thickness/2)])
								cylinder(d=35, h=wall_thickness);
							}
						}
					}
				}
			}
		}
		
		// Retainer lip
		difference() {
			cylinder(d1=d, d2=(d+(2*2)), h=3);
			cylinder(d1=40, d2=44, h=3);
		}
	}
}




module preview()
{
	color("blue") {
		button_base();
	}
	color("green") {
		translate([0, 0, base_height+2]) {
			button_retainer();
		}
	}
	color("red") {
		translate([0, 0, base_height+2]) {
			rotate([180, 0, 0]) {
				button_cap();
			}
		}
	}
}

module laser_base()
{
	difference() {
		circle(d=base_diameter);
		rotate([0, 0, 360/(bolt_count*2)]) { // Avoid collision with wire channel
			for (r = [0:(1/bolt_count):1]) { // 0->1 in fractions
				rotate([0, 0, r*360]) { // Spin item around origin
					translate([(base_diameter/2)-5, 0, 0]) { 
						circle(d=2.9); // threads
					}
				}
			}
		}
	}
}







//preview();
//button_base();
//button_retainer();
button_cap();
//laser_base();

