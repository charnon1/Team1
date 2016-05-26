# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor(int motor , int speed );
int main (){
  // This sets up the RPi hardware and ensures
  // everything is working correctly
  init(0);
  // Sets both motors to rotate at 50 speed (255)
  set_motor(1, 50);
  set_motor(2, 50);
  Sleep(1, 0);
  
  //Sets motors to 0 in case the Pi malfunctions and needs to be rescued
  set_motor(1, 0);
  set_motor(2, 0);
  Sleep(4, 0);

  //simulates the line being to the left by setting the right motor to 70 and the left motor to 30
  set_motor(1, 70);
  set_motor(2, 30);
  Sleep(3, 0);
  
  //Sets motors to 0 in case the Pi malfunctions and needs to be rescued
  set_motor(1, 0);
  set_motor(2, 0);
  Sleep(4, 0);
  
  //simulates the line being to the hard right by setting the left motor to 100 and the right motor to 0
  set_motor(1, 100);
  set_motor(2, 0);
  Sleep(3, 0);

  //sets motors to 0
  set_motor(1, 0);
  set_motor(2, 0);

return 0;}
