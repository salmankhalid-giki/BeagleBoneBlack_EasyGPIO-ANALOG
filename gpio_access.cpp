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

#include <gpio_access.h>


Digital_I_O::Digital_I_O()
{
  is_attached = 0;
}

Digital_I_O::~Digital_I_O()
{

  if(fd_digi)
    close(fd_digi);
  if(is_attached)
    {
      char buf[MAX_BUF];
      fd = open(GPIO_FILESYS_DIR "/unexport",O_WRONLY);
      if(fd<0)
        {

          perror("Error unexport -- method class destructor\n");

        }
      len = snprintf(buf,sizeof(buf),"%d",gpio_num);
      write(fd,buf,len);
      close(fd);
      is_attached = 0;
    }
}

bool Digital_I_O::attach(unsigned int pin_num)
{
  char buf[MAX_BUF];


  if(!is_attached && gpio_isAvailable(pin_num))
    {
      gpio_num = pin_num;
      cout<<"Pin number is:"<<pin_num<<"\n";
      fd = open(GPIO_FILESYS_DIR "/export",O_WRONLY);
      if(fd<0)
        {

          perror("Error export -- method attach() \n");
          return 0;
        }
      len = snprintf(buf,sizeof(buf),"%d",pin_num);
      write(fd,buf,len);
      close(fd);
      gpio_makeUnAvailable(gpio_num);
      is_attached = 1;
      fd = NULL;
      fd_digi = NULL;
      len = NULL;
      return 1;
    }
  else
    {
      perror("A pin is already attached\n");
      return 0;
    }

}

bool Digital_I_O::detach()
{
  char buf[MAX_BUF];
  if(fd_digi)
    close(fd_digi);
  if(is_attached)
    {
      fd = open(GPIO_FILESYS_DIR "/unexport",O_WRONLY);
      if(fd<0)
        {

          perror("Error unexport -- method detach() \n");
          return 0;
        }
      len = snprintf(buf,sizeof(buf),"%d",gpio_num);
      write(fd,buf,len);
      close(fd);
      gpio_makeAvailable(gpio_num);
      is_attached = 0;
      return 1;
    }
  else
    {
      perror("No pin is currently attached\n");
      return 0;
    }


}

bool Digital_I_O::pinMode(bool mode)
{
  char buf[MAX_BUF];
  if(is_attached)
    {
      len = snprintf(buf,sizeof(buf),GPIO_FILESYS_DIR "/gpio%d/direction",gpio_num);
      fd = open(buf,O_WRONLY);
      if(fd<0)
        {
          perror("Error direction -- method pinMode()");
          return 0;
        }
      if(!mode)
        {
          write(fd,"out",4);
          cout<<"Making pin "<<gpio_num<<" output\n";
          io_mode = 0;
        }
      else
        {
          write(fd,"in",3);
          cout<<"Making pin "<<gpio_num<<" input\n";
          io_mode = 1;
        }
      close(fd);
      fd = NULL;
      len = NULL;
      fd_digi = NULL;
      return 1;
    }
  else
    {
      perror("No pin is currently attached\n");
      return 0;
    }
}



bool Digital_I_O::digitalWrite(bool value)
{
  if(!io_mode)
    {
      char buf[MAX_BUF];
      len = snprintf(buf, sizeof(buf), GPIO_FILESYS_DIR "/gpio%d/value",gpio_num);
      fd_digi = open(buf,O_WRONLY);
      if(fd_digi < 0)
        {
          perror("Error value -- method digitalWrite()\n");
          return 0;
        }
      if(value == 1)
        {
          write(fd_digi,"1",1);
          cout<<"Making pin "<<gpio_num<<" high\n";
        }
      else
        {
          write(fd_digi,"0",1);
          cout<<"Making pin "<<gpio_num<<" low\n";
        }
      close(fd_digi);
      return 1;
    }
  else
    {

      perror("Write Mode Not Selected\n");
      return 0;
    }
}


int Digital_I_O::digitalRead()
{
  char digi_read;
  char buf[MAX_BUF];

  if(io_mode)
    {
      len = snprintf(buf, sizeof(buf), GPIO_FILESYS_DIR "/gpio%d/value",gpio_num);
      fd_digi = open(buf,O_RDONLY);
      if(fd_digi < 0)
        {
          perror("Error value -- method digitalRead()\n");
          return -1;
        }
      read(fd_digi,&digi_read,sizeof(char));

      if(digi_read != '0')
        return 1;
      else
        return 0;

      close(fd_digi);
    }


  else
    {
      perror("Read Mode Not Selected\n");
      return -1;
    }
}


bool Digital_I_O::isAvailable(unsigned int pin_num)
{
  return gpio_isAvailable(pin_num);
}
