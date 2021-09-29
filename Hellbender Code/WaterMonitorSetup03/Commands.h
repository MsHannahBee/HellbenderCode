/* Commands
 *  Read input from serial line and parse into commands and parameters
 *  M. Lucas 8/17/20
 *  
 *  Usage:
 *     Commands Cmd  - constructor
 *     Cmd.check - Check for command, return true or false
 *     Cmd.cmd   - Character string with command
 *     Cmd.nParams() - Return integer, number of parameters
 *     Cmd.iParam(int) - Return integer value of parameter(i) (i=0,n-1);
 *     Cmd.fParam(int) - Return float value of parameter(i) (i=0,n-1);
 *     Cmd.clear() - Clear variables and prepare for next command
 */
#ifndef Commands_h
#define Commands_h
#include "Arduino.h"

const int MAX_PARAM=6;
const int MAX_LEN=30;
const int MAX_CMDLEN=10;

class Commands
{

public:
  Commands();
  ~Commands();
  boolean check();
  int nParams();
  void clear();
  char cmd[MAX_CMDLEN];
  char param[MAX_PARAM][MAX_CMDLEN];
  int iParam(int i);
  float fParam(int i);

private:
  void reset();
  int _idx;
  char _buffer[MAX_LEN];
  int _nParam;
  boolean _readyForInput;
  boolean _commandReady;
  int parse();
  void copySubstr(char *dest, char *source, int first, int last);
};

#endif
