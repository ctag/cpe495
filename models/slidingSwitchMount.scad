// Horizontal Mechanical Switch Mount
// Christopher Bero - csb0019@uah.edu
// CPE 496 - 2016


interiorSize = 14; // Size of one side of the mounting hold for the switch
exteriorSize = 20; // Size of area around mounting hole
wallThickness = (exteriorSize - interiorSize)/2; // General wall thickness

// Area to be subtracted from the shell to make a mount point for the switch
module mountCavity()
{
    translate([wallThickness, wallThickness, 0]) {
        cube([interiorSize, interiorSize, wallThickness]);
    }
}

// Exterior profile of the entire mount
module mountShell()
{
    
}

mountCavity();