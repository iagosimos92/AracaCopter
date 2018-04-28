#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>

void handle(void) {
	printf("Rising\n");
}

int main() {
	// Init
	wiringPiSetup();
	wiringPiISR(18, INT_EDGE_RISING, &handle);
	if (wiringPiSetup () < 0)
	  {
	    printf ( "Unable to setup wiringPi: \n") ;
	    return 1 ;
	  }
	while(1){
		
	}
}
