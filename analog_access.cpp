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

#include <analog_access.h>


Analog_In::Analog_In()
{
  if(isLoaded_CAPE != 1)
    {
      cout<<"Attaching\n";
      system("echo BB-ADC > /sys/devices/bone_capemgr.8/slots");
      cout<<"Attaching Finished\n";
      is_attached = 0;
      isLoaded_CAPE = 1;
    }
  else
    {
      cout<<"Analog Cape already loaded\n";
    }
}

bool Analog_In::attach(unsigned char pin_num)
{
  char analog_input[4];
  char dummy_input[4];

  if(!is_attached)
    {

      if(pin_num == '0' || pin_num == '1' || pin_num == '2' || pin_num == '3' || pin_num == '4' || pin_num == '5')
        {
          len = snprintf(analog_Path,sizeof(analog_Path),ANALOG_SYSPATH"%c",pin_num);
          is_attached = 1;
          analog_pinNum = pin_num;
          analog_makeUnAvailable(pin_num);
          return 1;
        }
      else
        {
          cout<<"Wrong Pin Number\n";
          return 0;
        }

    }
  else
    {
      cout<<"Pin already Attached\n";
      return 0;
    }

}


bool Analog_In::detach()
{
  if(is_attached)
    {
      is_attached = 0;
      analog_makeAvailable(analog_pinNum);
      return 1;
    }
  else
    cout<<"No pin Attached\n";
}


int Analog_In::analogRead()
{
  char analog_input[4];
  char dummy_input[4];
  if(is_attached)
    {
      fd_analog = open(analog_Path,O_RDONLY);

      if(fd_analog < 0)
        {
          perror("Can not open file\n");
          return -1;
        }

      read(fd_analog,&dummy_input,sizeof(dummy_input));
      close(fd_analog);
      fd_analog = open(analog_Path,O_RDONLY);

      if(fd_analog < 0)
        {
          perror("Can not open file\n");
          return -1;
        }

      read(fd_analog,&analog_input,sizeof(analog_input));
      close(fd_analog);
      return atoi(analog_input);
    }

  else
    {
      cout<<"No Pin Attached\n";
      return -1;
    }

}

