#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   // run servo program
    system("sudo /AracaCopter/ServoBlaster/user/servod --pcm");
    printf("Init\n");
   while(1)
    {
    printf("\n");
    system("echo 0=1000us > /dev/servoblaster");//go to 0 degree
    sleep(1);

    system("echo 0=1500us > /dev/servoblaster");//go to 90 degree
    sleep(1);

    system("echo 0=2000us > /dev/servoblaster");//go to 180 degree
    sleep(1);
    }
    return 0;
}
