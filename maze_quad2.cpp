//Including libraries
#include <stdio.h>
#include <time.h>

//Loading methods form E101 library
extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int connect_to_server(char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int recieve_from_server(char message[24]);

int main(){

	//This sets up the RPi hardware and ensures that everything is working correctly
	init(1);

	//Connects to the gate server
	conect_to_server("130.195.6.196", 1024);

	//Sends the message "Please" to the gate server, which makes the server send the password to the Pi
	send_to_server("Please");

	//Recieves the password from the server and stores it in an array of chars
	char message[24];
	recieve_from_server(message);
	send_to_server(message);

	//Assumes that the server opened the gate within a second and drives forward at FULL SPEED
	//I have no idea if this is long enough to drive through the gate or short enough to stop the Pi before the next quadrant, so we should find out the optimum time to run the motors at full power for
	Sleep(1,0);
	set_motor(1,255);
	set_motor(2,255);
	Sleep(2,0);

	//Sets both motors to 0
	set_motor(1,0);
	set_motor(1,0);

	return 0;
}
