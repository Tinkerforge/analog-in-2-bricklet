/* analog-in-v2-bricklet
 * Copyright (C) 2015 Olaf Lüke <olaf@tinkerforge.com>
 *
 * analog-in.h: Implementation of Analog In 2.0 Bricklet messages
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

#ifndef ANALOG_IN_H
#define ANALOG_IN_H

#include <stdint.h>
#include "bricklib/com/com.h"
#include "bricklib/com/com_common.h"

#define FID_GET_VOLTAGE 1
#define FID_GET_ANALOG_VALUE 2
#define FID_SET_VOLTAGE_CALLBACK_PERIOD 3
#define FID_GET_VOLTAGE_CALLBACK_PERIOD 4
#define FID_SET_ANALOG_VALUE_CALLBACK_PERIOD 5
#define FID_GET_ANALOG_VALUE_CALLBACK_PERIOD 6
#define FID_SET_VOLTAGE_CALLBACK_THRESHOLD 7
#define FID_GET_VOLTAGE_CALLBACK_THRESHOLD 8
#define FID_SET_ANALOG_VALUE_CALLBACK_THRESHOLD 9
#define FID_GET_ANALOG_VALUE_CALLBACK_THRESHOLD 10
#define FID_SET_DEBOUNCE_PERIOD 11
#define FID_GET_DEBOUNCE_PERIOD 12
#define FID_SET_MOVING_AVERAGE 13
#define FID_GET_MOVING_AVERAGE 14
#define FID_VOLTAGE 15
#define FID_ANALOG_VALUE 16
#define FID_VOLTAGE_REACHED 17
#define FID_ANALOG_VALUE_REACHED 18

#define FID_LAST 14

typedef struct {
	MessageHeader header;
	uint8_t range;
} __attribute__((__packed__)) SetRange;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetRange;

typedef struct {
	MessageHeader header;
	uint8_t range;
} __attribute__((__packed__)) GetRangeReturn;

typedef struct {
	MessageHeader header;
	uint8_t length;
} __attribute__((__packed__)) SetMovingAverage;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetMovingAverage;

typedef struct {
	MessageHeader header;
	uint8_t length;
} __attribute__((__packed__)) GetMovingAverageReturn;

int32_t analog_value_from_mc(const int32_t value);
int32_t voltage_from_analog_value(const int32_t value);
void set_range(const ComType com, const SetRange *data);
void get_range(const ComType com, const GetRange *data);
void set_moving_average(const ComType com, const SetMovingAverage *data);
void get_moving_average(const ComType com, const GetMovingAverage *data);
void reinitialize_moving_average(void);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
