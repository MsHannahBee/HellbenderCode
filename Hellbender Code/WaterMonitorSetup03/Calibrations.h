#ifndef Calibrations_h
#define Calibrations_h


struct CalibStruct {
  float satDoVolt;
  float pHslope;
  float pHoffset;
  float orpOffset;
  float kValue;  
};

class Calibrations 
{
public:
  Calibrations();
  ~Calibrations();
  void reset();
  void read();
  void write();
  void display();
  CalibStruct cal;
  
private:
  int _EEStart;
};

#endif
