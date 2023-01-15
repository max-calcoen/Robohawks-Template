#pragma once
#include "vex.h" // import robot
#include "classes/autonClass.h" // to create the autons

extern Auton redRoller;
extern Auton redNoRoller;
extern Auton blueRoller;
extern Auton blueNoRoller;
extern Auton redSoloWinpoint;
extern Auton blueSoloWinpoint;
extern Auton skills;

// start touching roller in the middle
Auton redRoller("roller", "roller, 2 disks", 100, 100, 0, true, [] {
  
});

// start top left of right tile
Auton redNoRoller("no roller", "roller, 6 disks", 100, 100, 90, true, [] {
 
});

Auton redSoloWinpoint("winpoint", "2 rollers, 2 disks", 100, 100, 0, true, [] {

});

Auton blueRoller("roller", "roller, 2 disks", 100, 100, 0, false, [] {
  
});

Auton blueNoRoller("no roller", "2 disks", 100, 100, 90, false, [] {
  
});

Auton blueSoloWinpoint("winpoint", "2 rollers, 2 disks", 100, 100, 0, false, [] {
  
});

Auton skills("skills", "dev", 0, 0, 0, true, [] {
  
});