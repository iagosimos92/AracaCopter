from os import system
from time import sleep
import RPi.GPIO as GPIO


def callback_exit(channel):
	print("ISR")


def init():
	
	GPIO.setmode(GPIO.BOARD)
	GPIO.setwarnings(False)
	GPIO.setup(18,GPIO.IN)
	GPIO.add_event_detect(18, GPIO.FALLING, callback_exit)

while(1):

