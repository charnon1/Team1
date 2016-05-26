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

//Defining constants //kp = 0.0015, kd = 0.00015

int const base_speed = 40;
int const delay_s = 0;
int const delay_us = 500000;

int main(){
	float kp = 0.0015;
	int proportional_signal;
	
	float kd = 0;
	int derivative_signal;
	
	int current_error; //used to store error for each image taken
	
	init(0); //sets up the RPi hardware ensuring everything is working correctly
		
	//program infintely loops until the switch is closed
	while(true){
		//getting input from camera and calculating an error signal
		take_picture();	
		current_error = 0; //resets error for a new image
		proportional_signal = 0;
		for(int i = 0; i<320;i++){
			int pixel_err = get_pixel(i,120,3); //gets the value of the pixel at location x = i, y = 120 (0-255)
			
			//removing noise from the pixel, giving white a value of 1 and black a value of 0
			//127 was used as it is 1/2 of 255
			if(pixel_err < 127){ 
				pixel_err = 0; //this is when the pixel is more  black					
							  
			}
			else{
				pixel_err = 1; //this is when the pixel is more white
			}
			
		
			current_error = current_error + (i-160)*pixel_err; //sums up the total error for all the pixels
		}
		
		printf("Current error: %d ", current_error);
		//at this stage image_error will be negative if white line is left, 
		//positive if white line right or 0 if centred. The largest it can be is 12,880 (sum of 160->0)
		//therefore the proportional signal should never go above ~120 so the motors do not get in input above 255
		//in reality the signal should not be higher than ~4000 -> target +50 for turning
		
		//processing error signal and implementing it into the motors
		proportional_signal = current_error*kp;
		printf("Proportional: %d ", proportional_signal);
	
				
		int response_signal = proportional_signal; //might want to be subtracting derivative?
		
	
		set_motor(1,base_speed + response_signal); //sets left motor
		printf("Set left motor: %d ", base_speed);
		set_motor(2,base_speed - response_signal); //sets right motor
		printf("Set right motor: %d \n", base_speed-response_signal);
		  
		
		
	
		Sleep(0,500000);
	}
}
