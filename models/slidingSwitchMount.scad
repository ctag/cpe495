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
    holePlate=exteriorSize*1.5;
	holeDiam = 3;
    union() {
        %cube([wallThickness, exteriorSize, exteriorSize]); // Face plate
        // Shift bottom mounting plate
		translate([0, -((holePlate-exteriorSize)/2), 0])
            difference() {
                cube([exteriorSize, holePlate, wallThickness]); // Bottom plate
				// Distribute holes
				translate([wallThickness, wallThickness, 0]) {
					for (xi=[0:1]) {
						for (yi=[0:1]) {
							translate([xi*(exteriorSize-(wallThickness*2)), yi*(holePlate-(wallThickness*2)), 0])
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



difference() {
    mountShell();
    mountCavity();
}

//minkowski() {
//	cylinder(h=wallThickness, r=2);
//	mountShell();
//}




















