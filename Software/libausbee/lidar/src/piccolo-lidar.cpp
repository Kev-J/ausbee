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
 * Based on informations of http://xv11hacking.wikispaces.com
 *
 **********************************************************************/
//TODO cite source
#include "lidar/piccolo-lidar.h"

void AUSBEE::PiccoloLidar::parse(unsigned char* frame, struct Lidar::data *data)
{
    for (int i = 0 ; i < DATAS_PER_FRAME ; i++) {
        data[i].angle = (frame[1] - 0xA0)*4 + i; // Get angle for each data structure in degree
        data[i].speed = ((frame[2] << 8) + frame[3]) >> 6; // Get actual rotation speed of the LIDAR
        data[i].distance_mm = frame[4+i*4] + ((frame[5+i*4] & 0x3F) << 8); // Get the measured distance for each data structure
        data[i].signal_strength = frame[6+i*4] + (frame[7+i*4] << 8); // Get signal strength

        // Check if no error occurs during measure
        if (frame[5+i*4] & 0x80) {
            data[i].error = true;
            data[i].error_code = frame[4+i*4];
        } else {
            data[i].error = false;
            data[i].error_code = 0x0;
        }

        // Fill the strength warning flag in the data structure
        if (frame[5+i*4] & 0x40)
            data[i].strengthWarning = true;
        else
            data[i].strengthWarning = false;
    }
}
