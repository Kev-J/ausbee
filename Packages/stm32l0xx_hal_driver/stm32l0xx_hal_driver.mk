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

STM32L0XX_HAL_DRIVER_PATH=$(PACKAGES_PATH)/stm32l0xx_hal_driver
STM32L0XX_HAL_DRIVER_SRC_PATH=$(STM32L0XX_HAL_DRIVER_PATH)/Src

# Include files
STM32L0XX_HAL_DRIVER_INCLUDES+=-I"$(STM32L0XX_HAL_DRIVER_PATH)/Inc"
STM32L0XX_HAL_DRIVER_INCLUDES+=-I"$(CURDIR)" # For stm32f7xx_hal_conf.h

# Add the include directory to the libraries include dir
PACKAGES_INCLUDES+=$(STM32L0XX_HAL_DRIVER_INCLUDES)

# Source files
STM32L0XX_HAL_DRIVER_SRC_FILES+=$(wildcard $(STM32L0XX_HAL_DRIVER_SRC_PATH)/*.c)

# Object files list
STM32L0XX_HAL_DRIVER_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${STM32L0XX_HAL_DRIVER_SRC_FILES})

# Add the object files to the global object files list
OBJ_FILES+=$(STM32L0XX_HAL_DRIVER_OBJ_FILES)

# Build objects
$(STM32L0XX_HAL_DRIVER_OBJ_FILES): ${OUTPUT_PATH}/%.o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED)
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(STM32L0XX_HAL_DRIVER_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<
