#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   // run servo program
    system("sudo ~/AracaCopter/ServoBlaster/user/servod --pcm");
    printf("Init\n");
   int x=1000;
   while(1)
    {
    system("echo 0=%dus > /dev/servoblaster",x);//go to 0 degree
    sleep(1);
    x=1500;
    system("echo 0=%dus > /dev/servoblaster",x);//go to 90 degree
    sleep(1);
    x=2000;
    system("echo 0=%dus > /dev/servoblaster",x);//go to 180 degree
    sleep(1);
    }
    return 0;
}
