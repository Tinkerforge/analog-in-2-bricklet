function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletAnalogInV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'ABC'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    ai = BrickletAnalogInV2(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set Period for voltage callback to 1s (1000ms)
    % Note: The callback is only called every second if the 
    %       voltage has changed since the last call!
    ai.setVoltageCallbackPeriod(1000);

    % Register voltage callback to function cb_voltage
    set(ai, 'VoltageCallback', @(h, e) cb_voltage(e));

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback function for voltage callback (parameter has unit mV)
function cb_voltage(e)
    fprintf('Voltage: %g V\n', e.voltage/1000.0);
end
