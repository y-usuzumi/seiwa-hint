#pragma once

#include <DueTimer.h>

static int joystick_sw = 1;
static int joystick_origin_x = 0;
static int joystick_origin_y = 0;


class Joystick {
    int sw, xpin, ypin;
    int refreshInterval;
    int sw_status = 1;
    int joystick_origin_x = 0;
    int joystick_origin_y = 0;
    DueTimer timer;
    void reportJoystick();
    void calibrateJoystick();

  public:
    Joystick(int sw, int xpin, int ypin, DueTimer timer, int refreshInterval);
    void setup();
    void attachIntervalHandler(void (*h)());
    void calibrate();
    ~Joystick();
};
