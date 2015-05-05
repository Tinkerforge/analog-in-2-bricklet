<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletAnalogInV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletAnalogInV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'ABC'; // Change to your UID

// Callback for voltage smaller than 5V
function cb_reached($voltage)
{
    echo "Voltage dropped below 5V: " . $voltage / 1000.0 . "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$ai = new BrickletAnalogInV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$ai->setDebouncePeriod(10000);

// Register threshold reached callback to function cb_reached
$ai->registerCallback(BrickletAnalogInV2::CALLBACK_VOLTAGE_REACHED, 'cb_reached');

// Configure threshold for "smaller than 5V" (unit is mV)
$ai->setVoltageCallbackThreshold('<', 5*1000, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
