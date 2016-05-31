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

# Load all AUSBEE makefiles within the Libraries
# These makefiles will add their includes dir in LIBRARIES_INCLUDES_DIR
# and add their object files in LIBRARIES_OBJ_FILES.

include $(PACKAGES_PATH)/pkg-download.mk
include $(PACKAGES_PATH)/pkg-generic.mk
include $(PACKAGES_PATH)/pkg-extract.mk

ifeq ($(CONFIG_STM32L0XX_HAL_DRIVER),y)
include $(PACKAGES_PATH)/stm32l0xx_hal_driver/stm32l0xx_hal_driver.mk
endif

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
include $(PACKAGES_PATH)/stm32f10x_stdperiph_driver/stm32f10x_stdperiph_driver.mk
endif

ifeq ($(CONFIG_STM32F4XX_STDPERIPH_DRIVER),y)
include $(PACKAGES_PATH)/stm32f4xx_stdperiph_driver/stm32f4xx_stdperiph_driver.mk
endif

ifeq ($(CONFIG_STM32F7XX_HAL_DRIVER),y)
include $(PACKAGES_PATH)/stm32f7xx_hal_driver/stm32f7xx_hal_driver.mk
endif

ifeq ($(CONFIG_LIBAUSBEE),y)
include $(PACKAGES_PATH)/libausbee/libausbee.mk
endif

ifeq ($(CONFIG_STM32_TOUCHSENSING_LIBRARY),y)
include $(PACKAGES_PATH)/stm32_touchsensing_library/stm32_touchsensing_library.mk
endif

ifeq ($(CONFIG_STM32_USB_DEVICE_LIBRARY),y)
include $(PACKAGES_PATH)/stm32_usb_device_library/stm32_usb_device_library.mk
endif

#Generate Kconfig path and include custom platform Makefile
AUSBEE_CUSTOM_PACKAGES_KCONFIG_PATH=$(AUSBEE_DIR)/Packages/empty.Kconfig
ifeq ($(CONFIG_CUSTOM_PACKAGES),y)
CONFIG_CUSTOM_PACKAGES_PATH:=$(subst $(DQUOTE),,$(CONFIG_CUSTOM_PACKAGES_PATH))
ifeq ($(CONFIG_CUSTOM_PACKAGES_REL_PATH), y)
CONFIG_CUSTOM_PACKAGES_PATH:=$(CURDIR)/$(CONFIG_CUSTOM_PACKAGES_PATH)
endif
ifneq ("$(wildcard $(CONFIG_CUSTOM_PACKAGES_PATH)/packages.mk)", "")
include $(CONFIG_CUSTOM_PACKAGES_PATH)/packages.mk
endif
ifneq ("$(wildcard $(CONFIG_CUSTOM_PACKAGES_PATH)/Kconfig)", "")
AUSBEE_CUSTOM_PACKAGES_KCONFIG_PATH=$(CONFIG_CUSTOM_PACKAGES_PATH)/Kconfig
endif
AUSBEE_CUSTOM_PACKAGES_PATH=$(CONFIG_CUSTOM_PACKAGES_PATH)
endif

#export custom pacakges Kconfig path
export AUSBEE_CUSTOM_PACKAGES_KCONFIG_PATH
export AUSBEE_CUSTOM_PACKAGES_PATH

