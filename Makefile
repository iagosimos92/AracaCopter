CXX=g++
CXXFLAGS= -Wall -g -O2
CXX_OPTS= -DMPU6050 for MPU6050

INSTALL=install

PROG=run

%.o: %.c                                                                         
	$(CXX) $(CXXFLAGS) $(CXX_OPTS) $< -o $@ 


all: $(PROG).o 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(PROG) \
		quad.c \
		MotionSensor/libMotionSensor.a \
		libs/libI2Cdev.a   \
		-lwiringPi

$(PROG).o: MotionSensor/libMotionSensor.a libs/libI2Cdev.a

MotionSensor/libMotionSensor.a:
	$(MAKE) -C MotionSensor/ 

libs/libI2Cdev.a:
	$(MAKE) -C libs/I2Cdev

install1:
	$(INSTALL) -m 755 $(PROG) $(DESTDIR)/usr/local/bin/

clean:
	cd MotionSensor && $(MAKE) clean
	cd libs/I2Cdev && $(MAKE) clean
	rm -rf *.o *~ *.mod
	rm -rf $(PROG)
