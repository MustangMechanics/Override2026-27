/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       brian                                                     */
/*    Created:      8/28/2026, 3:56:50 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "controller.h"
#include "pneumatics.h"
#include "movement.h"
#include "test.h"
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void leftAuton(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  driveForward(3, 25);
  toggleOut();
  driveForward(-4, 25);
  driveForward(5.5, 25);
  driveTurn(-85, 25);
  driveForward(-6, 25);
  liftUp(50);
  vex::task::sleep(300);
  tiltOut();
  vex::task::sleep(500);
  liftDown(50);
  vex::task::sleep(1000);
  liftStop();
  openClaw();

  // ..........................................................................
}

void rightAuton(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  driveForward(3, 25);
  toggleOut();
  driveForward(-4, 25);
  driveForward(5.5, 25);
  driveTurn(90, 25);
  driveForward(-8, 25);
  liftUp(50);
  vex::task::sleep(300);
  tiltOut();
  vex::task::sleep(500);
  liftDown(50);
  vex::task::sleep(1000);
  liftStop();
  openClaw();
}  
void autonomous(void) {
  initializeExpectedHeading(); //Leave at start;
  // ..........................................................................
  // Insert autonomous user code here.
  driveAtSpeed(30);

  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(leftAuton);
  //Competition.autonomous(rightAuton);
  Competition.drivercontrol(driver);
  //printf("Hello VEX World! !\n");

  // Run the pre-autonomous function.
  pre_auton();
  initPneumatics();
  closeClaw();
  
  
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
