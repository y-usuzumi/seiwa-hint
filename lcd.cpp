#include "lcd.h"

LCD::LCD(int rs, int e, int d4, int d5, int d6, int d7) {
  lcd = new LiquidCrystal(rs, e, d4, d5, d6, d7);
}

void LCD::setup() {
  lcd->begin(16, 2);
}

void LCD::clearAll() {
  lcd->clear();
}

void LCD::clearHeader() {
  lcd->setCursor(0, 0);
  lcd->print(CLEAR_LINE);
  lcd->setCursor(0, 0);
}

void LCD::clearContent() {
  lcd->setCursor(0, 1);
  lcd->print(CLEAR_LINE);
  lcd->setCursor(0, 1);
}

void LCD::displayHeader(String data) {
  clearHeader();
  lcd->print(data);
}

void LCD::displayContent(String data) {
  clearContent();
  lcd->print(data);
}

LCD::~LCD() {
  if (lcd != NULL) {
    delete lcd;
  }
}
