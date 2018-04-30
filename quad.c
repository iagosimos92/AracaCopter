#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>
#include "MotionSensor.h"

int i=0;
unsigned int ch1=0;
struct timeval last_change;

void rising1(void) {
   wiringPiISR (0, INT_EDGE_FALLING, &falling1);
   
   struct timeval now;
   gettimeofday(&now, NULL);
   last_change = now;
}
void falling1() {
  wiringPiISR (0, INT_EDGE_RISING, &rising1);
   
  gettimeofday(&now, NULL);
  ch1 = now.tv_usec - last_change.tv_usec;
}


int main()
{
   
   wiringPiSetup();
   wiringPiISR (0, INT_EDGE_RISING, &rising1);
   system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");
   ms_open();
   
    
   while(1)
    {
    system("echo 0=1000us > /dev/servoblaster");//go to 0 degree      
    ms_update();
    printf("%d/n",Ch1);
    //printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}
