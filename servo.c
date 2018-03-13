#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   // run servo program
    system("sudo /home/pi/AracaCopter/ServoBlaster/user/servod --pcm");
    printf("\n");
   while(1)
    {
    printf("\n");
    printf("--------------------------------------->\n");
    system("echo 0=50 > /dev/servoblaster");//go to 0 degree
    printf("0                                           degree\n");
    sleep(1);

    system("echo 0=150 > /dev/servoblaster");//go to 90 degree
    printf("                 90                         degree\n");
    sleep(1);

    system("echo 0=250 > /dev/servoblaster");//go to 180 degree
    printf("                                     180    degree\n");
    sleep(1);
    }
    return 0;
}
