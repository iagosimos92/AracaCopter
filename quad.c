#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>
#include "MotionSensor.h"

volatile  int ch1=0;
struct timeval last_change;


void rising1(void) {
   gettimeofday(&last_change, NULL);
}

void falling1(void) {
   struct timeval now;
   gettimeofday(&now, NULL);
   ch1 = now.tv_usec - last_change.tv_usec;
}



int main()
{ 
   ms_open();
   wiringPiSetup();
   wiringPiISR (1, INT_EDGE_FALLING, &falling1);
   wiringPiISR (1, INT_EDGE_RISING, &rising1);
   //system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");

   while(1){
     ms_update();
     printf("CH1 : %d    ",ch1); 
     //system("echo 0=1000us > /dev/servoblaster");//go to 0 degree      
     //printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}
