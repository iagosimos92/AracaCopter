#include <stdio.h>
#include <wiringPi.h>

void init_env(){
  GPIO.setmode(GPIO.BOARD);
  GPIO.setwarnings(False);
}

void init_pin(){
  GPIO.setup(18,GPIO.IN);
}

int callback_exit(channel){
	//printf("Saindo do programa.");
}

init_env();
init_pin();

GPIO.add_event_detect(18, GPIO.FALLING, callback_exit);
//printf("Saindo do programa.");

while(1){}
