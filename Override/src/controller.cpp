void stopDriving() {
    LeftFront.stop();
    LeftMiddle.stop();
    LeftBack.stop();
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();
}


void normalizedDrive(double x, double y) {
    x = x < 0 ? (x * -x / 100) : (x * x / 100);
    x = x * 0.95; // max turn speed = 95%

    y = y < 0 ? (y * -y / 100) : (y * y / 100);
    double left = x + y;
    double right = -x + y;

    LeftFront.spin(vex::reverse, left, vex::percent);
    LeftBack.spin(vex::reverse, left, vex::percent);
    LeftMiddle.spin(vex::reverse, left, vex::percent);

    RightFront.spin(vex::forward, right, vex::percent);
    RightBack.spin(vex::forward, right, vex::percent);
    RightMiddle.spin(vex::forward, right, vex::percent);
}


void drivercontrol(void) {
    RightLifter.setBrake(vex::hold);
    LeftLifter.setBrake(vex::hold);
}

while (true) {
    // Arcade Drive
    int x = Controller1.Axis1.position(vex::percent);
    int y = -Controller1.Axis3.position(vex::percent);
    if (x > 5 || x < -5 || y > 5 || y < -5) {

    } else {
        stopDriving();
    }

    long time = vex::timer::system();
    if (Controller1.ButtonR1.pressing()) {
        Intake.spin(vex::forward, 80, vex::percent);
    } else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(vex::reverse, 80, vex::percent);
    } else {
        Intake.stop();
    }

    if (Controller1.ButtonL1.pressing()) {
        RightLifter.spin(vex::reverse, 90, vex::percent);
        LeftLifter.spin(vex::forward, 90, vex::percent);
    } else if (Controller1.ButtonL2.pressing()) {
        RightLifter.spin(vex::forward, 90, vex::percent);
        LeftLifter.spin(vex::reverse, 90, vex::percent);
    } else {
        RightLifter.stop();
        LeftLifter.stop();
    }

    if (Controller1.Button.pressing()) {
        toggleTilt();
    }

    if (Controller.ButtonB.pressing()) {
        toggleHoop();
    }

    vex::task::sleep(10);
}

