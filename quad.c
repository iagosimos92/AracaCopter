#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>
#include "MotionSensor.h"

int i=0;
int j=1;
unsigned int ch1=0;
unsigned int ch2=0;
unsigned int ch=0;
struct timeval last_change;



void ISR1(void) {
   struct timeval now;
   if(j==1){
      gettimeofday(&now, NULL);
      ch = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);
      if(ch1<2200){
         ch1=ch;
      }
      j=2;
   }
  if(j==2){
      gettimeofday(&now, NULL);
      ch = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);
      if(ch1<2200){
          ch1=ch;
       }
      j=1;
   }
   last_change = now;
}



int main()
{
   
   wiringPiSetup();
   wiringPiISR (0, INT_EDGE_BOTH, &ISR1);
   system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");
   ms_open();
   
    
   while(1)
    {
    system("echo 0=1000us > /dev/servoblaster");//go to 0 degree      
    ms_update();
    printf("%d\n",ch);
    //printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}
