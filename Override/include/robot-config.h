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

extern vex::motor Intake;
extern vex::motor RightLifter;
extern vex::motor LeftLifter;

extern vex::inertial InertialSensor1;

#endif  // ROBOT_CONFIG_H
