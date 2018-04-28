#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>

void handle() {
	printf("Rising\n");
}

int main() {
	// Init
	wiringPiSetup();
	wiringPiISR(18, INT_EDGE_RISING, handle);
	
	while(1){
		
	}
}
