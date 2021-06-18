#pragma once

#include <Arduino.h>

class SerialHelper {
    int tx, rx;
    int baudrate;

  public:
    SerialHelper(int tx, int rx, int baudrate);
    void sendCommand(String cmd);
    String readCommand();
    ~SerialHelper();
};
