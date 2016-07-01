#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Analog In Bricklet 2.0

# Get current voltage (unit is mV)
tinkerforge call analog-in-v2-bricklet $uid get-voltage
