#include "serial_helper.h"

SerialHelper::SerialHelper(int tx, int rx, int baudrate)
  : tx(tx), rx(rx), baudrate(baudrate) {}

void SerialHelper::sendCommand(String cmd) {

}

String SerialHelper::readCommand() {

}

SerialHelper::~SerialHelper() {}
