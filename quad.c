#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "MotionSensor.h"

int i=0;
void myInterrupt(void) {i++;}

int main()
{
   
   wiringPiSetup();
	wiringPiISR (0, INT_EDGE_FALLING, &myInterrupt) ;
   
   ms_open();
   system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");
    
   while(1)
    {
    system("echo 0=1000us > /dev/servoblaster");//go to 0 degree      
    ms_update();
    //printf("%d",i);
    printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}

