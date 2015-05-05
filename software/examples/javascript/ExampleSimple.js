var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'ABC'; // Change to your UID

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var ai = new Tinkerforge.BrickletAnalogInV2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Get current voltage (unit is mV)
        ai.getVoltage(
            function(voltage) {
                console.log('Voltage: '+voltage/1000+' V');
            },
            function(error) {
                console.log('Error: '+error);
            }
        );
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
