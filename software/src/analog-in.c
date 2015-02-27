/* analog-in-bricklet
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * analog-in.c: Implementation of Analog In Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "analog-in.h"

#include "bricklib/bricklet/bricklet_communication.h"
#include "bricklib/drivers/adc/adc.h"
#include "bricklib/utility/util_definitions.h"
#include "brickletlib/bricklet_entry.h"
#include "brickletlib/bricklet_simple.h"
#include "config.h"

#define VOLTAGE_AVERAGE 50

#define SIMPLE_UNIT_VOLTAGE 0
#define SIMPLE_UNIT_ANALOG_VALUE 1

const SimpleMessageProperty smp[] = {
	{SIMPLE_UNIT_VOLTAGE, SIMPLE_TRANSFER_VALUE, SIMPLE_DIRECTION_GET}, // TYPE_GET_VOLTAGE
	{SIMPLE_UNIT_ANALOG_VALUE, SIMPLE_TRANSFER_VALUE, SIMPLE_DIRECTION_GET}, // TYPE_GET_ANALOG_VALUE
	{SIMPLE_UNIT_VOLTAGE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_SET}, // TYPE_SET_VOLTAGE_CALLBACK_PERIOD
	{SIMPLE_UNIT_VOLTAGE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_GET}, // TYPE_GET_VOLTAGE_CALLBACK_PERIOD
	{SIMPLE_UNIT_ANALOG_VALUE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_SET}, // TYPE_SET_ANALOG_VALUE_CALLBACK_PERIOD
	{SIMPLE_UNIT_ANALOG_VALUE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_GET}, // TYPE_GET_ANALOG_VALUE_CALLBACK_PERIOD
	{SIMPLE_UNIT_VOLTAGE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_SET}, // TYPE_SET_VOLTAGE_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_VOLTAGE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_GET}, // TYPE_GET_VOLTAGE_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_ANALOG_VALUE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_SET}, // TYPE_SET_ANALOG_VALUE_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_ANALOG_VALUE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_GET}, // TYPE_GET_ANALOG_VALUE_CALLBACK_THRESHOLD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_SET}, // TYPE_SET_DEBOUNCE_PERIOD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_GET}, // TYPE_GET_DEBOUNCE_PERIOD
};

const SimpleUnitProperty sup[] = {
	{voltage_from_analog_value, SIMPLE_SIGNEDNESS_INT, FID_VOLTAGE, FID_VOLTAGE_REACHED, SIMPLE_UNIT_ANALOG_VALUE}, // voltage
	{analog_value_from_mc, SIMPLE_SIGNEDNESS_UINT, FID_ANALOG_VALUE, FID_ANALOG_VALUE_REACHED, SIMPLE_UNIT_ANALOG_VALUE}, // analog value
};

const uint8_t smp_length = sizeof(smp);

void invocation(const ComType com, const uint8_t *data) {
	switch(((SimpleStandardMessage*)data)->header.fid) {
		case FID_SET_AVERAGING: {
			set_averaging(com, (SetAveraging*)data);
			return;
		}

		case FID_GET_AVERAGING: {
			get_averaging(com, (GetAveraging*)data);
			return;
		}

		default: {
			simple_invocation(com, data);
			break;
		}
	}

	if(((SimpleStandardMessage*)data)->header.fid > FID_LAST) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	adc_channel_enable(BS->adc_channel);
	SLEEP_MS(2);

	BC->moving_average_upto = MAX_MOVING_AVERAGE;
	reinitialize_moving_average();

	simple_constructor();
}

void destructor(void) {
	simple_destructor();
	adc_channel_disable(BS->adc_channel);
}

void reinitialize_moving_average(void) {
	int32_t initial_value = BA->adc_channel_get_data(BS->adc_channel);
	for(uint8_t i = 0; i < BC->moving_average_upto; i++) {
		BC->moving_average[i] = initial_value;
	}
	BC->moving_average_tick = 0;
	BC->moving_average_sum = initial_value*BC->moving_average_upto;
}

int32_t analog_value_from_mc(const int32_t value) {
	uint16_t analog_data = BA->adc_channel_get_data(BS->adc_channel);
	BC->moving_average_sum = BC->moving_average_sum -
	                         BC->moving_average[BC->moving_average_tick] +
	                         analog_data;

	BC->moving_average[BC->moving_average_tick] = analog_data;
	BC->moving_average_tick = (BC->moving_average_tick + 1) % BC->moving_average_upto;

	return (BC->moving_average_sum + BC->moving_average_upto/2)/BC->moving_average_upto;
}

int32_t voltage_from_analog_value(const int32_t value) {
	// assumed values are operating voltage of 3.3V and 1/13 opamp multiplier
	int32_t voltage = value*3300*13/MAX_ADC_VALUE;

	// We only have resolution for ~10mV, remove unreliable counts.
	uint8_t last_digit = voltage % 10;
	if(last_digit >= 5) {
		voltage += (10-last_digit);
	} else {
		voltage -= last_digit;
	}

	return voltage;
}

void set_averaging(const ComType com, const SetAveraging *data) {
	if(BC->moving_average_upto != data->length) {
		if(data->length < 1) {
			BC->moving_average_upto = 1;
		} else if(data->length > MAX_MOVING_AVERAGE) {
			BC->moving_average_upto = MAX_MOVING_AVERAGE;
		} else {
			BC->moving_average_upto = data->length;
		}

		reinitialize_moving_average();
	}

	BA->com_return_setter(com, data);
}

void get_averaging(const ComType com, const GetAveraging *data) {
	GetAveragingReturn gar;

	gar.header        = data->header;
	gar.header.length = sizeof(GetAveragingReturn);
	gar.length        = BC->moving_average_upto;

	BA->send_blocking_with_timeout(&gar, sizeof(GetAveragingReturn), com);
}

void tick(const uint8_t tick_type) {
	simple_tick(tick_type);
}
