// Horizontal Mechanical Switch Mount
// Christopher Bero - csb0019@uah.edu
// CPE 496 - 2016

$fs = 1; // Minimum fragment size
interiorSize = 14; // Size of one side of the mounting hold for the switch
exteriorSize = 20; // Size of area around mounting hole
wallThickness = (exteriorSize - interiorSize)/2; // General wall thickness

// Area to be subtracted from the shell to make a mount point for the switch
module mountCavity()
{
    translate([0, wallThickness, wallThickness]) {
        cube([wallThickness, interiorSize, interiorSize]);
    }
}

// Exterior profile of the entire mount
module mountShell()
{
    holePlate=exteriorSize*2;
	holeDiam = 4;
	holeOffset = (wallThickness + (holeDiam/2));
    union() {
        *cube([wallThickness, exteriorSize, exteriorSize]); // Face plate
		translate([0, 0, (exteriorSize-wallThickness)])
			cube([exteriorSize, exteriorSize, wallThickness]); // Face plate
        // Shift bottom mounting plate
		translate([0, -((holePlate-exteriorSize)/2), 0])
            difference() {
                cube([exteriorSize, holePlate, wallThickness]); // Bottom plate
				// Distribute holes
				translate([holeOffset, holeOffset, 0]) {
					for (xi=[0:1]) {
						for (yi=[0:1]) {
							translate([xi*(exteriorSize-(holeOffset*2)), yi*(holePlate-(holeOffset*2)), 0])
							cylinder(wallThickness, d=holeDiam);
						}
					}
				}
            }
        cube([exteriorSize, wallThickness, exteriorSize]); // Right plate
        translate([0, exteriorSize-wallThickness, 0]) {
            cube([exteriorSize, wallThickness, exteriorSize]); // Left plate
        }
        *cube([]); // Mounting hole plate
    }
}

module antiWarp(X, Y, Z, buffer, rows, cols)
{
	width=((X-(buffer*2))/(cols*2));
	height=((Y-(buffer*2))/(rows*2));
	translate([buffer, buffer, 0])
	{
		for (xcount = [0:(cols-1)] )
		{
			for (ycount = [0:(rows-1)])
			{
				translate([xcount*(width*2), ycount*(height*2), 0])
					cube([width, height, Z]);
			}
		}
	}
}

difference() {
    mountShell();
    *mountCavity();
	antiWarp(exteriorSize+2, exteriorSize+2, 1.5, 1, 3, 3);
}



//minkowski() {
//	cylinder(h=wallThickness, r=2);
//	mountShell();
//}




















