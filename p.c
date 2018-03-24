#include <stdio.h>
#include <wiringPi.h>

void main (){

	pinMode (18, INPUT) ; 
	GPIO.add_event_detect(18, GPIO.FALLING, callback_exit);
	//printf("Saindo do programa.");

	while(1){}

	void callback_exit(){
		//printf("Saindo do programa.");
	}
}
