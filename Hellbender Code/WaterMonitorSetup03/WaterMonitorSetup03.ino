/* General Purpose Serial Communication Routine
 * 8/15/20 Creating class for Commands
 * 9/3/20 create commands for setting RTC
 */

#include "Commands.h"
#include "Calibrations.h"
#include "GravityPh.h"
#include "GravityEc.h"
#include "GravityDo.h"
#include "GravityOrp.h"
#include "GravityTemperature.h"
#include "GravityRtc.h"

Commands Cmd;
Calibrations Cal;

GravityPh pH;
GravityEc Ec;
GravityDo Do;
GravityOrp Orp;
GravityTemperature Temp;
GravityRtc rtc;


void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  Serial.println("Water Monitor Calibration Tool V0.3");
  Cal.read();
  setupSensors(Cal.cal);
  Serial.println(".... Sensor Setup Complete");

}

void loop() {
//  Serial.print(".");
  
  if (Cmd.check()) {
//    Serial.println(".");
//    Serial.println(Cmd.cmd);
// Display Calibration Data
    if (strcmp(Cmd.cmd,"DISP")==0) {
      displayData(Cal.cal);
// Read Calibration Data from EEPROM
    } else if (strcmp(Cmd.cmd,"READ")==0) {
      Serial.println("Read Calibration Data from EEPROM");
      Cal.read();
// Write Calibration Data to EEPROM
    } else if (strcmp(Cmd.cmd,"WRITE")==0) {
      Serial.println("Write Calibration Data to EEPROM");
      Cal.write();
// Reset Calibration data to defaults in Calibrations.cpp
    } else if (strcmp(Cmd.cmd,"RESET")==0) {
      Serial.println("Reset Calibration Data");
      Cal.write();
// Set SaturationDoVoltage (it is in mV)   SATDO:1284.5
    } else if (strcmp(Cmd.cmd,"SATDO")==0) {
      float satdo = Cmd.fParam(0);
      Serial.print("Sat DO Voltage: ");
      Serial.println(satdo);
      Cal.cal.satDoVolt = satdo;
// Set pH Offset      PHOFF:13.0
    } else if (strcmp(Cmd.cmd,"PHOFF")==0) {
      float offset = Cmd.fParam(0);
      Serial.print("pH Offset: ");
      Serial.println(offset);
      Cal.cal.pHoffset = offset;
      pH.setOffset(offset);
// Set pH Slope
    } else if (strcmp(Cmd.cmd,"PHSLOPE")==0) {
      float slope = Cmd.fParam(0);
      Serial.print("pH Slope: ");
      Serial.println(slope);
      Cal.cal.pHslope = slope;
      pH.setSlope(slope);

// Set Oxidation/Reduction Potential Offset
    } else if (strcmp(Cmd.cmd,"ORPOFF")==0) {
      float offset = Cmd.fParam(0);
      Serial.print("ORP Offset: ");
      Serial.println(offset);
      Cal.cal.orpOffset = offset;
// Set Electrical Conductivity kValue
    } else if (strcmp(Cmd.cmd,"KVALUE")==0) {
      float k = Cmd.fParam(0);
      Serial.print("kValue: ");
      Serial.println(k);
      Cal.cal.kValue = k;
        Ec.setKValue(k);
// Read pH Probe
    } else if (strcmp(Cmd.cmd,"PH")==0) {
      pH.update();
      Serial.print("pH: ");
      Serial.print(pH.getValue());
      Serial.print("   ");
      Serial.println(pH.getRawValue());
// Read EC Probe
    } else if (strcmp(Cmd.cmd,"EC")==0) {
      Ec.update();
      Serial.print("Ec: ");
      Serial.print(Ec.getValue());
      Serial.print("   ");
      Serial.println(Ec.getRawValue());
// Read DO probe
    } else if (strcmp(Cmd.cmd,"DO")==0) {
      Do.update();
      Serial.print("Do: ");
      Serial.print(Do.getValue());
      Serial.print("   ");
      Serial.println(Do.getRawValue());

// Read ORP Probe
     } else if (strcmp(Cmd.cmd,"ORP")==0) {
      Orp.update();
      Serial.print("Orp: ");
      Serial.print(Orp.getValue());
      Serial.print("   ");
      Serial.println(Orp.getRawValue());
// Read Temp probe (3 times)
     } else if (strcmp(Cmd.cmd,"TEMP")==0) {
      Temp.update();
      delay(850);
      for (int i=0; i<3; i++) {
         Temp.update();
         Serial.print("Temp: ");
         Serial.println(Temp.getValue());
         delay(1000);
      }

// DATE - Print RTC date
    } else if (strcmp(Cmd.cmd,"DATE")==0) {
      rtc.update();
      delay(10);
      Serial.print("Date/Time: ");
      Serial.print(rtc.month);
      Serial.print("/");
      Serial.print(rtc.day);
      Serial.print("/");
      Serial.print(rtc.year);
      Serial.print("   ");
      Serial.print(rtc.hour);
      Serial.print(":");
      Serial.print(rtc.minute);
      Serial.print(":");
      Serial.println(rtc.second);
      Serial.println(" ");
    } else if (strcmp(Cmd.cmd,"DAY")==0) {
      rtc.year = Cmd.iParam(0);         
      rtc.month = Cmd.iParam(1);         
      rtc.day = Cmd.iParam(2);         
      rtc.week = Cmd.iParam(3); 
      Serial.print("Date: ");
      Serial.print(rtc.month);
      Serial.print("/");
      Serial.print(rtc.day);
      Serial.print("/");
      Serial.print(rtc.year);
      Serial.print("   Day of Week:");
      Serial.println(rtc.week);
    } else if (strcmp(Cmd.cmd,"TIME")==0) {
      rtc.hour = Cmd.iParam(0);         
      rtc.minute = Cmd.iParam(1);         
      rtc.second = Cmd.iParam(2);         
      Serial.print("Time: ");
      Serial.print(rtc.hour);
      Serial.print(":");
      Serial.print(rtc.minute);
      Serial.print(":");
      Serial.println(rtc.second);  
    } else if (strcmp(Cmd.cmd,"SETRTC")==0) { 
      rtc.adjustRtc(rtc.year, rtc.month, rtc.day, rtc.week, rtc.hour, rtc.minute, rtc.second);
      delay(10);
      rtc.update();
      delay(10);
      Serial.print("Date/Time: ");
      Serial.print(rtc.month);
      Serial.print("/");
      Serial.print(rtc.day);
      Serial.print("/");
      Serial.print(rtc.year);
      Serial.print("   ");
      Serial.print(rtc.hour);
      Serial.print(":");
      Serial.print(rtc.minute);
      Serial.print(":");
      Serial.println(rtc.second);
      Serial.println(" ");
    } else {
      Serial.println("Command not recognized");
    }
    
    Cmd.clear();
    Serial.println(">");
  }
  delay(1000);
}

void displayData(CalibStruct c) {
      Serial.println(" ");      
      Serial.println(F("Calibration Data:"));
      Serial.print(F("SatDoVolt: "));
      Serial.println(c.satDoVolt);
      Serial.print(F("pH Slope:  "));
      Serial.println(c.pHslope);
      Serial.print(F("pH Offset: "));
      Serial.println(c.pHoffset);
      Serial.print(F("Ox/Red Offset: "));
      Serial.println(c.orpOffset);
      Serial.print(F("kValue:  "));
      Serial.println(c.kValue);
      Serial.println(" ");
}

void setupSensors(CalibStruct c) {
  pH.setup();
  pH.setOffset(c.pHoffset);
  pH.setSlope(c.pHslope);
  
  Ec.setup();
  Ec.setKValue(c.kValue);

  Do.setup();
  Do.setSatDoVolt(c.satDoVolt);

  Orp.setup();
  Orp.setOffset(c.orpOffset);

  Temp.setup();
  Temp.update();

  rtc.setup();
  rtc.update();
  
}
