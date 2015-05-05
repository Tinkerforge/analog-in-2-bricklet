function octave_example_simple()
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "ABC"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    ai = java_new("com.tinkerforge.BrickletAnalogInV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current voltage (unit is mV)
    voltage = ai.getVoltage();
    fprintf("Voltage: %g V\n", voltage/1000.0);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end
