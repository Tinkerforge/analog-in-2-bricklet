function octave_example_threshold()
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "ABC"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    ai = java_new("com.tinkerforge.BrickletAnalogInV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set threshold callbacks with a debounce time of 10 seconds (10000ms)
    ai.setDebouncePeriod(10000);

    % Register threshold reached callback to function cb_reached
    ai.addVoltageReachedCallback(@cb_reached);

    % Configure threshold for "smaller than 5V" (unit is mV)
    ai.setVoltageCallbackThreshold(ai.THRESHOLD_OPTION_SMALLER, 5*1000, 0);
    
    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback for voltage less than 5V
function cb_reached(e)
    fprintf("Voltage dropped below 5V: %g\n", e.voltage/1000.0);
end
