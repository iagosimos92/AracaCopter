#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>
#include "MotionSensor.h"

int i=0;
int j=1;
int ch1=0;
int ch1ant=0;
int t1=0;
struct timeval last_change;



void ISR1(void) {
   struct timeval now;
   if(j==1){
      gettimeofday(&now, NULL);
      t1 = now.tv_sec - last_change.tv_usec;
      if(t1<2200 || t1>800){
         ch1=t1;
      }
      j=2;
   }
  if(j==2){
      gettimeofday(&now, NULL);
      t1 = now.tv_usec - last_change.tv_usec;
      if(t1<2200 || t1>800){
          ch1=t1;
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
    //if (abs(ch1-ch1ant)>350){
    ///   ch1=ch1ant;        
    //}
    printf("%d\n",ch1);
      
    ch1ant=ch1;
    //printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}
