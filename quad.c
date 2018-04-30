#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>
#include "MotionSensor.h"
int i=0;
int j=1;
volatile  int t1=0;
volatile  int t2=0;
struct timeval last_change;


void ISR1(void) {
   struct timeval now;
   gettimeofday(&now, NULL);
   if(j==1){
      t1 = now.tv_usec - last_change.tv_usec;
      j=1;
   }
   j++;
  if(j==3){
      t2 = now.tv_usec - last_change.tv_usec;
      j=1;
   }
   last_change = now;
}



int main()
{ 
   ms_open();
   wiringPiSetup();
   wiringPiISR (0, INT_EDGE_BOTH, &ISR1);
   //system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");

   while(1){
     ms_update();
     printf("CH1 : %d    ",t1); 
     printf("CH1 : %d \n ",t2); 
     //system("echo 0=1000us > /dev/servoblaster");//go to 0 degree      
     //printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}
