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

PLATFORM_STM32F7DISCOVERY=$(PLATFORMS_PATH)/stm32f7discovery

PLATFORM_INCLUDES=-I"$(PLATFORM_STM32F7DISCOVERY)"
PLATFORM_INCLUDES+=-I"$(PLATFORM_STM32F7DISCOVERY)/drivers"

PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery.c

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_AUDIO),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_audio.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_CAMERA),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_camera.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_EEPROM),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_eeprom.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_LCD),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_lcd.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_QSPI),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_qspi.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_SD),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_sd.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_SDRAM),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_sdram.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_TS),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_ts.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_SD_DRIVER),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/drivers/sd_diskio.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_SDRAM_DRIVER),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/drivers/sdram_diskio.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_SRAM_DRIVER),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/drivers/sram_diskio.c
endif

ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY_USE_USBH_DRIVER),y)
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/drivers/usbh_diskio.c
endif

PLATFORM_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${PLATFORM_SRC_FILES})
PLATFORM_DEP_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.d,${PLATFORM_SRC_FILES})

OBJ_FILES+=$(PLATFORM_OBJ_FILES)
DEP_FILES+=$(PLATFORM_DEP_FILES)

$(PLATFORM_OBJ_FILES): $(OUTPUT_PATH)/%.o :$(AUSBEE_DIR)/%.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(call print_build,stm32f7discovery,$(subst $(AUSBEE_DIR)/,,$<))
	@mkdir -p $(dir $@)
	$(HOST_CC) $(HOST_CFLAGS) $(STM32F7XX_HAL_DRIVER_INCLUDES) $(PLATFORM_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PACKAGES_INCLUDES) $(PLATFORM_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<

.PHONY:platform_stm32f7discovery-clean
platform_stm32f7discovery-clean:
	$(RM_RF) $(OBJ_FILES)


-include $(PLATFORM_DEP_FILES)
