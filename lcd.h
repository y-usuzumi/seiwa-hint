#pragma once

#include <LiquidCrystal.h>

const String CLEAR_LINE = "                ";

class LCD {
    LiquidCrystal* lcd;

  public:
    LCD(int rs, int e, int d4, int d5, int d6, int d7);
    void setup();
    void clearAll();
    void clearHeader();
    void clearContent();
    void displayHeader(String data);
    void displayContent(String data);
    ~LCD();
};
