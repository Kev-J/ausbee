/**********************************************************************
 * This file is part of LIBAUSBEE.
 * 
 * LIBAUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LIBAUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LIBAUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (C) EIRBOT
 *
 * Authors :    Kevin JOLY <joly.kevin25@gmail.com>
 *
 **********************************************************************/
#ifndef LIDAR_H
#define LIDAR_H

//#include "AUSBEE/lidar.h"

#ifdef STM32F4XX
#include <stm32f4xx.h>
#elif STM32F10X
#include <stm32f10x.h>
#else
#include <stdint.h>
#endif

#define AUSBEE_LIDAR_PICCOLO_FRAME_LENGTH 22
#define AUSBEE_LIDAR_PICCOLO_DATA_LENGTH 4

struct ausbee_lidar_data{
	uint16_t angle; // Angle of the point
	int speed; // Speed of the Lidar
	int distance_mm; // Measured distance
	uint8_t signal_strength; // Strength of the signal
	uint8_t error; // 1 if an error is encountered
	uint8_t strengthWarning; // 1 if the signal strength is too low
	uint8_t error_code; // Error code in case of error
};

void ausbee_lidar_parse_piccolo(unsigned char frame[AUSBEE_LIDAR_PICCOLO_FRAME_LENGTH], struct ausbee_lidar_data data[AUSBEE_LIDAR_PICCOLO_DATA_LENGTH]);

#endif
