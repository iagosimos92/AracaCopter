#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //necessário para strcpy
int main()
{
   // run servo program
   system("sudo ~/AracaCopter/ServoBlaster/user/servod --pcm");
   printf("Init\n");
   int x=1500;
   char str1[50];
   char str2[4];
   char str3[22];

   while(1)
    {
    str1="echo 0=";
    str2="1500";
    str3="us > /dev/servoblaster";
    strncat(str1, str2, 4);
    strncat(str1, str3, 22);
    printf("string= %s\n",str1);
    //system(str1);//go to 90 degree
    sleep(1);

    }
    return 0;
}
