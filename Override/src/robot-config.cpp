#include "robot-config.h"

vex::brain Brain;
vex::controller Controller1 = vex::controller(vex::primary);

vex::motor LeftFront = vex::motor(vex::PORT1, vex::ratio6_1, false);
vex::motor LeftMiddle = vex::motor(vex::PORT2, vex::ratio18_1, false);
vex::motor LeftBack = vex::motor(vex::PORT3, vex::ratio6_1, false);
vex::motor RightFront = vex::motor(vex::PORT8, vex::ratio6_1, false);
vex::motor RightMiddle = vex::motor(vex::PORT9, vex::ratio18_1, false);
vex::motor RightBack = vex::motor(vex::PORT10, vex::ratio6_1, false);

vex::motor Intake = vex::motor(vex::PORT11, vex::ratio6_1, false);
vex::motor RightLifter = vex::motor(vex::PORT19, vex::ratio18_1, false);
vex::motor LeftLifter = vex::motor(vex::PORT20, vex::ratio18_1, false);

vex::inertial InertialSensor1 = vex::inertial(vex::PORT21);

