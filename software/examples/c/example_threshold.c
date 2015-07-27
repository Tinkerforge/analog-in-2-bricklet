#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_analog_in_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for voltage smaller than 5 V (parameter has unit mV)
void cb_voltage_reached(uint16_t voltage, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Voltage: %f V\n", voltage/1000.0);
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AnalogInV2 ai;
	analog_in_v2_create(&ai, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	analog_in_v2_set_debounce_period(&ai, 10000);

	// Register threshold reached callback to function cb_voltage_reached
	analog_in_v2_register_callback(&ai,
	                               ANALOG_IN_V2_CALLBACK_VOLTAGE_REACHED,
	                               (void *)cb_voltage_reached,
	                               NULL);

	// Configure threshold for "smaller than 5 V" (unit is mV)
	analog_in_v2_set_voltage_callback_threshold(&ai, '<', 5*1000, 0);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
