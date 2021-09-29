#include <EEPROM.h>
#include "Calibrations.h"
#include "Arduino.h"

Calibrations::Calibrations() {
 reset();
}

Calibrations::~Calibrations() {  
}

void Calibrations::reset() {
 cal = {
    1127.6f,
    -0.1f,
    14.0f,
    0.0f,
    1.0f
  };
}

void Calibrations::read() {
  EEPROM.get(_EEStart, cal);
}

void Calibrations::write() {
  EEPROM.put(_EEStart, cal);
}

void Calibrations::display() {
  Serial.println("Calibrations:");
  Serial.println(cal.satDoVolt);
  Serial.println(cal.pHslope);
  Serial.println(cal.pHoffset);
  Serial.println(cal.orpOffset);
  Serial.println(cal.kValue);  
  Serial.println(" ");  
  
}
