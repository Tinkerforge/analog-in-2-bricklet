use std::{io, error::Error};
use std::thread;
use tinkerforge::{ip_connection::IpConnection, 
                  analog_in_v2_bricklet::*};


const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Analog In Bricklet 2.0.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let ai = AnalogInV2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
    // Don't use device before ipcon is connected.

		// Get threshold receivers with a debounce time of 10 seconds (10000ms).
		ai.set_debounce_period(10000);

     let voltage_reached_receiver = ai.get_voltage_reached_callback_receiver();

        // Spawn thread to handle received callback messages. 
        // This thread ends when the `ai` object
        // is dropped, so there is no need for manual cleanup.
        thread::spawn(move || {
            for voltage_reached in voltage_reached_receiver {           
                		println!("Voltage: {} V", voltage_reached as f32 /1000.0);
            }
        });

		// Configure threshold for voltage "smaller than 5 V".
		ai.set_voltage_callback_threshold('<', 5*1000, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
