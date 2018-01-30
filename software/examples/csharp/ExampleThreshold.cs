using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Analog In Bricklet 2.0

	// Callback function for voltage reached callback
	static void VoltageReachedCB(BrickletAnalogInV2 sender, int voltage)
	{
		Console.WriteLine("Voltage: " + voltage/1000.0 + " V");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletAnalogInV2 ai = new BrickletAnalogInV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		ai.SetDebouncePeriod(10000);

		// Register voltage reached callback to function VoltageReachedCB
		ai.VoltageReachedCallback += VoltageReachedCB;

		// Configure threshold for voltage "smaller than 5 V"
		ai.SetVoltageCallbackThreshold('<', 5*1000, 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
