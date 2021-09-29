#include "GravityEc.h"
#include "Config.h"

extern uint16_t readMedianValue(int* dataArray, uint16_t arrayLength);

GravityEc::GravityEc()
{
}


GravityEc::~GravityEc()
{
  this->kValue = 1.0;
}

void GravityEc::setup()
{
	pinMode(ECPIN, INPUT);
}


void GravityEc::update()
{
	int ecValueBuffer[ARRAYLENGTH];
	float averageVoltage;
	for (uint8_t i = 0; i < ARRAYLENGTH; i++)
	{
		ecValueBuffer[i] = analogRead(ECPIN);
		delay(10);
	}
  this->ecRawValue = readMedianValue(ecValueBuffer, ARRAYLENGTH);
	averageVoltage = (this->ecRawValue/1024.0)*VREFMV;
	this->ecValue = 1000 * averageVoltage / 820.0 / 196.0 /this->kValue;
}

double GravityEc::getValue()
{
	return this->ecValue;
}
double GravityEc::getRawValue()
{
  return this->ecRawValue;
}
void GravityEc::setKValue(float value)
{
	this->kValue = value;
}
