#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>



void handle(void) {
	printf("Rising\n");
}

int main(void) {
	// Init
	wiringPiSetup();
	pinMode(24, INPUT);
	wiringPiISR(24, INT_EDGE_RISING, &handle);
	
	while(1){
		
	}
}
