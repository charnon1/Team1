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

//r Defining constants //kp = 0.0015, kd = 0.00015
double const kp = 0.015;//50/4000 -> used because we want +50 when ~4000 error signal might need to be higher
//double const kd = 0.001; //NEEDS TO BE TUNED
int const base_speed = 70;
int const delay_s = 0;
int const delay_us = 00000;

int main(){

        int current_error; //used to store error for each image taken
        int pixel_error; //used to store error for each pixel sample
        int previous_error = 0; //used to store the previous error to work out the derivative error

        int proportional_signal;
        int derivative_signal;

        int white_count; //keeps a count of how many white pixels are counted
        int pixel_val;
        int pixel_get;
        char message[24];

        init(1); //sets up the RPi hardware ensuring everything is working correctly

        connect_to_server("130.195.6.196", 1024);       //connects to the gate server
        send_to_server("Please");       //sends "Please" to the server to attempt to get the password for the gate
        recieve_from_server(message);   //recieves the password from the server
        send_to_server(message);        //sends the password to the server to open the gate - "this may be buggy"
        Sleep(2,0);                     //sleeps for a time to wait for the gate to open

        //program infintely loops - later only until the switch is opened?
        while(true){
                //getting input from camera and calculating an error signal
                take_picture();
                current_error = 0; //resets current_error for a new image
                for(int i = 0; i<320;i++){
                        pixel_get = get_pixel(i,120,3); //gets the value of the pixel at location x = i, y = 120 (0-255)

                        //removing noise from the pixel, giving white a value of 1 and black a value of 0
                        //127 was used as it is 1/2 of 255
                        if(pixel_get > 165){
                                pixel_val = 1; //this is when the pixel is more white than black

                        }
                        if(pixel_get <= 165){
                                pixel_val = 0; //this is when the pixel is more black than white
                        }

                        pixel_error = (i-160)*pixel_val; //gives a location to the error/white line (left or right of centre)
                        current_error = current_error + pixel_error; //sums up the total error for all the pixels
                }

                printf("Current error: %d ", current_error);
                //at this stage current_error will be negative if white line is left,
                //positive if white line right or 0 if centred. The largest it can be is 12,880 (sum of 160->0)
                //therefore the proportional signal should never go above ~120 so the motors do not get in input above 255
                proportional_signal = current_error*kp;
                //derivative_signal = current_error - previous_error/0.1 * kd;
                previous_error = current_error;
                printf("Proportional: %d ", 5, proportional_signal);
                //printf("Derivative: %d ", 5, derivative_signal);


                int response_signal = proportional_signal; //might want to be subtracting derivative?

                        set_motor(1,base_speed + response_signal); //causes the robot to turn
                        printf("Set left motor: %d ", 5, base_speed + response_signal);
                        set_motor(2,base_speed - response_signal);
                        printf("Set right motor: %d \n", 5, base_speed);
                printf("...............................\n");

        }
}

