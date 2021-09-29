/* Water Quality Data Logger
 *  V0.1 - Looking to only log raw data where an option.
 *         Ignore any calibration data
 *  V0.2 - I think it is working
 *  V0.3 - Fixed analogRead and filename issues - FAT32 - filename length issue
 */

#include <SD.h>
#include "GravityTemperature.h"
#include "GravityRtc.h"

GravityTemperature Temp;
GravityRtc rtc;
const int SDSelect = 4;

long lastTime;
const long deltaTime = 10000;  // Logging time in milliseconds

String dataString = "";
String dataStringConsole = ""; // Data string with added labels for console output


const int ARRAYLENGTH=10;
File dataFile;

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  Serial.println("Water Monitor Logging Tool V0.3");


  setupSensors();
  Serial.println(".... Sensor Setup Complete");

  Serial.print("Initializing SD card...");
  pinMode(10,OUTPUT);
  if (!SD.begin(SDSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");

  dataFile = SD.open("sensor.csv", FILE_WRITE);
  if (dataFile && dataFile.position() == 0) {
      dataFile.println(F("date,DO,ec,pH,temp(C)"));
      dataFile.close();
  }

  lastTime = millis();
}

void loop() {
  if (millis() - lastTime > deltaTime) {
    lastTime = millis();

    //Update time from clock module
    rtc.update();

    //add time to dataString
    // Year Month Day Hours Minute Seconds
    dataString = "";
    dataString += String(rtc.year,10);
    dataString += "/";
    dataString += String(rtc.month, 10);
    dataString += "/";
    dataString += String(rtc.day, 10);
    dataString += " ";
    dataString += String(rtc.hour, 10);
    dataString += ":";
    dataString += String(rtc.minute, 10);
    dataString += ":";
    dataString += String(rtc.second, 10);
    dataString += ",";

    // write time to SD card, write in two operations to keep write size small
    dataFile = SD.open("sensor.csv", FILE_WRITE);
    if (dataFile) {
           dataFile.print(dataString);
           dataFile.close();
    }
    Serial.print(dataString);

    //Empty dataString and add sensor readings
    dataString = "";
    dataStringConsole = "";
    for (int i=0; i<3; i++) {
       int data = readSensor(i);
       dataString += String(data, 10);
       dataString += String(",");
       
       if(i == 0){
          dataStringConsole += " DO: ";
          dataStringConsole += String(data, 10);
          dataStringConsole += String(",");
        }
       else if(i == 1){
          dataStringConsole += " EC: ";
          dataStringConsole += String(data, 10);
          dataStringConsole += String(",");
        }
        
       else if(i == 2){
          dataStringConsole += " PH: ";
          dataStringConsole += String(data, 10);
          dataStringConsole += String(",");
        
        }
        
       //else if(i == 3){
          //dataStringConsole += " Orp: ";
          //dataStringConsole += String(data, 10);
          //dataStringConsole += String(",");
        
        //}
  

    }
    //Get temp
    Temp.update();
    delay(850);
    Temp.update();
    float temp = Temp.getValue();
    dataStringConsole += " Temp: ";
    dataStringConsole += String(temp,10);
    dataString += String(temp,10);
    
   
    //Write sensor readings to SD card
    dataFile = SD.open("sensor.csv", FILE_WRITE);
    if (dataFile)
     {
        dataFile.println(dataString);
        dataFile.close();
        Serial.println(dataStringConsole);
     }
        
  }
  
}



void setupSensors() {
  Temp.setup();
  Temp.update();

  rtc.setup();
  rtc.update();  
}

extern uint16_t readMedianValue(int* dataArray, uint16_t arrayLength);

int readSensor(int pin) {
  int analogBuffer[ARRAYLENGTH];

  for (uint8_t i = 0; i < ARRAYLENGTH; i++)
  {
    analogBuffer[i] = analogRead(pin);
    delay(10);
  }

  int RawValue = readMedianValue(analogBuffer, ARRAYLENGTH); // get median value of several readings for stability
 
  return RawValue;
}
