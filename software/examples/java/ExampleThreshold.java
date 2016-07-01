import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletAnalogInV2;

public class ExampleThreshold {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Analog In Bricklet 2.0
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletAnalogInV2 ai = new BrickletAnalogInV2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		ai.setDebouncePeriod(10000);

		// Add voltage reached listener (parameter has unit mV)
		ai.addVoltageReachedListener(new BrickletAnalogInV2.VoltageReachedListener() {
			public void voltageReached(int voltage) {
				System.out.println("Voltage: " + voltage/1000.0 + " V");
			}
		});

		// Configure threshold for voltage "smaller than 5 V" (unit is mV)
		ai.setVoltageCallbackThreshold('<', 5*1000, 0);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
