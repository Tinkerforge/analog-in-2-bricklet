import com.tinkerforge.BrickletAnalogInV2;
import com.tinkerforge.IPConnection;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "ABC"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletAnalogInV2 ai = new BrickletAnalogInV2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Set Period for voltage callback to 1s (1000ms)
		// Note: The voltage callback is only called every second if the
		//       voltage has changed since the last call!
		ai.setVoltageCallbackPeriod(1000);

		// Add and implement voltage listener (called if voltage changes)
		ai.addVoltageListener(new BrickletAnalogInV2.VoltageListener() {
			public void voltage(int voltage) {
				System.out.println("Voltage: " + voltage/1000.0 + " V");
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
