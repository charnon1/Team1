//Including libraries
#include <stdio.h>
#include <time.h>

//Loading methods form E101 library
extern "C" int init(int d_lev);
extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int connect_to_server(char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);

int main(){
	
	
	init(0); //sets up the RPi hardware ensuring everything is working correctly

	connect_to_server("130.195.6.196", 1024);       //connects to the gate server
	send_to_server("Please");       //sends "Please" to the server to attempt to get the$
	char message[24];
	receive_from_server(message);   //recieves the password from the server
	send_to_server(message);        //sends the password to the server to open the gate 
	Sleep(1,0);                     //sleeps for a time to wait for the gate to open 
	
	//sets motors to go to get the robot through the gate
	set_motor(0,150);
	set_motor(1,150);
	Sleep(3,0);
	
	//stops the motors when the robot should be through the gate
	set_motor(0,0);
	set_motor(1,0);

}