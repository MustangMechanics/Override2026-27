#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "vex.h"

extern vex::brain Brain;
extern vex::controller Controller1;

extern vex::motor LeftFront;
extern vex::motor LeftMiddle;
extern vex::motor LeftBack;
extern vex::motor RightFront;
extern vex::motor RightMiddle;
extern vex::motor RightBack;

extern vex::motor Intake1;
extern vex::motor Intake2;
extern vex::motor Intake3;

extern vex::rotation TrackingFB;
extern vex::rotation TrackingLR;

extern vex::optical RightOptical;
extern vex::optical LeftOptical;
extern vex::inertial InertialSensor1;
extern vex::inertial InertialSensor2;
extern vex::distance BackLaser;
extern vex::distance HopperLaser;
extern vex::distance FrontLeftLaser;
extern vex::distance FrontRightLaser;
extern vex::distance LeftLaser;
extern vex::distance RightLaser;

extern vex::gps Gps;

#endif  // ROBOT_CONFIG_H
