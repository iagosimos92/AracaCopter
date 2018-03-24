from os import system
from time import sleep
import RPi.GPIO as GPIO


GPIO.add_event_detect(18, GPIO.FALLING, callback_exit)

def init_env():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setwarnings(False)

def init_pin():
	GPIO.setup(18,GPIO.IN)

def callback_exit(channel):
	print("Saindo do programa.")


###################
# Inicio programa #
###################

init_env()
init_pin()



print("Botão pino 18...: Sair do programa")

loop=True
while(loop):
	loop=True
