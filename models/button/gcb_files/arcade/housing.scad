$fn = 60;
use <../torus.scad>
use <../threads.scad>
use <cap.scad>
use <cherry_mx_cap.scad>
use <../keyboards/cherry/switch_mx.scad>

// thickness of the wall
wall_thickness = 1;


// width of the plunger that will go inside
housing_plunger_diameter = 27;
/*
// TODO: rework this so that there is a internal guide for the plunger
//       without affecting the height of the bezel.
//       right now the bezel is the guide so it must be as tall
// the size of the threaded body
*/

// the actual diameter of the main body. this is the part that slides trhu the cabinet hole
housing_diameter = 30;
// how long to make the hole thing, this measures from the base of the plunger to the bottom of the threaded body
housing_height = 17;

// the exterior diamter of the bezel
housing_bezel_diameter = 35;
// the total bezel height
housing_bezel_height = 5;
// how much should the bezel cover the cap
housing_bezel_bleed = 1;

// pitch for the metric thead. edit source if you need imperial.
housing_metrich_thread_pitch = 3.3;

// threading option. set to false to use snap-in. warning, it is buggy.
housing_use_threading = false;

// the depth of the panel that will be used for snap-in. TODO improve the design using another var for the lenght of the cut out. that way, if using a very thin board (e.g. metal plate) we can make the cut and the snap triangle longer, so that we still have enought bending on the arm to move it. Also add the traditional 3 level to the snap triangle so that it work with panel irregularities/multiple close sizes/etc.
housing_snapin_height = 7;

/** convenience module. hollow cylinder.
also work around lack of diameter in older openscad versions.
@params h=height, d=external diameter, id=internal diameter
@use global wall_thickness
*/
module hollow_cylinder(h,d,id){
	difference(){
		cylinder(h=h, r=d/2);
		translate([0,0,-wall_thickness])
			cylinder(h=h+wall_thickness*2, r=id/2);
	}
}


module housing(d, h, plunger_d, bezel_d, bezel_h, bezel_bleed, use_threads, thread_pitch, snapin_height){

	//1. main body. a tube with the thickness of the wall
	// TODO; this have to be threaded
	//color("blue") hollow_cylinder(h=h, d=d, id=d-wall_thickness);

	//2. the plunger guide and bezel
	//2.1 bezel
	translate([0,0,bezel_h/2 - bezel_bleed]){
		color("gold")
		quarter_torus(r=bezel_h/2, d=bezel_d);
		color("green")
		hollow_cylinder(h=bezel_h/2, d=bezel_d, id=plunger_d);
	}
	//2.2 guide. fill the gap from the torus to the main body
	color("silver")
	translate( [0,0, - bezel_bleed] )
	hollow_cylinder( h=bezel_h, d=bezel_d-bezel_h, id=plunger_d );

	//1.(again) main body.
	if( true == use_threads ){
		// main body, threading... fingers crossed
		translate([0,0,bezel_h - bezel_bleed ])
		difference(){
			metric_thread(internal=false,diameter=d+wall_thickness, pitch=thread_pitch, length=h - bezel_h );
			translate([0,0, - wall_thickness ])
				cylinder(h=(h-bezel_h)+2*wall_thickness, r=10);
					// TODO: i have no idea who to make the pitch thing take into account the diameter i want
		}
	}else{
		//main body, snap-in
		color("blue")
		difference(){
			union(){
				cylinder(h=h, r=d/2);
				translate([0,0,bezel_h-bezel_bleed]){
					difference(){
						translate([0,0,snapin_height])
							cylinder(h=2*wall_thickness, r1=d/2+1.5*wall_thickness, r2=d/2);
						translate([-d,-d,0])
							cube([d-d/6+wall_thickness,d*2,snapin_height+3*wall_thickness]);
						translate([d/6,-d,0])
							cube([d-d/6+wall_thickness,d*2,snapin_height+3*wall_thickness]);
					}
				}
			}
			// move to after the bezel base (as it will rest on top of the panel being snapped)
			translate([0,0,bezel_h-bezel_bleed]){
				translate([-d/6,-d/2,0]) cube([wall_thickness,d,snapin_height+3*wall_thickness]);
				translate([d/6,-d/2,0]) cube([wall_thickness,d,snapin_height+3*wall_thickness]);
				translate([-d/6,-d/2-wall_thickness,snapin_height+2*wall_thickness]) cube([d/3+wall_thickness,d+2*wall_thickness,1]);
			}
			translate([0,0,-wall_thickness])
				cylinder(h=h+2*wall_thickness, r=d/2-wall_thickness/2);
		}

	}
}



housing(d=housing_diameter, h=housing_height, plunger_d=housing_plunger_diameter, bezel_d=housing_bezel_diameter, bezel_h=housing_bezel_height, bezel_bleed=housing_bezel_bleed, thread_pitch=housing_metrich_thread_pitch, use_threads=housing_use_threading, snapin_height=housing_snapin_height);



