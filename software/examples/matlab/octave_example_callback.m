function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Analog In Bricklet 2.0

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    ai = java_new("com.tinkerforge.BrickletAnalogInV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register voltage callback to function cb_voltage
    ai.addVoltageCallback(@cb_voltage);

    % Set period for voltage callback to 1s (1000ms)
    % Note: The voltage callback is only called every second
    %       if the voltage has changed since the last call!
    ai.setVoltageCallbackPeriod(1000);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for voltage callback (parameter has unit mV)
function cb_voltage(e)
    fprintf("Voltage: %g V\n", e.voltage/1000.0);
end
