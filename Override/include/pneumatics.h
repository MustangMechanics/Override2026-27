bool isHoopDown() { return isActOpen[HOOP]; }
void hoopDown() { openActuator(HOOP); }
void hoopUp() { closeActuator(HOOP); }
bool toggleHoop() { return toggleActuator(HOOP); }

bool isTiltOut() { return isActOpen[TILT]; }
void tiltOut() { openActuator(TILT); }
void tiltIn() { closeActuator(TILT); }
bool toggleTilt() { return toggleActuator(TILT); }