#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "MotionSensor.h"


int main() {
	ms_open();
	while(1){
		ms_update();
		printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
		return 2;
	}
        return 0;
}



