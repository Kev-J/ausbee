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

STM32_USB_DEVICE_LIBRARY_PATH=$(PACKAGES_PATH)/stm32_usb_device_library
STM32_USB_DEVICE_LIBRARY_CORE_SRC_PATH=$(STM32_USB_DEVICE_LIBRARY_PATH)/Core
STM32_USB_DEVICE_LIBRARY_CLASS_SRC_PATH=$(STM32_USB_DEVICE_LIBRARY_PATH)/Class

# Include files
STM32_USB_DEVICE_LIBRARY_INCLUDES+=-I"$(STM32_USB_DEVICE_LIBRARY_PATH)/Core/Inc"
#TODO Choose which class with KConfig
STM32_USB_DEVICE_LIBRARY_INCLUDES+=-I"$(STM32_USB_DEVICE_LIBRARY_PATH)/Class/CDC/Inc"
STM32_USB_DEVICE_LIBRARY_INCLUDES+=-I"$(CURDIR)" # For config files

# Add the include directory to the libraries include dir
PACKAGES_INCLUDES+=$(STM32_USB_DEVICE_LIBRARY_INCLUDES)

# Source files
STM32_USB_DEVICE_LIBRARY_SRC_FILES+=$(STM32_USB_DEVICE_LIBRARY_CORE_SRC_PATH)/Src/usbd_core.c
STM32_USB_DEVICE_LIBRARY_SRC_FILES+=$(STM32_USB_DEVICE_LIBRARY_CORE_SRC_PATH)/Src/usbd_ctlreq.c
STM32_USB_DEVICE_LIBRARY_SRC_FILES+=$(STM32_USB_DEVICE_LIBRARY_CORE_SRC_PATH)/Src/usbd_ioreq.c
#TODO Choose which class with KConfig
STM32_USB_DEVICE_LIBRARY_SRC_FILES+=$(STM32_USB_DEVICE_LIBRARY_CLASS_SRC_PATH)/CDC/Src/usbd_cdc.c

# Object files list
STM32_USB_DEVICE_LIBRARY_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${STM32_USB_DEVICE_LIBRARY_SRC_FILES})

# Add the object files to the global object files list
OBJ_FILES+=$(STM32_USB_DEVICE_LIBRARY_OBJ_FILES)

# Build objects
$(STM32_USB_DEVICE_LIBRARY_OBJ_FILES): ${OUTPUT_PATH}/%.o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED)
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(STM32_USB_DEVICE_LIBRARY_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<
