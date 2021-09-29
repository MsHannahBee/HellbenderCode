#pragma once
#include "ISensor.h"
#include "Arduino.h"
class GravityEc : public ISensor
{
public:
	GravityEc();
	~GravityEc();

public:
	void setup();
	void update();
	double getValue();
  double getRawValue();
	void setKValue(float value);

	int pin;
	double ecValue;
  double ecRawValue;
	float kValue;

};
