/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    Any additions, corrections and criticism are welcome

    This piece of code provides an arduino like interface for the BBB (GPIO and Analog)
    so the users familiar with arduino can have full advantage of 1 Ghz Arm Processor
    and easy access to GPIO and Analog inputs/outputs.Serial and I2C will be added later 

    Written by Muhammad Salman Khalid

*/


#define LOAD_CAPE "echo BB-ADC > /sys/devices/bone_capemgr.8/slots"
#define ANALOG_SYSPATH "/sys/devices/ocp.2/helper.14/AIN"
//#define ANALOG_SYSPATH "/sys/devices/ocp.2/44e0d000.tscadc/tiadc/iio:\\device0/in_voltage"


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <cstdlib>
#include <stdio.h>
#include <accessor.h>

using namespace std;

class Analog_In: protected Accessor
{

private:
  int len,fd_analog;
  unsigned char analog_pinNum;
  bool is_attached;
  char analog_Path[150];
public:
  Analog_In();
//~Analog_In();
  bool attach(unsigned char pin_num);
  bool detach();
  int analogRead();

};

