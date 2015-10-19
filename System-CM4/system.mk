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

CMSIS_DEVICE_SUPPORT_PATH=$(SYSTEM_PATH)/CMSIS/Device/ST/STM32F4xx
CMSIS_CORE_SUPPORT_PATH=$(SYSTEM_PATH)/CMSIS/Include

LINKER_SCRIPT=$(OUTPUT_PATH)/link.ld
LINKER_SCRIPT_INPUT=$(SYSTEM_PATH)/link.ld.in

SYSTEM_INCLUDES=-I"$(CMSIS_DEVICE_SUPPORT_PATH)/Include"
SYSTEM_INCLUDES+=-I"$(CMSIS_CORE_SUPPORT_PATH)"
SYSTEM_INCLUDES+=-I"$(SYSTEM_PATH)/include"

SYSTEM_SRC_C_FILES+=$(CMSIS_DEVICE_SUPPORT_PATH)/Source/Templates/system_stm32f4xx.c
SYSTEM_SRC_C_FILES+=$(SYSTEM_PATH)/syscalls.c

ifeq ($(CONFIG_STM32F4XX_STDPERIPH_DRIVER),y)
SYSTEM_SRC_C_FILES+=$(SYSTEM_PATH)/stm32f4xx_conf.c
endif

SYSTEM_SRC_S_FILES+=$(CMSIS_DEVICE_SUPPORT_PATH)/Source/Templates/gcc_ride7/startup_$(shell echo $(DEVICE_NAME) | tr A-Z a-z).s

# Object files list
SYSTEM_OBJ_C_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${SYSTEM_SRC_C_FILES})
SYSTEM_OBJ_S_FILES=$(patsubst ${AUSBEE_DIR}/%.s,${OUTPUT_PATH}/%.o,${SYSTEM_SRC_S_FILES})
SYSTEM_DEP_C_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.d,${SYSTEM_SRC_C_FILES})

# Add object files to the global obj files list
OBJ_FILES+=$(SYSTEM_OBJ_C_FILES) $(SYSTEM_OBJ_S_FILES)
DEP_FILES+=$(SYSTEM_DEP_C_FILES)

$(LINKER_SCRIPT): $(LINKER_SCRIPT_INPUT) $(CONFIG_DEPS)
	$(call print_gen,System-CM4,$(subst $(OUTPUT_PATH)/,,$@))
	$(HOST_CC) -x c -P -C -DRAM_LENGTH=$(RAM_LENGTH) -DFLASH_LENGTH=$(FLASH_LENGTH) -E $< -o $@

# Build objects
$(SYSTEM_OBJ_S_FILES): ${OUTPUT_PATH}/%.o :${AUSBEE_DIR}/%.s $(TOOLCHAIN_EXTRACTED)
	$(call print_build,System-CM4,$(subst $(AUSBEE_DIR)/System-CM4/,,$<))
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(SYSTEM_INCLUDES) -c $<

$(SYSTEM_OBJ_C_FILES): ${OUTPUT_PATH}/%.o :${AUSBEE_DIR}/%.c $(TOOLCHAIN_EXTRACTED)
	$(call print_build,System-CM4,$(subst $(AUSBEE_DIR)/System-CM4/,,$<))
	@mkdir -p $(dir $@)
	$(HOST_CC) $(HOST_CFLAGS) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<

.PHONY: system-clean
system-clean:
	$(RM_RF) $(SYSTEM_OBJ_C_FILES) $(SYSTEM_OBJ_S_FILES) $(LINKER_SCRIPT)

SYSTEM_LOAD:

-include $(SYSTEM_DEP_C_FILES)
