# use file to set a servo position in us
def servo_set_us(servo, pos):
    with open("/dev/servoblaster", 'w') as f:
        cmd = str(servo) + '=' + str(pos) + 'us'
        cmd += '\n'
        f.write(cmd)
servo_set_us(0,1000)
