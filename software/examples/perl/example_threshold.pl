#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletAnalogInV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ai = Tinkerforge::BrickletAnalogInV2->new(&UID, $ipcon); # Create device object

# Callback subroutine for voltage smaller than 5 V (parameter has unit mV)
sub cb_voltage_reached
{
    my ($voltage) = @_;

    print "Voltage: " . $voltage/1000.0 . " V\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$ai->set_debounce_period(10000);

# Register threshold reached callback to subroutine cb_voltage_reached
$ai->register_callback($ai->CALLBACK_VOLTAGE_REACHED, 'cb_voltage_reached');

# Configure threshold for "smaller than 5 V" (unit is mV)
$ai->set_voltage_callback_threshold('<', 5*1000, 0);

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
