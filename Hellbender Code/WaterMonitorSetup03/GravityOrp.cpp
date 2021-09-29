/*********************************************************************
* GravityOrp.cpp
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Monitoring water quality parameters Oxidation-Reduction Potential
*
* Product Links：http://www.dfrobot.com.cn/goods-840.html
*
* Sensor driver pin：A3 (pin(A3))
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-14
**********************************************************************/

#include "GravityOrp.h"


extern uint16_t readMedianValue(int* dataArray, uint16_t arrayLength);

GravityOrp::GravityOrp()
{
  offset = 0.0;
}

GravityOrp::~GravityOrp()
{
}

//********************************************************************************************
// Function name: setup()
// Function description: Initialize the sensor
//********************************************************************************************
void GravityOrp::setup()
{
	pinMode(ORPPIN, INPUT);
}

//********************************************************************************************
// Function name: update()
// Function description: update sensor value
//********************************************************************************************
void GravityOrp::update()
{
	double averageValue = 0;
	for (uint8_t i = 0; i < ARRAYLENGTH; i++)
	{
		orpArray[i] = analogRead(ORPPIN);    //read an analog value every 20ms
		delay(10);
	}
	this->orpRawValue = readMedianValue(orpArray, ARRAYLENGTH);
	this->orpValue = ((30 * VREFMV) - (75 * this->orpRawValue*VREFMV / 1024)) / 75 - this->offset;
}


//********************************************************************************************
// Function name: getValue()
// Function Description: Return sensor data
//********************************************************************************************
double GravityOrp::getValue()
{
  return this->orpValue;
}

//********************************************************************************************
// Function name: getRawValue()
// Function Description: Return raw adc data (median value)
//********************************************************************************************
double GravityOrp::getRawValue()
{
 return this->orpRawValue;
}

void GravityOrp::setOffset(float off)
{
  this->offset = off;
}
