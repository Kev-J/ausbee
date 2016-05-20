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

PLATFORMS_INCLUDES_DIR=-I"$(PLATFORM_STM32F7DISCOVERY)"

PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_audio.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_camera.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_eeprom.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_lcd.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_qspi.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_sd.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_sdram.c
PLATFORM_SRC_FILES+=$(PLATFORM_STM32F7DISCOVERY)/stm32746g_discovery_ts.c
PLATFORM_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${PLATFORM_SRC_FILES})
PLATFORM_DEP_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.d,${PLATFORM_SRC_FILES})

OBJ_FILES+=$(PLATFORM_OBJ_FILES)
DEP_FILES+=$(PLATFORM_DEP_FILES)

$(PLATFORM_OBJ_FILES): $(OUTPUT_PATH)/%.o :$(AUSBEE_DIR)/%.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(call print_build,stm32f7discovery,$(subst $(AUSBEE_DIR)/,,$<))
	@mkdir -p $(dir $@)
	#$(HOST_CC) $(HOST_CFLAGS) $(STM32F4XX_STDPERIPH_DRIVER_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	#$(HOST_CC) $(HOST_CFLAGS) $(STM32F4XX_STDPERIPH_DRIVER_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	#$(HOST_CC) -o $@ $(HOST_CFLAGS) $(STM32F4XX_STDPERIPH_DRIVER_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<
	$(HOST_CC) $(HOST_CFLAGS) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<

.PHONY:platform_stm32f7discovery-clean
platform_stm32f7discovery-clean:
	$(RM_RF) $(OBJ_FILES)


-include $(PLATFORM_DEP_FILES)
