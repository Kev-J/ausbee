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
# You should have received a copy of the GNU General Public License# along with AUSBEE.  If not, see <http://www.gnu.org/licenses/>.

# Path
CONFIG_FREERTOS_USE_HTTP=y
FREERTOS_VERSION=$(subst $(DQUOTE),,$(CONFIG_FREERTOS_VERSION_DOWNLOAD))
FREERTOS_URL=$(CONFIG_FREERTOS_URL_DOWNLOAD)
FREERTOS_ARCHIVE=FreeRTOS_V$(FREERTOS_VERSION).zip
FREERTOS_LOCAL_FILE_PATH=$(OPERATING_SYSTEMS_PATH)/FreeRTOS

FREERTOS_INCLUDE_PATH=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/include
FREERTOS_LOCAL_INCLUDE_PATH=include

ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
FREERTOS_TARGET_INCLUDE_PATH=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM4F
FREERTOS_TARGET_SRC_FILES=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
FREERTOS_TARGET_INCLUDE_PATH=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM3
FREERTOS_TARGET_SRC_FILES=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
endif 

FREERTOS_SRC_FILES= FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/tasks.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/croutine.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/list.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/queue.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/timers.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/MemMang/heap_1.c # TODO make it configurable

$(eval $(call pkg-generic,FREERTOS))


#ARCHIVE_FREERTOS_PATH=$(subst $(DQUOTE),,$(CONFIG_DOWNLOADS_DIR)/FreeRTOSV$(CONFIG_FREERTOS_VERSION_DOWNLOAD).zip)
#FREERTOS_PATH=$(OPERATING_SYSTEMS_PATH)/FreeRTOS
#FREERTOS_TOP_PATH=$(subst $(DQUOTE),,$(FREERTOS_PATH)/FreeRTOSV$(CONFIG_FREERTOS_VERSION_DOWNLOAD))
#FREERTOS_SRC_PATH=$(FREERTOS_TOP_PATH)/FreeRTOS/Source
#
#ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
#FREERTOS_SRC_PORT_PATH=$(FREERTOS_SRC_PATH)/portable/GCC/ARM_CM4F
#else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
#FREERTOS_SRC_PORT_PATH=$(FREERTOS_SRC_PATH)/portable/GCC/ARM_CM3
#endif 
#
##FreeRTOS Includes
#FREERTOS_INCLUDES_DIR=-I"$(FREERTOS_PATH)/include"
#FREERTOS_INCLUDES_DIR+=-I"$(FREERTOS_SRC_PATH)/include"
#FREERTOS_INCLUDES_DIR+=-I"$(INCLUDE_KCONFIG_PATH)"
#
#TARGET_INCLUDES+=$(FREERTOS_INCLUDES_DIR) -I"$(FREERTOS_SRC_PORT_PATH)"
#SIM_INCLUDES+=$(FREERTOS_INCLUDES_DIR)
#
##TODO make choice for user to remove unnecessary files
## Source files list
#FREERTOS_SRC_FILES=$(FREERTOS_SRC_PATH)/tasks.c
#FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/croutine.c
#FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/list.c
#FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/queue.c
#FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/timers.c
#FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/portable/MemMang/heap_1.c # TODO make it configurable
#
## Object files list
#FREERTOS_TARGET_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.$(TARGET_ARCH).o,${FREERTOS_SRC_FILES})
#FREERTOS_TARGET_DEP_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.$(TARGET_ARCH).d,${FREERTOS_SRC_FILES})
#FREERTOS_SIM_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.sim.o,${FREERTOS_SRC_FILES})
#FREERTOS_SIM_DEP_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.sim.d,${FREERTOS_SRC_FILES})
#FREERTOS_TARGET_OBJ_FILES+=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.$(TARGET_ARCH).o,${FREERTOS_TARGET_SRC_FILES})
#FREERTOS_TARGET_DEP_FILES+=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.$(TARGET_ARCH).d,${FREERTOS_TARGET_SRC_FILES})
#FREERTOS_SIM_OBJ_FILES+=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.sim.o,${FREERTOS_SIM_SRC_FILES})
#FREERTOS_SIM_DEP_FILES+=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.sim.d,${FREERTOS_SIM_SRC_FILES})
#
#
#
## Add object files to the global object files list
#TARGET_OBJ_FILES+=$(FREERTOS_TARGET_OBJ_FILES)
#TARGET_DEP_FILES+=$(FREERTOS_TARGET_DEP_FILES)
#SIM_OBJ_FILES+=$(FREERTOS_SIM_OBJ_FILES)
#SIM_DEP_FILES+=$(FREERTOS_SIM_DEP_FILES)
#
## Build objects
#$(FREERTOS_TARGET_OBJ_FILES): ${OUTPUT_PATH}/%.$(TARGET_ARCH).o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
#	$(call print_build,FreeRTOS,$(subst $(FREERTOS_SRC_PATH)/,,$<))
#	@mkdir -p $(dir $@)
#	$(TARGET_CC) $(TARGET_CFLAGS) $(GLOBAL_CFLAGS) $(TARGET_INCLUDES) $(GLOBAL_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
#	$(TARGET_CC) -o $@ $(TARGET_CFLAGS) $(GLOBAL_CFLAGS) $(TARGET_INCLUDES) $(GLOBAL_OPTIMISATION) -c $<
#
#$(FREERTOS_SIM_OBJ_FILES): ${OUTPUT_PATH}/%.sim.o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
#	$(call print_build,FreeRTOS,$(subst $(FREERTOS_SRC_PATH)/,,$<))
#	@mkdir -p $(dir $@)
#	$(SIM_CC) $(SIM_CFLAGS) $(GLOBAL_CFLAGS) $(SIM_INCLUDES) $(GLOBAL_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
#	$(SIM_CC) -o $@ $(SIM_CFLAGS) $(GLOBAL_CFLAGS) $(SIM_INCLUDES) $(GLOBAL_OPTIMISATION) -c $<
#
## Make sure that the archive has been extracted
#OPERATING_SYSTEMS_LOAD: $(FREERTOS_TOP_PATH)/.extracted
#$(FREERTOS_SRC_FILES): $(FREERTOS_TOP_PATH)/.extracted
#
## Extract files
#$(FREERTOS_TOP_PATH)/.extracted:$(ARCHIVE_FREERTOS_PATH)
#	$(UNZIP) -d $(FREERTOS_PATH) $<
#	$(TOUCH) $@
#
##TODO ifeq for choosing if FreeRTOS must be downloaded or not
## Download requested files
#$(ARCHIVE_FREERTOS_PATH):
#	$(MKDIR_P) $(CONFIG_DOWNLOADS_DIR)
#	$(WGET) -O $@ $(CONFIG_FREERTOS_URL_DOWNLOAD) || $(RM_RF) $@
#
#.PHONY: freertos-clean freertos-dirclean
#freertos-clean:
#	$(RM_RF) $(FREERTOS_OBJ_FILES)
#
#freertos-dirclean:
#	$(RM_RF) $(FREERTOS_TOP_PATH)
#
#-include $(FREERTOS_DEP_FILES)
