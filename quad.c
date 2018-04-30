#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>
#include "MotionSensor.h"

int i=0;
int j=0;
volatile int ch1=0;
volatile int t1=0;
volatile int ch2=0;
volatile int t2=0;
struct timeval last_change;

void ISR1(void) {
   struct timeval now;
   if(j==0){
      gettimeofday(&now, NULL);
      t1 = now.tv_usec - last_change.tv_usec;
      j=1;
   }
   j++;
   if(j==3){
      gettimeofday(&now, NULL);
      t2 = now.tv_usec - last_change.tv_usec;
      ch2=t1+t2;
      if(ch2>17000 && ch2<20000){
         if(t1>=1000 && t1<=2000){
            ch1=t1;
         }
         if(t2>=1000 && t2<=2000){
            ch1=t2;
         }
      }
      
      j=0;
    }
    gettimeofday(&last_change, NULL);
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
    printf("CH1 : %d   ",ch1);
    printf("  CH2 : %d\n",ch2);
    //printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}
