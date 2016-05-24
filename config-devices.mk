# Get the device name for preprocessing according to stm32Fxxx.h

# This file is part of AUSBEE.
#
# Copyright (C) 2015 AUSBEE Developers <ausbee@googlegroups.com>
#
# AUSBEE is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# AUSBEE is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with AUSBEE.  If not, see <http://www.gnu.org/licenses/>.

#STM32F7XX Devices
ifeq ($(CONFIG_DEVICE_STM32F756xx),y)
DEVICE_NAME=STM32F756xx
else ifeq ($(CONFIG_DEVICE_STM32F746xx),y)
DEVICE_NAME=STM32F746xx
else ifeq ($(CONFIG_DEVICE_STM32F745xx),y)
DEVICE_NAME=STM32F745xx

# STM32F4XX Devices
else ifeq ($(CONFIG_DEVICE_STM32F40_41xxx),y)
DEVICE_NAME=STM32F40_41xxx
else ifeq ($(CONFIG_DEVICE_STM32F427_437xx),y)
DEVICE_NAME=STM32F427_437xx
else ifeq ($(CONFIG_DEVICE_STM32F429_439xx),y)
DEVICE_NAME=STM32F429_439xx
else ifeq ($(CONFIG_DEVICE_STM32F401xx),y)
DEVICE_NAME=STM32F401xx

# STM32F1XX Devices
else ifeq ($(CONFIG_DEVICE_STM32F10X_LD),y)
DEVICE_NAME=STM32F10X_LD
else ifeq ($(CONFIG_DEVICE_STM32F10X_LD_VL),y)
DEVICE_NAME=STM32F10X_LD_VL
else ifeq ($(CONFIG_DEVICE_STM32F10X_MD),y)
DEVICE_NAME=STM32F10X_MD
else ifeq ($(CONFIG_DEVICE_STM32F10X_MD_VL),y)
DEVICE_NAME=STM32F10X_MD_VL
else ifeq ($(CONFIG_DEVICE_STM32F10X_HD),y)
DEVICE_NAME=STM32F10X_HD
else ifeq ($(CONFIG_DEVICE_STM32F10X_HD_VL),y)
DEVICE_NAME=STM32F10X_HD_VL
else ifeq ($(CONFIG_DEVICE_STM32F10X_XL),y)
DEVICE_NAME=STM32F10X_XL
else ifeq ($(CONFIG_DEVICE_STM32F10X_CL),y)
DEVICE_NAME=STM32F10X_CL

# STM32L0XX
else ifeq ($(CONFIG_DEVICE_STM32L011xx),y)
DEVICE_NAME=STM32L011xx
else ifeq ($(CONFIG_DEVICE_STM32L021xx),y)
DEVICE_NAME=STM32L021xx
else ifeq ($(CONFIG_DEVICE_STM32L031xx),y)
DEVICE_NAME=STM32L031xx
else ifeq ($(CONFIG_DEVICE_STM32L041xx),y)
DEVICE_NAME=STM32L041xx
else ifeq ($(CONFIG_DEVICE_STM32L051xx),y)
DEVICE_NAME=STM32L051xx
else ifeq ($(CONFIG_DEVICE_STM32L052xx),y)
DEVICE_NAME=STM32L052xx
else ifeq ($(CONFIG_DEVICE_STM32L053xx),y)
DEVICE_NAME=STM32L053xx
else ifeq ($(CONFIG_DEVICE_STM32L061xx),y)
DEVICE_NAME=STM32L061xx
else ifeq ($(CONFIG_DEVICE_STM32L062xx),y)
DEVICE_NAME=STM32L062xx
else ifeq ($(CONFIG_DEVICE_STM32L063xx),y)
DEVICE_NAME=STM32L063xx
else ifeq ($(CONFIG_DEVICE_STM32L071xx),y)
DEVICE_NAME=STM32L071xx
else ifeq ($(CONFIG_DEVICE_STM32L072xx),y)
DEVICE_NAME=STM32L072xx
else ifeq ($(CONFIG_DEVICE_STM32L073xx),y)
DEVICE_NAME=STM32L073xx
else ifeq ($(CONFIG_DEVICE_STM32L081xx),y)
DEVICE_NAME=STM32L081xx
else ifeq ($(CONFIG_DEVICE_STM32L082xx),y)
DEVICE_NAME=STM32L082xx
else ifeq ($(CONFIG_DEVICE_STM32L083xx),y)
DEVICE_NAME=STM32L083xx
endif
