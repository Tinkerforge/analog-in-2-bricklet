#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_analog_in_v2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'ABC' # Change to your UID

ipcon = IPConnection.new # Create IP connection
ai = BrickletAnalogInV2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Set Period for voltage callback to 1s (1000ms)
# Note: The callback is only called every second if the 
#       voltage has changed since the last call!
ai.set_voltage_callback_period 1000

# Register illuminance callback (parameter has unit mV)
ai.register_callback(BrickletAnalogInV2::CALLBACK_VOLTAGE) do |voltage|
  puts "Voltage: #{voltage/1000.0} V"
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
