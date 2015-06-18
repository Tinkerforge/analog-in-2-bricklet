#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletAnalogInV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'ABC'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ai = Tinkerforge::BrickletAnalogInV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current voltage (unit is mV)
my $voltage = $ai->get_voltage()/1000.0;
print "Voltage: $voltage V\n";

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
