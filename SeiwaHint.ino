#include "defs.h"
#include "lcd.h";

#ifdef ENABLE_JOYSTICK
#include "joystick.h"
#endif

const int GLOBAL_SWITCH_PIN = 9;
const int GLOBAL_5V_OUTPUT_PIN = 10;

const int LCD_RS = 2;
const int LCD_E = 3;
const int LCD_D4 = 4;
const int LCD_D5 = 5;
const int LCD_D6 = 6;
const int LCD_D7 = 7;

#ifdef ENABLE_JOYSTICK
const int JOYSTICK_SW = 13;
const int JOYSTICK_X_PIN = A1;
const int JOYSTICK_Y_PIN = A2;
const int JOYSTICK_REFRESH_INTERVAL = 20000;
#endif

LCD *lcd = new LCD(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#ifdef ENABLE_JOYSTICK
Joystick *joystick = new Joystick(JOYSTICK_SW, JOYSTICK_X_PIN, JOYSTICK_Y_PIN, Timer.getAvailable(), JOYSTICK_REFRESH_INTERVAL);
#endif

bool reportGlobalSwitch(void*);

static bool global_switch = false;

void writeToSerial(char* s) {
  SerialUSB.print(s);
  SerialUSB.flush();
}

void flip_global_switch() {
  global_switch = !global_switch;
  digitalWrite(GLOBAL_5V_OUTPUT_PIN, global_switch ? HIGH : LOW);
}

void setup() {
  pinMode(GLOBAL_SWITCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GLOBAL_SWITCH_PIN), flip_global_switch, LOW);
  pinMode(GLOBAL_5V_OUTPUT_PIN, OUTPUT);
  digitalWrite(GLOBAL_5V_OUTPUT_PIN, HIGH);

  SerialUSB.begin(119200);
  while (!SerialUSB) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial3.begin(119200);

  lcd->setup();

#ifdef ENABLE_JOYSTICK
  joystick->setup();
  joystick->attachIntervalHandler(reportJoystick);
#endif
}

bool reportGlobalSwitch(void *argument) {
  char gs[30];
  sprintf(gs, "A:GS:%d\n", digitalRead(GLOBAL_SWITCH_PIN));
  writeToSerial(gs);
  return true;
}

#ifdef ENABLE_JOYSTICK

void reportJoystick() {
  int sw = digitalRead(JOYSTICK_SW_PIN);
  if (sw != joystick_sw) {
    joystick_sw = sw;
    char swmsg[30];
    // 1: released, 0: pressed. Reverse it.
    sprintf(swmsg, "A:J:SW:%d\n", !sw);
    writeToSerial(swmsg);
  }
  int x = analogRead(JOYSTICK_Y_PIN);
  int y = analogRead(JOYSTICK_X_PIN);
  char xymsg[30];
  sprintf(xymsg, "A:J:XY:%d:%d\n", x - joystick_origin_x, y - joystick_origin_y);
  writeToSerial(xymsg);
}
#endif

void runCommand(String cmd) {
  if (cmd == "PING") {
    String xyz("HELLO");
    writeToSerial("PONG\n");
  } else if (cmd == "CLEAR") {
    lcd->clearAll();
  }
}

void loop() {
  if (SerialUSB.available()) {
    String data = SerialUSB.readStringUntil('\n');
    if (data.startsWith("C:")) {
      String content = data.substring(2);
      runCommand(content);
    } else if (data.startsWith("D0:")) {
      String header = data.substring(3);
      lcd->displayHeader(header);
    } else if (data.startsWith("D1:")) {
      String content = data.substring(3);
      lcd->displayContent(content);
    }
  }
  if (Serial3.available()) {
    String data = Serial3.readStringUntil('\n');
    lcd->displayHeader("S3:" + data);
    Serial3.println(data);
  }
}
