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

STM32F10X_STDPERIPH_DRIVER_PATH=$(PACKAGES_PATH)/stm32f10x_stdperiph_driver
STM32F10X_STDPERIPH_DRIVER_SRC_PATH=$(STM32F10X_STDPERIPH_DRIVER_PATH)/src

# Include files
STM32F10X_STDPERIPH_DRIVER_INC_PATH=-I"$(STM32F10X_STDPERIPH_DRIVER_PATH)/inc"

# Add the include directory to the libraries include dir
PACKAGES_INCLUDES+=$(STM32F10X_STDPERIPH_DRIVER_INC_PATH)

# Source files
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_CAN),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_can.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_RCC),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_rcc.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_GPIO),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_gpio.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_TIM),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_tim.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_USART),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_usart.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_MISC),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/misc.c
endif
#TODO add others

# Object files list
STM32F10X_STDPERIPH_DRIVER_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${STM32F10X_STDPERIPH_DRIVER_SRC_FILES})

# Add the object files to the global object files list
OBJ_FILES+=$(STM32F10X_STDPERIPH_DRIVER_OBJ_FILES)

# Build objects
$(STM32F10X_STDPERIPH_DRIVER_OBJ_FILES): ${OUTPUT_PATH}/%.o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED)
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(STM32F10X_STDPERIPH_DRIVER_INC_PATH) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<

.PHONY:stm32f10x_stdperiph_driver-clean stm32f10x_stdperiph_driver-doc

stm32f10x_stdperiph_driver-clean:
	$(RM_RF) $(STM32F10X_STDPERIPH_DRIVER_OBJ_FILES)

stm32f10x_stdperiph_driver-doc:
	$(CD) $(DOCUMENTATION_PATH)/STM32F10x_StdPeriph_Driver ; \
	$(DOXYGEN) $(DOCUMENTATION_PATH)/STM32F10x_StdPeriph_Driver/Doxyfile
