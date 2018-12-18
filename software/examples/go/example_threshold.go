package main

import (
	"fmt"
	"github.com/tinkerforge/go-api-bindings/analog_in_v2_bricklet"
	"github.com/tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Analog In Bricklet 2.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	ai, _ := analog_in_v2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get threshold receivers with a debounce time of 10 seconds (10000ms).
	ai.SetDebouncePeriod(10000)

	ai.RegisterVoltageReachedCallback(func(voltage uint16) {
		fmt.Printf("Voltage: %f V\n", float64(voltage)/1000.0)
	})

	// Configure threshold for voltage "smaller than 5 V".
	ai.SetVoltageCallbackThreshold('<', 5*1000, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
