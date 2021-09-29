#pragma once

#include "ISensor.h"
#include "Arduino.h"
#include "Config.h"

class GravityDo: public ISensor
{
public:
	GravityDo();
	~GravityDo();

public:
	void setup();
	void update();
  double getValue();
  double getRawValue();
  void setSatDoVolt(float satDoVolt);
  float getTemperature() const;
  void setTemperature(float temperature);

private:
    float  _temperature;
    double _doValue;
    double _doRawValue;

    float  _saturationDoVoltage;
    float  _saturationDoTemperature;
    float  _averageVoltage;
};  
