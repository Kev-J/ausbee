# This file is part of AUSBEE.
#
# Copyright (C) 2016 AUSBEE Developers <ausbee@googlegroups.com>
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

FATFS_PATH=$(PACKAGES_PATH)/fatfs
FATFS_SRC_PATH=$(FATFS_PATH)/src

# Include files
FATFS_INCLUDES+=-I"$(FATFS_SRC_PATH)"
FATFS_INCLUDES+=-I"$(CURDIR)" # For ff_conf.h

# Add the include directory to the libraries include dir
PACKAGES_INCLUDES+=$(FATFS_INCLUDES)

# Source files
FATFS_SRC_FILES+=$(wildcard $(FATFS_SRC_PATH)/*.c)

# Object files list
FATFS_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${FATFS_SRC_FILES})

# Add the object files to the global object files list
OBJ_FILES+=$(FATFS_OBJ_FILES)

# Build objects
$(FATFS_OBJ_FILES): ${OUTPUT_PATH}/%.o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED)
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PLATFORM_INCLUDES) $(STM32F7XX_HAL_DRIVER_INCLUDES) $(FATFS_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<
