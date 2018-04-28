#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>

// Which GPIO pin we're using
#define PIN 18
// How much time a change must be since the last in order to count as a change
#define IGNORE_CHANGE_BELOW_USEC 100
struct timeval last_change;

void handle(void) {
	
	
	struct timeval now;
	unsigned long diff;

	gettimeofday(&now, NULL);

	// Time difference in usec
	diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

	printf("Rising\n");

	last_change = now;
}

int main(void) {
	// Init
	wiringPiSetup();

	// Set pin to output in case it's not
	pinMode(PIN, INPUT);

	// Time now
	gettimeofday(&last_change, NULL);

	// Bind to interrupt
	wiringPiISR(PIN, INT_EDGE_RISING, &handle);

	
	
}
