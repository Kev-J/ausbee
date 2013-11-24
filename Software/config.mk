# If we are not configuring, include the configuration file
noconfig_goals= %-defconfig config menuconfig nconfig xconfig gconfig alldefconfig
clean_dirclean_goals= %-clean %-dirclean dirclean clean
ifeq ($(filter $(noconfig_goals)$(clean_dirclean_goals),$(MAKECMDGOALS)),)

ifneq ("$(wildcard .config)", "")
include .config
else #If the configuration file is not found and no config goals is provided, print error
$(error Please run an configuration command (your_board-defconfig, alldefconfig, menuconfig, config, ...))
endif

else
#TODO print error when:
# - No device has been provided
# - No core selected
endif


######################################################################
# Shell commands
MKDIR_P=mkdir -p
CD=cd
RM_RF=rm -rf
WGET=wget
UNZIP=unzip
TOUCH=touch
STM32FLASH=stm32flash

######################################################################
# Path variables
DQUOTE="
# Remove highlighting problem"

CONFIGS_PATH=$(CURDIR)/configs
# Project output files
OUTPUT_PATH=$(CURDIR)/output
OUTPUT_TARGET_HEX=$(subst $(DQUOTE),,$(OUTPUT_PATH)/$(CONFIG_PROJECT_NAME).hex)
OUTPUT_TARGET_ELF=$(subst $(DQUOTE),,$(OUTPUT_PATH)/$(CONFIG_PROJECT_NAME).elf)
# Toolchain
TOOLCHAIN_PATH=$(CURDIR)/Toolchain
ifeq ($(CONFIG_DOWNLOAD_TOOLCHAIN),y)
TOOLCHAIN_EXTRACTED_PATH=$(subst $(DQUOTE),,$(TOOLCHAIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME))
TOOLCHAIN_ARCHIVE_NAME=$(notdir $(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_MIRROR)))
TOOLCHAIN_BIN_PATH=$(TOOLCHAIN_EXTRACTED_PATH)/bin
TOOLCHAIN_EXTRACTED=$(TOOLCHAIN_EXTRACTED_PATH).extracted
else
TOOLCHAIN_BIN_PATH=$(CONFIG_TOOLCHAIN_BIN_PATH)
endif

# System
ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
SYSTEM_PATH=$(CURDIR)/System-CM4
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
SYSTEM_PATH=$(CURDIR)/System-CM3
endif
# FreeRTOS
FREERTOS_PATH=$(CURDIR)/FreeRTOS
# Libraries
LIBRARIES_PATH=$(CURDIR)/Libraries
# Project
PROJECT_PATH=$(CURDIR)/Project

######################################################################
# Build variables
HOST_AS=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-as)
HOST_CC=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-gcc)
HOST_CXX=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-g++)
HOST_LD=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-ld)
HOST_OBJCPY=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-objcopy)
HOST_SIZE=$(subst $(DQUOTE),,$(TOOLCHAIN_BIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-size)

ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
HOST_COMMON_FLAGS=-mthumb -mcpu=cortex-m4
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
HOST_COMMON_FLAGS=-mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd
endif

# get DEVICE_NAME variable
include config-devices.mk

HOST_OPTIMISATION=$(subst $(DQUOTE),,-O$(CONFIG_OPTIMISATION))
HOST_CFLAGS=$(HOST_COMMON_FLAGS) $(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_CFLAGS) -D$(DEVICE_NAME))
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
HOST_CFLAGS+=-DUSE_STDPERIPH_DRIVER
endif
ifeq ($(CONFIG_USE_ASSERT_PARAM),y)
HOST_CFLAGS+=-DUSE_ASSERT_PARAM
endif
HOST_LDFLAGS=$(HOST_COMMON_FLAGS) $(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_LDFLAGS))

######################################################################
# Project configuration

# Conditions for starting to build project
PROJECT_BUILD_PATH=$(BUILD_PATH)/project
PROJECT_DEPENDENCIES = $(FREERTOS_TOP_PATH)/.extracted # Need includes files of FreeRTOS

# Program device
BAUDRATE_SERIAL_INTERFACE=$(subst $(DQUOTE),,$(CONFIG_BAUDRATE_SERIAL_INTEFACE))
PROGRAM_SERIAL_INTERFACE=$(subst $(DQUOTE),,$(CONFIG_PROGRAM_SERIAL_INTERFACE))

