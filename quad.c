#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "MotionSensor.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <wiringPi.h>

int main()
{  
 unsigned int x=0;
    x=millis();
    printf("Tempo= %d",x);

    sleep(1);
    return 0;
}
