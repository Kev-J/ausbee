# If we are not configuring, include the configuration file
noconfig_goals= %-defconfig config menuconfig nconfig xconfig gconfig alldefconfig
ifeq ($(filter $(noconfig_goals),$(MAKECMDGOALS)),)

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

######################################################################
# Path variables
DQUOTE="
# Remove highlighting problem"

CONFIGS_PATH=$(CURDIR)/configs
# Project output files
OUTPUT_PATH=$(CURDIR)/output
OUTPUT_TARGET_HEX=$(subst $(DQUOTE),,$(OUTPUT_PATH)/$(CONFIG_PROJECT_NAME).hex)
OUTPUT_TARGET_ELF=$(subst $(DQUOTE),,$(OUTPUT_PATH)/$(CONFIG_PROJECT_NAME).elf)
# System
ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
SYSTEM_PATH=$(CURDIR)/System-CM4
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
SYSTEM_PATH=$(CURDIR)/System-CM3
endif
# FreeRTOS
FREERTOS_PATH=$(CURDIR)/FreeRTOS

######################################################################
# Build variables
HOST_CC=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-gcc)
HOST_CXX=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-g++)
HOST_LD=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-ld)
HOST_OBJCPY=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-objcopy)
HOST_SIZE=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_PATH)/$(CONFIG_TOOLCHAIN_TARGET_NAME)-size)

HOST_OPTIMISATION=$(subst $(DQUOTE),,-O$(CONFIG_OPTIMISATION))
HOST_CFLAGS=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_CFLAGS) -D$(CONFIG_DEVICE_NAME))
HOST_LDFLAGS=$(subst $(DQUOTE),,$(CONFIG_TOOLCHAIN_LDFLAGS))

######################################################################
# Project configuration

# Conditions for starting to build project
PROJECT_BUILD_PATH=$(BUILD_PATH)/project
PROJECT_DEPENDENCIES = $(FREERTOS_TOP_PATH)/.extracted # Need includes files of FreeRTOS
