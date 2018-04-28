#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>
int i=0;
void handle(void) {
	i++;
}

int main() {
	// Init
	wiringPiSetup();
	wiringPiISR(18, INT_EDGE_RISING, &handle);
	
	while(1){
		printf("%d",i);
	}
}
