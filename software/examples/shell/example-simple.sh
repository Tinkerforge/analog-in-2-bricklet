#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=ABC

# get current voltage (unit is mV)
tinkerforge call analog-in-v2-bricklet $uid get-voltage
