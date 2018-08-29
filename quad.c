#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "MotionSensor.h"


int main()
{ 
   ms_open();
   //system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");

   while(1){
     ms_update();
     
     //system("echo 0=1000us > /dev/servoblaster");//go to 0 degree      
     //printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}
