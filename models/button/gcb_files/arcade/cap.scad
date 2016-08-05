$fn=60;

use <../torus.scad>

// thickness of the wall.
wall_thickness = 1;

// diameter of the plunger
plunger_diameter = 80;
// height of the plunger
plunger_height = 10;

// concave top? this will only work with diameter==22. ...can't be bothered with math right now.
plunger_concave =false;


/* values from happ:
(i assume their values are inches, since there is no unit...)
ext bezel diam = 1.3in (33mm)
bezel height = no idea. i will guess 0.14in (3.5mm)
plunger diam = 0.87in (22mm)
plunger height out of bezel = 0.14in (3.5mm)
plunger travel = no idea.
threaded body diam = 1.10in (27.95mm)

mounting hole diameter = 1.13in (28.7mm)
*/


//module plunger(d, h, concave){
//	dFraction=d/10;
//	dCurve=d/20;
//	translate([0,0,-wall_thickness])
//	difference(){
//		difference(){
//			union(){
//				half_torus( r=dFraction, d=d );
//				translate([0,0,-(dFraction)])
//					cylinder( h=dFraction, r=d/2 - (dFraction), center=false);
//				cylinder( h=h-(dFraction), r=d/2 , center=false);
//			}
//			*translate([0,0,wall_thickness])
//				cylinder( h=h-(dFraction), r=d/2-1 , center=false);
//		}
//		*if( true == concave ){
//			if( 22 == plunger_diameter ){
//				// trial and error concave. TODO: recall basic trigonometry...
//				translate([0,0,-d*2-1.3])
//					sphere( r=d*2);
//			}
//		}
//	}
//}

module plunger(d, h, concave){
	dFraction=d/15;
	translate([0,0,-(h-(dFraction))+wall_thickness])
		difference(){
			union(){
				half_torus( r=dFraction, d=d );
				translate([0,0,-dFraction])
					cylinder( h=dFraction, r=d/2 - dFraction, center=false);
				cylinder( h=h-(dFraction), r=d/2 , center=false);
			}
			translate([0,0,(h-wall_thickness-(dFraction))])
				cylinder( h=h-(dFraction), r=d/2-1 , center=false);
		}
}

plunger(d=plunger_diameter, h=plunger_height, concave=false);
