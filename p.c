#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>



int handle(void) {
	printf("Rising\n");
}

int main(void) {
	// Init
	wiringPiSetup();
	pinMode(18, INPUT);
	wiringPiISR(18, INT_EDGE_RISING, &handle);
	
	while(1){
		
	}
}
