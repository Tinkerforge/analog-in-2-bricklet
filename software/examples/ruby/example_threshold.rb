#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_analog_in_v2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
ai = BrickletAnalogInV2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
ai.set_debounce_period 10000

# Register voltage reached callback (parameter has unit mV)
ai.register_callback(BrickletAnalogInV2::CALLBACK_VOLTAGE_REACHED) do |voltage|
  puts "Voltage: #{voltage/1000.0} V"
end

# Configure threshold for voltage "smaller than 5 V" (unit is mV)
ai.set_voltage_callback_threshold '<', 5*1000, 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
