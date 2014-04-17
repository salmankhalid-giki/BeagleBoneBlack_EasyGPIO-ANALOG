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



#include<accessor.h>

bool Accessor::isAvailable_GPIO[] = {0};
bool Accessor::isAvailable_ANALOG[] = {0};
bool Accessor::isLoaded_CAPE = 0;

Accessor::Accessor()
{

}


void Accessor::gpio_makeAvailable(unsigned int pin_Num)
{
  isAvailable_GPIO[pin_Num] = 0;
}


void Accessor::gpio_makeUnAvailable(unsigned int pin_Num)
{
  isAvailable_GPIO[pin_Num] = 1;
}



bool Accessor::gpio_isAvailable(unsigned int pin_Num)
{

  if(isAvailable_GPIO[pin_Num])
    return 0;

  else
    return 1;
}



void Accessor::analog_makeAvailable(unsigned int pin_Num)
{
  isAvailable_ANALOG[pin_Num] = 0;
}

void Accessor::analog_makeUnAvailable(unsigned int pin_Num)
{
  isAvailable_ANALOG[pin_Num] = 1;
}

bool Accessor::analog_isAvailable(unsigned int pin_Num)
{
  if(isAvailable_ANALOG[pin_Num])
    return 0;
  else
    return 1;
}
