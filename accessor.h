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



#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>


using namespace std;

class Accessor
{
private:
  static bool isAvailable_GPIO[200];
  static bool isAvailable_ANALOG[6];


public:
  static bool isLoaded_CAPE;
  Accessor();
  void gpio_makeAvailable(unsigned int pin_Num);
  void gpio_makeUnAvailable(unsigned int pin_Num);
  bool gpio_isAvailable(unsigned int pin_Num);

  void analog_makeAvailable(unsigned int pin_Num);
  void analog_makeUnAvailable(unsigned int pin_Num);
  bool analog_isAvailable(unsigned int pin_Num);

};
