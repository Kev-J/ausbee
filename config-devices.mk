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

ifeq ($(CONFIG_DEVICE_STM32F40_41xxx),y)
DEVICE_NAME=STM32F40_41xxx
else ifeq ($(CONFIG_DEVICE_STM32F427_437xx),y)
DEVICE_NAME=STM32F427_437xx
else ifeq ($(CONFIG_DEVICE_STM32F429_439xx),y)
DEVICE_NAME=STM32F429_439xx
else ifeq ($(CONFIG_DEVICE_STM32F401xx),y)
DEVICE_NAME=STM32F401xx
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
else ifeq ($(CONFIG_DEVICE_XMEGA16A4),y)
DEVICE_NAME=XMEGA16A4
GLOBAL_CFLAGS+=-mmcu=atxmega16a4 -DF_CPU=$(CRYSTAL_FREQUENCY)
endif

GLOBAL_CFLAGS+=-D$(DEVICE_NAME)

