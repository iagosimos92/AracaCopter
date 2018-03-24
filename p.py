from os import system
from time import sleep
import RPi.GPIO as GPIO

def init_env():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setwarnings(False)

def init_pin():
	GPIO.setup(14,GPIO.IN)

def callback_exit(channel):
	print("Saindo do programa.")


###################
# Inicio programa #
###################

init_env()
init_pin()

GPIO.add_event_detect(14, GPIO.FALLING, callback_exit)
print("Saindo do programa.")
loop=True
while(loop):
	loop=True
