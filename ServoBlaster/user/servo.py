# use file to set a servo position in us
def servo_set_us(servo, pos):
    with open("/dev/servoblaster", 'w') as fd:
        cmd = str(servo) + '=' + str(pos) + 'us'
        cmd += '\n'
        fd.write(cmd)
servo_set_us(0,1000)
