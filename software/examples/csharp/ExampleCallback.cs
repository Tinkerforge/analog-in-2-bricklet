using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback function for voltage callback (parameter has unit mV)
	static void VoltageCB(BrickletAnalogInV2 sender, int voltage)
	{
		Console.WriteLine("Voltage: " + voltage/1000.0 + " V");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletAnalogInV2 ai = new BrickletAnalogInV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register voltage callback to function VoltageCB
		ai.Voltage += VoltageCB;

		// Set period for voltage callback to 1s (1000ms)
		// Note: The voltage callback is only called every second
		//       if the voltage has changed since the last call!
		ai.SetVoltageCallbackPeriod(1000);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
