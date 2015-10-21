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

SYSTEM_CM3_LOCAL_FILE_PATH=$(SYSTEM_PATH)
SYSTEM_CM3_LOCAL_INCLUDE_PATH=include CMSIS/CM3/DeviceSupport/ST/STM32F10x CMSIS/CM3/CoreSupport

SYSTEM_CM3_TARGET_LOCAL_SRC_FILES=syscalls.c CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c CMSIS/CM3/CoreSupport/core_cm3.c

SYSTEM_CM3_TARGET_LOCAL_S_SRC_FILES=CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_$(shell echo $(DEVICE_NAME) | tr A-Z a-z).s

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
SYSTEM_CM4_TARGET_LOCAL_SRC_FILES=stm32f4xx_conf.c
endif


$(eval $(call pkg-generic,SYSTEM_CM4))

LINKER_SCRIPT=$(OUTPUT_PATH)/link.ld
LINKER_SCRIPT_INPUT=$(SYSTEM_PATH)/link.ld.in

$(LINKER_SCRIPT): $(LINKER_SCRIPT_INPUT) $(CONFIG_DEPS) $(TOOLCHAIN_EXTRACTED) 
	$(call print_gen,System-CM4,$(subst $(OUTPUT_PATH)/,,$@))
	$(TARGET_CC) -x c -P -C -DRAM_LENGTH=$(RAM_LENGTH) -DFLASH_LENGTH=$(FLASH_LENGTH) -E $< -o $@
