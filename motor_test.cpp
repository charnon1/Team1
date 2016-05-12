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
// Sets both motors to rotate at 100% speed (255), then in reverse.
set_motor(1, 255);
set_motor(2, 255);
Sleep(1, 0);
set_motor(1, -255);
set_motor(2, -255);
Sleep(1, 0);
set_motor(1, 0);
set_motor(2, 0);
Sleep(4, 0);
//75% speed (191)
set_motor(1, 191);
set_motor(2, 191);
Sleep(2, 0);
set_motor(1, -191);
set_motor(2, -191);
Sleep(2, 0);
set_moto(1, 0);
set_motor(2, 0);
Sleep(4, 0);
//50% speed (127)
set_motor(1, 127);
set(motor(2, 127);
Sleep(3, 0);
set_motor(1, -127);
set_motor(2, -127);
Sleep(3, 0);
set_motor(1, 0);
set_motor(2, 0);
Sleep(4, 0);
//25% speed (56)
set_motor(1, 56);
set_motor(2, 56);
Sleep(4, 0);
set_motor(1, -56);
set_motor(2, -56);
Sleep(4, 0);
set_motor(1, 0);
set_motor(2, 0);
//Attempts to turn on the spot with both motors in full speed in opposite directions
set_motor(1, 255);
set_motor(2, -255);
Sleep(1, 0);
set_motor(1, 0);
set_motor(2, 0);
Sleep(4, 0);
//Turns at 75%
set_motor(1, -191);
set_motor(2, 191);
Sleep(2, 0);
set_motor(1, 0);
set_motor(2, 0);
Sleep(4, 0);
//Turns at 50%
set_motor(1, 127);
set_motor(2, -127);
Sleep(3, 0);
set_motor(1, 0);
set_motor)2, 0);
Sleep(4,0);
//Turns at 25%
set_motor(1, -56);
set_motor(2, 56);
sleep(4, 0);
//sets motors to 0
set_motor(1, 0);
set_motor(2, 0);

return 0;}
