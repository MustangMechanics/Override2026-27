#include "vex.h"
#include "movement.h"
#include "robot-config.h"

using namespace vex;

//added 11-13
double D = 3.25;
double pi = 3.14159265358979323846;
double C = pi * D;
double drivingToDriven = 3.0/5.0; //assumed ratio for outer motors (non-middle)
double expectedHeading;
double motorPositions[6] = {0};
double startPositions[6] = {0};
double minSpeed = 7; //min voltage to beat Fs

void initializeExpectedHeading() {
    expectedHeading = InertialSensor.rotation(deg);
}
void bound(double& value, double lo, double hi) {
    if(value > hi) {
        value = hi;
    }
    if(value < lo) {
        value = lo;
    }
}

//added 11-13
void updateStartPositions() { //at start of user function
    startPositions[0] = -LeftFront.position(rotationUnits::rev);
    startPositions[1] = -LeftMiddle.position(rotationUnits::rev);
    startPositions[2] = -LeftBack.position(rotationUnits::rev);
    startPositions[3] = RightFront.position(rotationUnits::rev);
    startPositions[4] = RightMiddle.position(rotationUnits::rev);
    startPositions[5] = RightBack.position(rotationUnits::rev);
    motorPositions[0] = -LeftFront.position(rotationUnits::rev);
    motorPositions[1] = -LeftMiddle.position(rotationUnits::rev);
    motorPositions[2] = -LeftBack.position(rotationUnits::rev);
    motorPositions[3] = RightFront.position(rotationUnits::rev);
    motorPositions[4] = RightMiddle.position(rotationUnits::rev);
    motorPositions[5] = RightBack.position(rotationUnits::rev);
}

double getInches() { //used for straight drive detection accuracy, always with updateStartPositions() first (before the loop)
    motorPositions[0] = -LeftFront.position(rotationUnits::rev);
    motorPositions[1] = -LeftMiddle.position(rotationUnits::rev);
    motorPositions[2] = -LeftBack.position(rotationUnits::rev);
    motorPositions[3] = RightFront.position(rotationUnits::rev);
    motorPositions[4] = RightMiddle.position(rotationUnits::rev);
    motorPositions[5] = RightBack.position(rotationUnits::rev);
    double differences[6];
    for(int i=0; i<=5; i++) {
        differences[i] = motorPositions[i] - startPositions[i];
    }
    double avgRevs = (differences[0] + differences[3]) / 2.0;
    double output = avgRevs * drivingToDriven * C;
    return output;
}

void stopDriving() {
    LeftFront.stop();
    LeftMiddle.stop();
    LeftBack.stop();
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();

}

void driveBrake() {
    LeftFront.stop(brake);
    LeftMiddle.stop(brake);
    LeftBack.stop(brake);
    RightFront.stop(brake);
    RightMiddle.stop(brake);
    RightBack.stop(brake);
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

void inchDrive(double distance, double speed, long maxTime) {
    updateStartPositions(); 
    // Assuming 360 ticks per revolution and 3.25 inch wheels
    double startPos = getInches(); //inches
    double targetPos = startPos + distance; //inches
    double currentPos = startPos;

    double driveStartHeading = expectedHeading; //degrees;
    double currentHeading = driveStartHeading;

    double headingError = 0.0;
    double prevHeadingError = 0.0;

    double kP = 3;
    double kI = 0.01; // 0.005 – 0.05
    double kD = 300; //account for time division

    double time = Brain.Timer.time(msec);
    double prevTime = time - 20.0;

    double dt = 20.0;

    double kHP = 1; //turn correction
    double KHD = 50;

    double error = distance; //inches
    double prevError = distance; //inches
    double accuracy = 0.5; // Acceptable error in inches

    double derivative = 0.0;
    double integral = 0.0;

    double hD = 0.0; //heading integral and derivative
    double hP = 0.0;

    double turnOffset = 0.0; //turn offset

    double output;
    double right = 0.0;
    double left = 0.0;

    long endTime = vex::timer::system() + maxTime;


    while(fabs(error) > accuracy && vex::timer::system() < endTime) {
        currentPos = getInches();
        error = (targetPos - currentPos);
        time = Brain.Timer.time(msec);
        dt = time - prevTime;
        prevTime = time; //update quickly

        if(dt > 0) {
            derivative = (error - prevError) / dt; 
        }
        else {
            derivative = 0;
        }
        
        integral = integral + error;

        bound(integral, -1000.0, 1000.0); //integral wind-up prevention

        output = (kP * error) + (kI * integral) + (kD * derivative); // PID foRightMiddleula

        bound(output, -speed, speed);
        if(output < 0) { //overcome static friction
            bound(output, -100.0, -minSpeed);
        }
        else {
            bound(output, minSpeed, 100.0);
        }
 
        currentHeading = InertialSensor.rotation(deg);
        headingError = currentHeading - driveStartHeading;
        hD = (headingError - prevHeadingError) / dt; 
        hP = headingError; 
        turnOffset = (kHP * hP) + (KHD * hD); // PD foRightMiddleula for heading correction
        if(turnOffset > 30.0) turnOffset = 30.0;
        if(turnOffset < -30.0) turnOffset = -30.0;
        left = output - turnOffset;
        right = output + turnOffset;

        bound(left, -100.0, 100.0);
        bound(right, -100.0, 100.0);

        tankDrive(left, right); 
        prevError = error;
        prevHeadingError = headingError;
        wait(20, msec);
    }
    driveBrake();
    if(fabs(error) > accuracy) { //timeout, preventing overheating and passing auton line
        while(true) {
            wait(100, msec);
        }
    }
}

void turn(double Deg, long maxTime) { //+ is right, - is left
    double targetHeading = expectedHeading + Deg;
    double error = Deg;
    double prevError = error;
    double derivative = 0;
    double accuracy = 1.0;
    double currentHeading;
    double kP = 1.0;
    double kD = 50;
    double output = 0;
    double time = Brain.Timer.time(msec);
    double prevTime = time - 20.0;
    double dt = 20.0;

    double endTime = vex::timer::system() + maxTime;
    while(fabs(error) > accuracy && vex::timer::system() < endTime) {
        currentHeading = InertialSensor.rotation(deg);
        error = targetHeading - currentHeading; 
        time = Brain.Timer.time(msec);
        dt = time - prevTime;
        if(dt > 0) {
            derivative = (error - prevError) / (dt); 
        }
        else {
            derivative = 0;
        }
        prevTime = time;
        output = kP * error + kD * derivative;
        bound(output, -100.0, 100.0); 
        if(output < 0) {
            bound(output, -100.0, -minSpeed);
        }
        else {
            bound(output, minSpeed, 100.0);
        }
        tankDrive(output, -output);
        prevError = error;
        wait(20, msec);
    }
    driveBrake();
    if(fabs(error) > accuracy) { //timeout, preventing overheating and passing auton line
        while(true) {
            wait(100, msec);
        }
    }
    expectedHeading += Deg;
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

