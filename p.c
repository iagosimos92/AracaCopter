#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>
int i=0;

void myInterrupt(void) {i++;}

int main(void) {

	wiringPiSetup();
	wiringPiISR (24, INT_EDGE_FALLING, &myInterrupt) ;

	while(1){
		printf("%d",i);
	}
}
