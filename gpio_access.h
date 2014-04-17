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

#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0
#define GPIO_FILESYS_DIR "/sys/class/gpio"
#define MAX_BUF 64

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <accessor.h>

using namespace std;

class Digital_I_O: protected Accessor
{
private:
  int fd,len,fd_digi;
  unsigned int gpio_num;
  bool is_attached,io_mode;
public:
  Digital_I_O();
  ~Digital_I_O();
  bool attach(unsigned int pin_num);  
  bool detach();
  bool digitalWrite(bool value);
  int digitalRead();
  bool pinMode(bool mode);
  bool isAvailable(unsigned int pin_num);
};
