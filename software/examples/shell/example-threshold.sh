#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Analog In Bricklet 2.0

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
tinkerforge call analog-in-v2-bricklet $uid set-debounce-period 10000

# Handle incoming voltage reached callbacks (parameter has unit mV)
tinkerforge dispatch analog-in-v2-bricklet $uid voltage-reached &

# Configure threshold for voltage "smaller than 5 V" (unit is mV)
tinkerforge call analog-in-v2-bricklet $uid set-voltage-callback-threshold smaller 5000 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
