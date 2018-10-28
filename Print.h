#ifndef EXIBIR_H
#define EXIBIR_H

#include <Arduino.h>
#include <TimeLib.h>

class Exibir{
  public:
  void config();

  void digitalClockDisplay();
  void printDigits(int digits);
};

#endif
