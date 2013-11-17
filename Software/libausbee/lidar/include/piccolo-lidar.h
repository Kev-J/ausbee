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
#ifndef PICCOLO_H
#define PICCOLO_H

#include "lidar.h"

namespace AUSBEE {
    class PiccoloLidar : public Lidar {
        public:
            static const int FRAME_LENGTH = 22;
            static const int DATAS_PER_FRAME = 4;
        public:
            void parse(unsigned char* frame, struct Lidar::data data[DATAS_PER_FRAME]);
    };
}
#endif
