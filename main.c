#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "MotionSensor.h"

#define delay_ms(a) usleep(a*1000)

float add_float();

float add_float() {
	ms_open();
	do{
		ms_update();
		//printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
		return ypr[YAW];
	}while(1);

	return 0;
}
