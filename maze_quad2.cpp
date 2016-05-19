
//Including libraries
#include <stdio.h>
#include <time.h>

//Loading methods form E101 library
extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int connect_to_server(char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);

//Defining constants
double const kp = 0.5;
double const kd = 0.5;
int const base_speed = 80;
int const delay_s = 0;
int const delay_us = 250000;

int main(){

        double current_error = 0;
        double proportional_signal;
        double error;

        //This sets up the RPi hardware and ensures that everything is working correctly
        init(1);

        //Connects to the gate server
//      connect_to_server("130.195.6.196", 1024);

        //Sends the message "Please" to the gate server, which makes the server send the pas$
//      send_to_server("Please");

        //Recieves the password from the server and stores it in an array of chars
//      char message[24];
//      receive_from_server(message);
//      send_to_server(message);

        //Loops for taking and analysing pictures to get errors. Runs 30 times
        for(int n=0; n<30; n++){
                take_picture();

                //calculates proportional error
                for (int i=0; i<320; i++){
                error = (i-160)*get_pixel(120, i, 3);
                        current_error = current_error + error;
                }
                //calculates derivative error

                //implements errors to control motors
                proportional_signal = current_error*kp;

                printf("Proportional signal is: %d\n", proportional_signal );

                set_motor(1, base_speed - proportional_signal);
                set_motor(2, base_speed + proportional_signal);

                //sleeps for the defined delays
                Sleep(delay_s, delay_us);
        }

        //Sets both motors to 0
        set_motor(1, 0);

        set_motor(2, 0);

        return 0;
}
