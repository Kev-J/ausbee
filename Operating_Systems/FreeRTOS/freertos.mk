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

# Path
ARCHIVE_FREERTOS_PATH=$(subst $(DQUOTE),,$(CONFIG_DOWNLOADS_DIR)/FreeRTOSV$(CONFIG_FREERTOS_VERSION_DOWNLOAD).zip)
FREERTOS_PATH=$(OPERATING_SYSTEMS_PATH)/FreeRTOS
FREERTOS_TOP_PATH=$(subst $(DQUOTE),,$(FREERTOS_PATH)/FreeRTOSV$(CONFIG_FREERTOS_VERSION_DOWNLOAD))
FREERTOS_SRC_PATH=$(FREERTOS_TOP_PATH)/FreeRTOS/Source

ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
FREERTOS_SRC_PORT_PATH=$(FREERTOS_SRC_PATH)/portable/GCC/ARM_CM4F
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
FREERTOS_SRC_PORT_PATH=$(FREERTOS_SRC_PATH)/portable/GCC/ARM_CM3
endif 

#FreeRTOS Includes
FREERTOS_INCLUDES_DIR=-I"$(FREERTOS_PATH)/include"
FREERTOS_INCLUDES_DIR+=-I"$(FREERTOS_SRC_PATH)/include"
FREERTOS_INCLUDES_DIR+=-I"$(FREERTOS_SRC_PORT_PATH)"
FREERTOS_INCLUDES_DIR+=-I"$(INCLUDE_KCONFIG_PATH)"
OPERATING_SYSTEMS_INCLUDES=$(FREERTOS_INCLUDES_DIR)

#TODO make choice for user to remove unnecessary files
# Source files list
FREERTOS_SRC_FILES=$(FREERTOS_SRC_PATH)/tasks.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/croutine.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/list.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/queue.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/timers.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/portable/MemMang/heap_1.c # TODO make it configurable
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PORT_PATH)/port.c

# Object files list
FREERTOS_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${FREERTOS_SRC_FILES})
FREERTOS_DEP_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.d,${FREERTOS_SRC_FILES})

# Add object files to the global object files list
OBJ_FILES+=$(FREERTOS_OBJ_FILES)

# Build objects
$(FREERTOS_OBJ_FILES): ${OUTPUT_PATH}/%.o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(FREERTOS_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

$(FREERTOS_DEP_FILES): ${OUTPUT_PATH}/%.d :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(FREERTOS_INCLUDES_DIR) $(HOST_OPTIMISATION) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(@:.d=.o)" "$<"

# Make sure that the archive has been extracted
$(FREERTOS_SRC_FILES): $(FREERTOS_TOP_PATH)/.extracted

# Extract files
$(FREERTOS_TOP_PATH)/.extracted:$(ARCHIVE_FREERTOS_PATH)
	$(UNZIP) -d $(FREERTOS_PATH) $<
	$(TOUCH) $@

#TODO ifeq for choosing if FreeRTOS must be downloaded or not
# Download requested files
$(ARCHIVE_FREERTOS_PATH):
	$(MKDIR_P) $(CONFIG_DOWNLOADS_DIR)
	$(WGET) -O $@ $(CONFIG_FREERTOS_URL_DOWNLOAD)

.PHONY: freertos-clean freertos-dirclean
freertos-clean:
	$(RM_RF) $(FREERTOS_OBJ_FILES)

freertos-dirclean:
	$(RM_RF) $(FREERTOS_TOP_PATH)

-include $(FREERTOS_DEP_FILES)
