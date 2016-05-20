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

ifeq ($(CONFIG_PLATFORM_AUSBEE_MAIN_BOARD_V0_1),y)
include $(PLATFORMS_PATH)/ausbee_main_board_v0.1/platform.mk
PLATFORM_CLEAN_GOAL+=platform_ausbee_main_board_v0_1-clean
endif
ifeq ($(CONFIG_PLATFORM_STM32F4DISCOVERY),y)
include $(PLATFORMS_PATH)/stm32f4discovery/platform.mk
PLATFORM_CLEAN_GOAL+=platform_stm32f4discovery-clean
endif
ifeq ($(CONFIG_PLATFORM_STM32F7DISCOVERY),y)
include $(PLATFORMS_PATH)/stm32f7discovery/platform.mk
PLATFORM_CLEAN_GOAL+=platform_stm32f7discovery-clean
endif
ifeq ($(CONFIG_PLATFORM_AUSBEE_SERVO_MODULE_V0_1),y)
include $(PLATFORMS_PATH)/ausbee_servo_module_v0.1/platform.mk
PLATFORM_CLEAN_GOAL+=platform_ausbee_servo_module_v0_1-clean
endif


#Generate Kconfig path and include custom platform Makefile
AUSBEE_CUSTOM_PLATFORMS_KCONFIG_PATH=$(AUSBEE_DIR)/Platforms/empty.Kconfig
ifeq ($(CONFIG_CUSTOM_PLATFORMS),y)
CONFIG_CUSTOM_PLATFORMS_PATH:=$(subst $(DQUOTE),,$(CONFIG_CUSTOM_PLATFORMS_PATH))
ifeq ($(CONFIG_CUSTOM_PLATFORMS_REL_PATH), y)
CONFIG_CUSTOM_PLATFORMS_PATH:=$(CURDIR)/$(CONFIG_CUSTOM_PLATFORMS_PATH)
endif
ifneq ("$(wildcard $(CONFIG_CUSTOM_PLATFORMS_PATH)/platforms.mk)", "")
include $(CONFIG_CUSTOM_PLATFORMS_PATH)/platforms.mk
endif
ifneq ("$(wildcard $(CONFIG_CUSTOM_PLATFORMS_PATH)/Kconfig)", "")
AUSBEE_CUSTOM_PLATFORMS_KCONFIG_PATH=$(CONFIG_CUSTOM_PLATFORMS_PATH)/Kconfig
endif
endif

#export custom platforms Kconfig path
export AUSBEE_CUSTOM_PLATFORMS_KCONFIG_PATH

.PHONY: platforms-clean
platforms-clean: $(PLATFORM_CLEAN_GOAL)
