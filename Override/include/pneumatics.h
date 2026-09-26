#ifndef PNEUMATICS_H
#define PNEUMATICS_H

void initPneumatics();

bool isHoopDown();
void hoopDown();
void hoopUp();
bool toggleHoop();

bool isTiltOut();
void tiltOut();
void tiltIn();
bool toggleTilt();

bool isCatcherOut();
void catcherOut();
void catcherIn();
bool toggleCatcher();

#endif // PNEUMATICS_H