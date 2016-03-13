module torus(r, d){
	rotate_extrude(convexity = 10)
		translate([d/2-r, 0, 0])
			circle(r=r);
}

/** only the top portion of a torus */
module half_torus(r,d){
	difference(){
		torus( r=r, d=d );
		translate([0,0,d/2])
			cube( [d,d,d], center=true );
	}
}


/** only the top/exterior quarter */
module quarter_torus(r,d){
	difference(){
		half_torus( r=r, d=d );
		cylinder( r=d/2-r, h=d, center=true );
	}
}

/** only the exterior quarter */
module ring_torus(r,d){
	difference(){
		torus( r=r, d=d );
		cylinder( r=d/2-r, h=d, center=true );
	}
}

/** custom torums */
module custom_torus(r,d){
	rotate_extrude(convexity = 10)
		translate([d/2-r/2, 0, 0])
			child();
}


