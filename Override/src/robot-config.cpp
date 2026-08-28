#include "robot-config.h"

vex::brain Brain;
vex::controller Controller1 = vex::controller(vex::primary);

vex::motor LeftFront = vex::motor(vex::PORT1, vex::ratio6_1, false);
vex::motor LeftMiddle = vex::motor(vex::PORT2, vex::ratio18_1, false);
vex::motor LeftBack = vex::motor(vex::PORT3, vex::ratio6_1, false);
vex::motor RightFront = vex::motor(vex::PORT8, vex::ratio6_1, false);
vex::motor RightMiddle = vex::motor(vex::PORT9, vex::ratio18_1, false);
vex::motor RightBack = vex::motor(vex::PORT10, vex::ratio6_1, false);

vex::motor Intake1 = vex::motor(vex::PORT11, vex::ratio6_1, false);
vex::motor Intake2 = vex::motor(vex::PORT19, vex::ratio18_1, false);
vex::motor Intake3 = vex::motor(vex::PORT20, vex::ratio18_1, false);
vex::motor LowHopper = vex::motor(vex::PORT21, vex::ratio18_1, false);
vex::motor HighHopper = vex::motor(vex::PORT21, vex::ratio18_1, false);

vex::rotation TrackingFB = vex::rotation(vex::PORT21);
vex::rotation TrackingLR = vex::rotation(vex::PORT21);
vex::inertial InertialSensor1 = vex::inertial(vex::PORT21);
vex::inertial InertialSensor2 = vex::inertial(vex::PORT21);
vex::optical RightOptical = vex::optical(vex::PORT21);
vex::optical LeftOptical = vex::optical(vex::PORT21);
vex::distance BackLaser = vex::distance(vex::PORT21);
vex::distance HopperLaser = vex::distance(vex::PORT21);
vex::distance FrontLeftLaser = vex::distance(vex::PORT21);
vex::distance FrontRightLaser = vex::distance(vex::PORT21);
vex::distance LeftLaser = vex::distance(vex::PORT21);
vex::distance RightLaser = vex::distance(vex::PORT21);
vex::gps Gps = vex::gps(vex::PORT21);
