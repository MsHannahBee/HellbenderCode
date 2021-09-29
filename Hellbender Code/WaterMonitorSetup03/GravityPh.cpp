/*********************************************************************
* GravityPh.cpp
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Monitoring water quality parameters ph
*
* Product Links：http://www.dfrobot.com.cn/goods-812.html
*
* Sensor driver pin：A2 (pin(A2))
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-07
**********************************************************************/

#include "GravityPh.h"
#include "Config.h"

extern uint16_t readMedianValue(int* dataArray, uint16_t arrayLength);

GravityPh::GravityPh()
{
}

//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the ph sensor
//********************************************************************************************
void GravityPh::setup()
{
	pinMode(PHPIN, INPUT);
}


//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void GravityPh::update()
{

	double averageVoltage = 0;

	for (uint8_t i = 0; i < ARRAYLENGTH; i++)
	{
		pHArray[i] = analogRead(PHPIN);
		delay(10);
	}
	pHRawValue = readMedianValue(pHArray, ARRAYLENGTH);
	averageVoltage = pHRawValue*VREFV / 1024.0;
	pHValue = this->slope*averageVoltage + this->offset;

}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double GravityPh::getValue()
{
	return this->pHValue;
}
double GravityPh::getRawValue()
{
  return this->pHRawValue;
}

void GravityPh::setOffset(float offset)
{
  this->offset = offset;
}
void GravityPh::setSlope(float slope)
{
 this->slope = slope;
}
