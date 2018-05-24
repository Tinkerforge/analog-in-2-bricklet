#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletAnalogInV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Analog In Bricklet 2.0

# Callback subroutine for voltage callback
sub cb_voltage
{
    my ($voltage) = @_;

    print "Voltage: " . $voltage/1000.0 . " V\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ai = Tinkerforge::BrickletAnalogInV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register voltage callback to subroutine cb_voltage
$ai->register_callback($ai->CALLBACK_VOLTAGE, 'cb_voltage');

# Set period for voltage callback to 1s (1000ms)
# Note: The voltage callback is only called every second
#       if the voltage has changed since the last call!
$ai->set_voltage_callback_period(1000);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
