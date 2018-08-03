import logging
import os
import sys
import time

import RPi.GPIO as GPIO

logging_level = logging.DEBUG
logging.basicConfig(filename='data-station.log',
                        level=logging_level,
                        format='%(asctime)s.%(msecs)03d %(levelname)s \t%(message)s',
                        datefmt="%d %b %Y %H:%M:%S")

# Log to STDOUT
ch = logging.StreamHandler(sys.stdout)
ch.setLevel(logging_level)
formatter = logging.Formatter('%(asctime)s.%(msecs)03d %(levelname)s %(message)s')
ch.setFormatter(formatter)
logging.getLogger().addHandler(ch)

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
            logging.debug("PI_OVERRIDE_CMD is HIGH")
        else:
            logging.debug("PI_POWER_CMD_3V3 is HIGH")
    else:
        # There is no cmd intructing to RPi to be on. Make sure this is true
        # in 5 seconds.
        logging.info("Initiating shutdown...")
        time.sleep(5)
        if not (GPIO.input(pi_override_cmd) or GPIO.input(pi_power_cmd_3v3)):
            ogging.info("Shutting down")
            os.system("sudo shutdown now")
        else:
            logging.info("Aborting shutdown")
