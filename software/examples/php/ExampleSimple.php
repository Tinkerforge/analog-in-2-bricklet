<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletAnalogInV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletAnalogInV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change to your UID

$ipcon = new IPConnection(); // Create IP connection
$ai = new BrickletAnalogInV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current voltage (unit is mV)
$voltage = $ai->getVoltage();
echo "Voltage: " . $voltage/1000.0 . " V\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
