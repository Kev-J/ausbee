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

STM32F10X_STDPERIPH_DRIVER_LOCAL_FILE_PATH=$(PACKAGES_PATH)/stm32f10x_stdperiph_driver
STM32F10X_STDPERIPH_DRIVER_SRC_PATH=src

# Include files
STM32F10X_STDPERIPH_DRIVER_TARGET_LOCAL_INCLUDE_PATH=inc

# Source files
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_CAN),y)
STM32F10X_STDPERIPH_DRIVER_TARGET_LOCAL_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_can.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_RCC),y)
STM32F10X_STDPERIPH_DRIVER_TARGET_LOCAL_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_rcc.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_GPIO),y)
STM32F10X_STDPERIPH_DRIVER_TARGET_LOCAL_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_gpio.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_TIM),y)
STM32F10X_STDPERIPH_DRIVER_TARGET_LOCAL_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_tim.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_USART),y)
STM32F10X_STDPERIPH_DRIVER_TARGET_LOCAL_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_usart.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_MISC),y)
STM32F10X_STDPERIPH_DRIVER_TARGET_LOCAL_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/misc.c
endif
#TODO add others


$(eval $(call pkg-generic,STM32F10X_STDPERIPH_DRIVER))
