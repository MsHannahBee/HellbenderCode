#pragma once

//The maximum length of the sensor filter array
#define ARRAYLENGTH 10

//SD card update data time, 60,000 is 1 minute
#define SDUPDATEDATATIME 60000

//EC sensor is selected by default, comment this line to use TDS sensor
#define SELECTEC 

//Sensor pin settings
#define DOPIN  A0
#define ECPIN  A1
#define PHPIN  A2
#define ORPPIN A3
#define TEMPPIN 5


//Set sensor offset (calibration data)
#define PHOFFSET 0.12
#define ECKVALUE 0.6

//Set voltage reference for all sensors in config.h
#define VREFMV 5000.0
#define VREFV 5.00

//The maximum number of sensors
#define SENSORCOUNT 5

//The sensor corresponds to the array number, ph=0, temperature=1..., the maximum number is SENSORCOUNT-1
enum SensorNumber
{
	phSensor = 0,
	temperatureSensor,
	doSensor,
	ecSensor,
	orpSensor
};
