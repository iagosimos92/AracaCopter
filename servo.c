#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   // run servo program
    system("sudo ~/AracaCopter/ServoBlaster/user/servod --pcm");
    printf("Init\n");
   int x=1500;
   char string[50];
   while(1)
    {
    string +="echo 0=";
    string +=x;
    string +="us > /dev/servoblaster";
    string +='\0' 
    system(string);//go to 90 degree
    sleep(1);

    }
    return 0;
}
