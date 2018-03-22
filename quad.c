#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "MotionSensor.h"

int main()
{
   ms_open();
   // run servo program
    //system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");
    printf("Init\n");
   while(1)
    {
    system("echo 0=1000us > /dev/servoblaster");//go to 0 degree
    sleep(1);

    system("echo 0=1500us > /dev/servoblaster");//go to 90 degree
    sleep(1);

    system("echo 0=2000us > /dev/servoblaster");//go to 180 degree
    sleep(1);
      
    system("echo 0=1500us > /dev/servoblaster");//go to 90 degree
    sleep(1);
      
    ms_update();
    printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    return 0;
}

