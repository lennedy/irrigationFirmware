#include "Print.h"

void Exibir::config(){
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor  
}

void Exibir::digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void Exibir::printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
