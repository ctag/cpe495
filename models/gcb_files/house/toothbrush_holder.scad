$fn = 8;
//use <../torus.scad>
/** custom torums */
module custom_torus(r,d){
		rotate_extrude(convexity = 10)
				translate([d/2-r, 0, 0])
							child();
}

/**
does not need to be parametrized... i think.

it is made of a torus where R=14, r=elipsis( ... no idea how to describe
elipsis matematicaly at this hour of the night, so let's just say larger
side diameter=35 and smaller side diameter=13. then 5mm on the bottom cut
out.

hum... the tops are a fatter... need a way to do poly rotate extrude...
but i think that should work. let's print and see...

*/


difference(){
	// the oval torus
	translate([0,0,10])
	custom_torus(r=15/2, d=41)
		scale([1,2.69,1])
			circle(r=13/2);

	// a block in the end to cut the bottom
	translate([-50,-50,-100])
		cube([100, 100, 100]);
}
/*
13 - 35
100 - x
3500 = 13x
x = 269.
*/


