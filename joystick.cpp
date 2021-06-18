#include "joystick.h"

Joystick::Joystick(int sw, int xpin, int ypin, DueTimer timer, int refreshInterval) :
  sw(sw), xpin(xpin), ypin(ypin), timer(timer), refreshInterval(refreshInterval) {
}

void Joystick::setup() {
  pinMode(sw, INPUT);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  digitalWrite(sw, HIGH);

  calibrateJoystick();
}

void Joystick::attachIntervalHandler(void (*h)()) {
  timer.attachInterrupt(h).setPeriod(refreshInterval).start();
}

void Joystick::calibrate() {
  joystick_origin_x = analogRead(ypin);
  joystick_origin_y = analogRead(xpin);
}

Joystick::~Joystick() {}
