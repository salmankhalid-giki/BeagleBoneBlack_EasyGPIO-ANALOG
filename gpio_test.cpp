#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <gpio_access.h>

using namespace std;



int main(void)
{

  int x;
  unsigned int y,z;
  unsigned int pin_num = 7;
  bool mode_confirm,write_confirm,attach_confirm,detach_confirm;
  bool mode_confirm1,write_confirm1,attach_confirm1,detach_confirm1;
  bool high = 1;
  int pinread;
  Digital_I_O pin_check,pin_check1;
  while(1)
    {
      cout<<"Enter GPIO number 1\n";
      cin>>y;
      cout<<"Enter GPIO number 2\n";
      cin>>z;
      if(y == 0 || z == 0)
        break;
      else
        {
          attach_confirm = pin_check.attach(y);
          if(!attach_confirm)
            cout<<"Error attaching 0\n";
          attach_confirm1 = pin_check1.attach(z);
          if(!attach_confirm1)
            cout<<"Error attaching 1\n";

          if(attach_confirm)
            {
              cout<<"Enter 0 for output and 1 for input--0\n";
              cin>>y;
              if(y == 0)
                {
                  mode_confirm = pin_check.pinMode(OUTPUT);
                  cout<<"Making pin output\n";
                }
              else
                {
                  mode_confirm = pin_check.pinMode(INPUT);
                  cout<<"Making pin input\n";
                }
            }

          if(attach_confirm1)
            {
              cout<<"Enter 0 for output and 1 for input--1\n";
              cin>>z;
              if(z == 0)
                {
                  mode_confirm1 = pin_check1.pinMode(OUTPUT);
                  cout<<"Making pin output\n";
                }
              else
                {
                  mode_confirm1 = pin_check1.pinMode(INPUT);
                  cout<<"Making pin input\n";
                }
            }


          while(mode_confirm || mode_confirm1)
            {

              if(y == 0 && mode_confirm)
                {
                  cout<<"Enter pin Output 1 for HIGH 0 for Low\n";
                  cin>>x;
                  if(x == 1)
                    write_confirm = pin_check.digitalWrite(HIGH);

                  else if(x == 0)
                    write_confirm = pin_check.digitalWrite(LOW);
                  else
                    mode_confirm = 0;
                }

              if(z == 0 && mode_confirm)
                {

                  cout<<"Enter pin Output 1 for HIGH 0 for Low\n";
                  cin>>x;
                  if(x == 1)
                    write_confirm = pin_check1.digitalWrite(HIGH);

                  else if(x == 0)
                    write_confirm = pin_check1.digitalWrite(LOW);
                  else
                    mode_confirm1;

                }


              if(y == 1 && mode_confirm)
                {
                  cout<<"Enter any integer to Read. Enter 0 to quit -- 0\n";
                  cin>>x;
                  if(x == 0)
                    mode_confirm = 0;
                  else
                    {
                      pinread = pin_check.digitalRead();
                      cout<<"Output is "<<pinread<<"\n";
                    }
                }



              if(z == 1 && mode_confirm1)
                {

                  cout<<"Enter any integer to Read. Enter 0 to quit -- 1\n";
                  cin>>x;
                  if(x == 0)
                    mode_confirm1 = 0;
                  else
                    {
                      pinread = pin_check1.digitalRead();
                      cout<<"Output is "<<pinread<<"\n";
                    }
                }



            }
          detach_confirm = pin_check.detach();
          detach_confirm1 = pin_check1.detach();


        }
    }
  return 0;
}
