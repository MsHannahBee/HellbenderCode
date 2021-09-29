#include "Commands.h"
#include "Arduino.h"

Commands::Commands() {
  this->reset(); 
}

Commands::~Commands() {
}

void Commands::reset() {
  _idx = 0;
  _nParam = 0;
  _readyForInput = true;
  _buffer[0] = '\0';
  cmd[0] = '\0';
  for (int i=0; i<MAX_PARAM; i++) {
    param[i][0] = '\0';
  }
}

boolean Commands::check() {
  while (_readyForInput && Serial.available() >0) {
    char inChar = Serial.read();
    if (inChar == '\n') {
      _buffer[_idx] = '\0';
      Serial.flush();
      _readyForInput = false;
      _commandReady = true;
      int n = parse();
      return true;
    }
    if (inChar != '\r') {
      _buffer[_idx] = inChar;
      _idx++;
    }
    delay(1);
  }
  return false;
}

void Commands::clear() {
  this->reset();
}

int Commands::nParams() {
  return _nParam;
}

int Commands::parse() {
  int np = 0;
  int i = 0;
  int beg = 0;
  int idxColon = -1;
  int idxComma;
  int strPtr = 0;
  boolean Param = false;
  int lengthCmd = strlen(_buffer);
//  Serial.print("Length CMD: ");
//  Serial.println(lengthCmd);
  Serial.println(_buffer);
  while (i < lengthCmd) {
    if (!Param) {  
      if (_buffer[i] == ':') {
        cmd[strPtr++] = '\0';
        Param = true;
        strPtr = 0;
      } else {
        cmd[strPtr] = _buffer[i];
        strPtr++;
      }
    } else {
      if (_buffer[i] == ',') {
        param[np][strPtr] = '\0';
        strPtr = 0;
        np++;
      } else {
        param[np][strPtr] = _buffer[i];
        strPtr++;
      }
    }
    i++;
  }
  if(Param){
    param[np][strPtr] = "\0";
    np++;
  } else {
    cmd[strPtr] = '\0';
  }
  strupr(cmd);
  _nParam = np;
  return np;
}

int Commands::iParam(int i) {
  if (i < _nParam && i>-1) {
    return atoi(param[i]);
  } else {
    return -999;
  }
}

float Commands::fParam(int i) {
  if (i < _nParam && i>-1) {
    return atof(param[i]);
  } else {
    return -999;
  }
}
