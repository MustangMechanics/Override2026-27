#include "vex.h"
#include "movement.h"
#include "robot-config.h"

void stopDriving() {
    LeftFront.stop();
    LeftMiddle.stop();
    LeftBack.stop();
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();

}

void setBrakeMode(vex::brakeType mode) {
    LeftFront.setBrake(mode);
    LeftMiddle.setBrake(mode);
    LeftBack.setBrake(mode);
    RightFront.setBrake(mode);
    RightMiddle.setBrake(mode);
    RightBack.setBrake(mode);
}

double convertDegreesToInches(double degrees) {
    double inches = degrees / 58.76; // changed from 58.76 to 21.16 based on testing
    return inches;
}


double convertInchesToDegrees(double inches) {
    double degrees = inches * 58.76; // changed from 58.76 to 21.16 based on testing
    return degrees;
}


void tankDrive(double leftSpeed, double rightSpeed) {
   
    leftSpeed = leftSpeed * 0.12;
    rightSpeed = rightSpeed * 0.12;

    LeftFront.spin(vex::reverse, leftSpeed, vex::volt);
    LeftMiddle.spin(vex::reverse, leftSpeed, vex::volt);
    LeftBack.spin(vex::reverse, leftSpeed, vex::volt);

    RightFront.spin(vex::forward, rightSpeed, vex::volt);
    RightMiddle.spin(vex::forward, rightSpeed, vex::volt);
    RightBack.spin(vex::forward, rightSpeed, vex::volt);

}


void driveForward(double inches, double speed) {
    printf("Drive forward\n");
    double currentPosition = (RightMiddle.position(vex::degrees)); // Get the current position of the right middle motor in degrees
    double startingPosition = convertDegreesToInches(currentPosition); // Convert the current position to inches 
    double travelDegrees = (inches * 58.76); // changed from 58.76 to 21.16 based on testing
    double endPosition = currentPosition + travelDegrees;
    double endPositionInches = convertDegreesToInches(endPosition);
    
        
    long startTime = vex::timer::system();
    
    printf("Starting Position: %f degrees, End Position: %f degrees, %f inches\n", travelDegrees, endPosition, inches);
    // add number of degrees needed to turn to the current position to get the end position
    tankDrive(speed, speed);
    
    while (true) {
        currentPosition = (RightMiddle.position(vex::degrees));
        double error = endPosition - currentPosition;
        if (fabs(error) < 29.38) { // 10.58 (changed from 29.38) degrees is 0.5 inches b/c changed 58.76 to 21.16 based on testing
            break;
        }
        printf("Error: %f degrees  Current position: %f degrees  End position: %f degrees\n ", error, currentPosition, endPosition);
        vex::task::sleep(10);
    }
    

    stopDriving();
    long endTime = vex::timer::system();
    currentPosition = (RightMiddle.position(vex::degrees));
    printf("Drive Time: %lu ms  Actual distance: %f inches\n", endTime - startTime, currentPosition - startingPosition);

//void moveToHeight(double inches) {}
}


void driveTurn(double degrees, double speed) {
    
    double currentPosition = InertialSensor.rotation(vex::degrees); 
    double startingPosition = currentPosition;
    double endPosition = currentPosition + degrees;
        
    long startTime = vex::timer::system();
    
    printf("Starting Position: %f degrees, End Position: %f degrees\n", degrees, endPosition);
    // add number of degrees needed to turn to the current position to get the end position
    tankDrive(speed, -speed);
    
    while (true) {
        currentPosition = InertialSensor.rotation(vex::degrees);
        double error = endPosition - currentPosition;
        if (fabs(error) < 2) { // 10.58 (changed from 29.38) degrees is 0.5 inches b/c changed 58.76 to 21.16 based on testing
            break;
        }
        printf("Error: %f degrees  Current position: %f degrees  End position: %f degrees\n ", error, currentPosition, endPosition);
        vex::task::sleep(10);
    }
    
    stopDriving();
    long endTime = vex::timer::system();
    currentPosition = InertialSensor.rotation(vex::degrees);
    printf("Drive Time: %lu ms  Actual distance turned: %f degrees\n", endTime - startTime, currentPosition - startingPosition);

}



