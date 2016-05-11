//Code for making the motors repsond to input from the camera, i.e., making the robot
//follow white lines.

#include <stdio.h>
#include <time.h>

//Loading methods from ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);

int const delay;
int const kp;
int const ki;
int const kd;

int main(){
	int current_error = 0;
	int kp = 0.5;
	int proportional_signal;



//Loops for taking and analysing pictures to get errors
	for(n=0, n<30, n++){
		int take_picture();
		//calculates proportional error
		for (i=0, i<320, i++){
			if(get_pixel(i, 120, 3) > 200){
				error = (i-160);
			}
			current_error = current_error + error;
		}
		//calculates integral error

		//calculates derivative error

		//implements errors to control motors
		proportional_signal = error*kp;

		printf("Proportional signal is: %d", proportional_signal );

		if(current_error > 0){
			set_motor(1, (proportional_signal/(160*1*kp))*255);
		}
		else{
			set_motor(2, (proportional_signal/(160*1*kp))*255);
		}

	}


