<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletAnalogInV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletAnalogInV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'ABC'; // Change to your UID

// Callback function for voltage callback (parameter has unit mV)
function cb_voltage($voltage)
{
    echo "Voltage: " . $voltage / 1000.0 . " V\n";
}

$ipcon = new IPConnection(); // Create IP connection
$ai = new BrickletAnalogInV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Set Period for voltage callback to 1s (1000ms)
// Note: The callback is only called every second if the 
//      voltage has changed since the last call!
$ai->setVoltageCallbackPeriod(1000);

// Register illuminance callback to function cb_illuminance
$ai->registerCallback(BrickletAnalogInV2::CALLBACK_VOLTAGE, 'cb_voltage');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
