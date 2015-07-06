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


# If we are not configuring, include the configuration file
noconfig_goals= %-defconfig config menuconfig nconfig xconfig gconfig alldefconfig
clean_dirclean_help_doc_goals= %-clean %-dirclean dirclean clean help doc
ifneq ($(filter $(clean_dirclean_help_doc_goals),$(MAKECMDGOALS)),)

ifneq ("$(wildcard .config)", "")
include .config
endif

else ifeq ($(filter $(noconfig_goals),$(MAKECMDGOALS)),)

ifneq ("$(wildcard .config)", "")
include .config
else #If the configuration file is not found and no config goals is provided, print error
$(error Please run a configuration command (your_board-defconfig, alldefconfig, menuconfig, config, ...) \
 before building your project. Please, have a look in "make help".)
endif

# clean, dirclean ,help ,doc
else
#include .config only if exist for menuconfig (for customs path)
-include .config
endif


######################################################################
# Shell commands
MKDIR_P=mkdir -p
CD=cd
RM_RF=rm -rf
WGET=wget
UNZIP=unzip
TOUCH=touch
ECHO_E=@echo -e
DOXYGEN=doxygen
GIT_CLONE=git clone
ifeq ($(CONFIG_PROGRAMMING_USART),y)
STM32FLASH=stm32flash
else
ifeq ($(CONFIG_PROGRAMMING_STLINK),y)
STM32FLASH=st-flash
endif
endif
ifeq ($(CONFIG_PROGRAMMING_AVRDUDE),y)
AVRDUDE=avrdude
endif


######################################################################
# Path variables
DQUOTE="
# Remove highlighting problem"

INCLUDE_KCONFIG_PATH=$(CURDIR)/include

#Configs
CONFIGS_PATH=$(AUSBEE_DIR)/Configs

# Project output files
OUTPUT_PATH=$(CURDIR)/Output

# A subdir is defined, use it as ouput directory
ifneq ($(origin OUTPUT_SUB_PATH), undefined)
	OUTPUT_PATH=$(CURDIR)/Output/$(OUTPUT_SUB_PATH)
endif
OUTPUT_TARGET_HEX=$(subst $(DQUOTE),,$(OUTPUT_PATH)/$(CONFIG_PROJECT_NAME).hex)
OUTPUT_TARGET_BIN=$(subst $(DQUOTE),,$(OUTPUT_PATH)/$(CONFIG_PROJECT_NAME).bin)
OUTPUT_TARGET_ELF=$(subst $(DQUOTE),,$(OUTPUT_PATH)/$(CONFIG_PROJECT_NAME).elf)

# Toolchain
# Handle AVR special case
ifeq ($(CONFIG_AVR_CORE),y)
CONFIG_TOOLCHAIN_TARGET_NAME=avr
CONFIG_DOWNLOAD_TOOLCHAIN=n
CONFIG_TOOLCHAIN_CUSTOM_BIN_PATH=n
CONFIG_USE_FPU=n
endif

TOOLCHAIN_PATH=$(AUSBEE_DIR)/Toolchain
TOOLCHAIN_BUILD_PATH=$(TOOLCHAIN_PATH)/Build
ifeq ($(CONFIG_DOWNLOAD_TOOLCHAIN),y)
TOOLCHAIN_EXTRACTED_PATH=$(subst $(DQUOTE),,$(TOOLCHAIN_BUILD_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME))
TOOLCHAIN_ARCHIVE_NAME=$(notdir $(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_MIRROR)))
TOOLCHAIN_BIN_PATH=$(TOOLCHAIN_EXTRACTED_PATH)/bin
TOOLCHAIN_EXTRACTED=$(TOOLCHAIN_EXTRACTED_PATH).extracted
else 
ifeq ($(CONFIG_TOOLCHAIN_CUSTOM_BIN_PATH),y)
TOOLCHAIN_BIN_PATH=$(CONFIG_TOOLCHAIN_BIN_PATH)
else
TOOLCHAIN_BIN_PATH=$(dir $(shell which $(CONFIG_TOOLCHAIN_TARGET_NAME)-gcc))
endif
endif

# System
ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
SYSTEM_PATH=$(AUSBEE_DIR)/System-CM4
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
SYSTEM_PATH=$(AUSBEE_DIR)/System-CM3
endif

# OS_PATH
OPERATING_SYSTEMS_PATH=$(AUSBEE_DIR)/Operating_Systems

# Packages
PACKAGES_PATH=$(AUSBEE_DIR)/Packages

# Platforms
PLATFORMS_PATH=$(AUSBEE_DIR)/Platforms

# Project
PROJECT_PATH=$(AUSBEE_DIR)/Project

# Documentation
DOCUMENTATION_PATH=$(AUSBEE_DIR)/Documentation

# Build
BUILD_PATH=$(OUTPUT_PATH)/Build

######################################################################
# Build variables
HOST_AS=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-as)
HOST_AR=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-ar)
HOST_CC=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-gcc)
HOST_CXX=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-g++)
HOST_LD=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-ld)
HOST_OBJCPY=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-objcopy)
HOST_SIZE=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-size)
HOST_STRIP=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-strip)

# RAM and FLASH length for linker script preprocessing
RAM_LENGTH=$(subst $(DQUOTE),,$(CONFIG_RAM_LENGTH)) 
FLASH_LENGTH=$(subst $(DQUOTE),,$(CONFIG_FLASH_LENGTH)) 

# Crystal frequency
CRYSTAL_FREQUENCY=$(subst $(DQUOTE),,$(CONFIG_CRYSTAL_FREQUENCY)) 

# Common flags : Core type
HOST_COMMON_FLAGS=
ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
HOST_COMMON_FLAGS=-mthumb
#HOST_COMMON_FLAGS+=-mcpu=cortex-m4 -fsingle-precision-constant -Wdouble-promotion -mfloat-abi=hard -mfpu=fpv4-sp-d16
HOST_COMMON_FLAGS+=-mcpu=cortex-m4
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
HOST_COMMON_FLAGS=-mthumb
HOST_COMMON_FLAGS+=-mcpu=cortex-m3
endif

#Common flags : FPU
ifeq ($(CONFIG_USE_FPU),y)
#-mfloat-abi=hard : Application Binary Interface type for float process. Use hard.
#-fsingle-precision-constant : do not use double precision implicitly when you declare constant without f (example : 1.2f)
#-Wdouble-promotion : Print warning when implicit conversion from float to double
HOST_COMMON_FLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion
else
ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
HOST_COMMON_FLAGS+=-msoft-float
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
HOST_COMMON_FLAGS+=-msoft-float
endif
endif

include $(AUSBEE_DIR)/config-devices.mk # get DEVICE_NAME variable

HOST_COMMON_FLAGS+=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_COMMON_FLAGS) -D$(DEVICE_NAME))

# CFLAGS and CXXFLAGS
HOST_CFLAGS=$(HOST_COMMON_FLAGS) $(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_CFLAGS))
HOST_CXXFLAGS=$(HOST_COMMON_FLAGS) $(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_CXXFLAGS) )

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
HOST_CFLAGS+=-DUSE_STDPERIPH_DRIVER
HOST_CXXFLAGS+=-DUSE_STDPERIPH_DRIVER
endif
ifeq ($(CONFIG_STM32F4XX_STDPERIPH_DRIVER),y)
HOST_CFLAGS+=-DUSE_STDPERIPH_DRIVER
HOST_CXXFLAGS+=-DUSE_STDPERIPH_DRIVER
endif
ifeq ($(CONFIG_DEBUG),y)
HOST_CFLAGS+=-DDEBUG -DUSART_DEBUG=$(subst $(DQUOTE),,$(CONFIG_USART_DEBUG))
HOST_CXXFLAGS+=-DDEBUG -DUSART_DEBUG=$(subst $(DQUOTE),,$(CONFIG_USART_DEBUG))
endif

HOST_CFLAGS+=-DHSE_VALUE=$(CRYSTAL_FREQUENCY)
HOST_CXXFLAGS+=-DHSE_VALUE=$(CRYSTAL_FREQUENCY)

# LDFLAGS
HOST_LDFLAGS=$(HOST_COMMON_FLAGS) $(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_LDFLAGS)) 

# GCC optimisation
HOST_OPTIMISATION=$(subst $(DQUOTE),,-O$(CONFIG_OPTIMISATION))

######################################################################
# Project configuration

# Conditions for starting to build project
PROJECT_BUILD_PATH=$(BUILD_PATH)/project

# Program device
BAUDRATE_SERIAL_INTERFACE=$(subst $(DQUOTE),,$(CONFIG_BAUDRATE_SERIAL_INTEFACE))
PROGRAM_SERIAL_INTERFACE=$(subst $(DQUOTE),,$(CONFIG_PROGRAM_SERIAL_INTERFACE))
