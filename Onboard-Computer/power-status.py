import RPi.GPIO as GPIO
import time
import os

# Map pins to P1 header on the Raspberry Pi
GPIO.setmode(GPIO.BOARD)

# Power Status of the RPi, as observed by the Arduino
pi_power_status = 8

# Manual override of power-off command
pi_override_cmd = 13

# Arduino-command to power-off RPi
pi_power_cmd_3v3 = 16

# Setup
GPIO.setup(pi_power_status, GPIO.OUT)
GPIO.setup(pi_override_cmd, GPIO.IN)
GPIO.setup(pi_power_cmd_3v3, GPIO.IN)

# Always set HIGH. When RPi is powered, the arduino knows through this signal.
GPIO.output(pi_power_status, GPIO.HIGH)

while True:
    if (GPIO.input(pi_override_cmd) or GPIO.input(pi_power_cmd_3v3)):
        if (GPIO.input(pi_override_cmd)):
            print 'PI_OVERRIDE_CMD is HIGH'
        else:
            print 'PI_POWER_CMD_3V3 is HIGH'
    else:
        # There is no cmd intructing to RPi to be on. Make sure this is true
        # in 5 seconds.
        print 'Initiating shutdown'
        time.sleep(5)
        if not (GPIO.input(pi_override_cmd) or GPIO.input(pi_power_cmd_3v3)):
            os.system("sudo shutdown now")
        else:
            print 'Aborting shutdown'
