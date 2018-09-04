#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //necessário para strcpy

int main()
{
   // run servo program
   system("sudo ~/AracaCopter/ServoBlaster/user/servod --pcm");
   printf("Init\n");
   int x=1000,i=0;
   char str1[50]="echo 0=";
   char str2[4]="1000";
   char str3[22]="us > /dev/servoblaster";

   while(1)
    {
      if(i==0){
        x=x+1;
         if(x>=2000){
            i=1;
         }
      }
      if(i==1){
        x=x+1;
         if(x<=1000){
            i=0;
         }
      }
    itoa(x, str2, 10);
    strncat(str1, str2, 4);
    strncat(str1, str3, 22);
   // printf("string= %s\n",str1);
    system(str1);//go to 90 degree
    }
    return 0;
}
