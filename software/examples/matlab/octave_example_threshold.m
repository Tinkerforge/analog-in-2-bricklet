function octave_example_threshold()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Analog In Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    ai = javaObject("com.tinkerforge.BrickletAnalogInV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    ai.setDebouncePeriod(10000);

    % Register voltage reached callback to function cb_voltage_reached
    ai.addVoltageReachedCallback(@cb_voltage_reached);

    % Configure threshold for voltage "smaller than 5 V"
    ai.setVoltageCallbackThreshold("<", 5*1000, 0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for voltage reached callback
function cb_voltage_reached(e)
    fprintf("Voltage: %g V\n", e.voltage/1000.0);
end
