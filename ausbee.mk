# Makefile for configuring and building an AUSBEE project
#
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

AUSBEE_DIR?=.

include $(AUSBEE_DIR)/config.mk

######################################################################
# KCONFIG variables
KCONFIG_SOURCES_PATH=$(AUSBEE_DIR)/kconfig-frontends
KCONFIG_BUILD_PATH=$(KCONFIG_SOURCES_PATH)/build
CONF=$(KCONFIG_BUILD_PATH)/frontends/conf/conf
MCONF=$(KCONFIG_BUILD_PATH)/frontends/mconf/mconf
NCONF=$(KCONFIG_BUILD_PATH)/frontends/nconf/nconf
QCONF=$(KCONFIG_BUILD_PATH)/frontends/qconf/qconf
GCONF=$(KCONFIG_BUILD_PATH)/frontends/gconf/gconf
CONFIG_DEPS=.config
export AUSBEE_DIR

######################################################################
# Print functions
define print_build
	$(ECHO_E) "\e[32mBuild \e[1m$1\e[0m\e[32m file: \e[1m$2\e[0m"
endef
define print_gen
	$(ECHO_E) "\e[34mGenerate \e[1m$1\e[0m\e[34m file:\e[1m $2\e[0m"
endef

######################################################################
# Build target
all: $(OUTPUT_TARGET_BIN) $(OUTPUT_TARGET_HEX) size_after_build

include $(TOOLCHAIN_PATH)/toolchain.mk
ifneq ($(SYSTEM_PATH),)
include $(SYSTEM_PATH)/system.mk
endif
include $(PACKAGES_PATH)/packages.mk
include $(PLATFORMS_PATH)/platforms.mk
include $(OPERATING_SYSTEMS_PATH)/operating_systems.mk

include $(PROJECTS_PATH)/projects.mk

size_after_build: $(OUTPUT_TARGET_ELF)
	$(HOST_SIZE) $^

$(OUTPUT_TARGET_HEX): $(OUTPUT_TARGET_ELF)
	$(call print_gen,$(PROJECT_NAME),$(notdir $@))
	$(HOST_OBJCPY) -O ihex $^ $@

$(OUTPUT_TARGET_BIN): $(OUTPUT_TARGET_ELF)
	$(call print_gen,$(PROJECT_NAME),$(notdir $@))
	$(HOST_OBJCPY) -O binary $^ $@

$(OUTPUT_TARGET_ELF): $(OBJ_FILES) $(LIB_FILES) $(LINKER_SCRIPT)
	$(call print_gen,$(PROJECT_NAME),$(notdir $@))
	$(MKDIR_P) $(OUTPUT_PATH)
	$(HOST_CC) -o $@ -T$(LINKER_SCRIPT) $(OBJ_FILES) $(HOST_LDFLAGS)

######################################################################
# Configuration tool

# Load board configuration
.PHONY: %-defconfig
%-defconfig: $(CONF) 
	$(CONF) --defconfig=$(CONFIGS_PATH)/$@ $(AUSBEE_DIR)/Kconfig
	mkdir -p include/
	mkdir -p include/config include/generated
	$(CONF) --silentoldconfig $(AUSBEE_DIR)/Kconfig

# Load default configuration
.PHONY: alldefconfig
alldefconfig: $(CONF)
	$(CONF) --alldefconfig $(AUSBEE_DIR)/Kconfig
	mkdir -p include/
	mkdir -p include/config include/generated
	$(CONF) --silentoldconfig $(AUSBEE_DIR)/Kconfig

.PHONY: config
config: $(CONF)
	$(CONF) $(AUSBEE_DIR)/Kconfig
	mkdir -p include/
	mkdir -p include/config include/generated
	$(CONF) --silentoldconfig $(AUSBEE_DIR)/Kconfig

.PHONY: menuconfig
menuconfig: $(MCONF)
	$(MCONF) $(AUSBEE_DIR)/Kconfig
	mkdir -p include/
	mkdir -p include/config include/generated
	$(CONF) --silentoldconfig $(AUSBEE_DIR)/Kconfig

.PHONY: nconfig
nconfig: $(NCONF)
	$(NCONF) $(AUSBEE_DIR)/Kconfig
	mkdir -p include/
	mkdir -p include/config include/generated
	$(CONF) --silentoldconfig $(AUSBEE_DIR)/Kconfig

.PHONY: xconfig
xconfig: $(QCONF)
	$(QCONF) $(AUSBEE_DIR)/Kconfig
	mkdir -p include/
	mkdir -p include/config include/generated
	$(CONF) --silentoldconfig $(AUSBEE_DIR)/Kconfig

.PHONY: gconfig
gconfig: $(GCONF)
	$(GCONF) $(AUSBEE_DIR)/Kconfig
	mkdir -p include/
	mkdir -p include/config include/generated
	$(CONF) --silentoldconfig $(AUSBEE_DIR)/Kconfig

# KCONFIG build
$(MCONF): $(CONF)
$(NCONF): $(CONF)
$(QCONF): $(CONF)
$(GCONF): $(CONF)

$(CONF): $(KCONFIG_BUILD_PATH)/Makefile
	$(MAKE) -C $(KCONFIG_BUILD_PATH)

$(KCONFIG_BUILD_PATH)/Makefile:
	$(MKDIR_P) $(KCONFIG_BUILD_PATH)
	$(CD) $(KCONFIG_BUILD_PATH) ; ../configure

######################################################################
# Program and run
.PHONY: program
ifeq ($(CONFIG_PROGRAMMING_USART),y)
program: $(OUTPUT_TARGET_HEX)
	$(STM32FLASH) -w $(<) -b $(BAUDRATE_SERIAL_INTERFACE) -v -g 0x0 $(PROGRAM_SERIAL_INTERFACE)
else
ifeq ($(CONFIG_PROGRAMMING_STLINK),y)
program: $(OUTPUT_TARGET_BIN)
	$(STM32FLASH) --reset write $(<) 0x08000000
endif
endif


######################################################################
# Clean, and other stuffs
.PHONY: dirclean clean
dirclean: toolchain-dirclean operating_systems-dirclean clean
	$(RM_RF) .config .config.old $(KCONFIG_BUILD_PATH) $(BUILD_PATH)

CLEAN_GOALS=packages-clean operating_systems-clean
ifneq ($(SYSTEM_PATH),)
CLEAN_GOALS+=system-clean
endif

CLEAN_GOALS=

.PHONY: $(CLEAN_GOALS)
clean: $(CLEAN_GOALS)
	$(RM_RF) $(OBJ_FILES) $(DEP_FILES)

######################################################################
# Help
.PHONY: help
help:
	$(ECHO_E) "                ####################"
	$(ECHO_E) "                # AUSBEE by EIRBOT #"
	$(ECHO_E) "                ####################"
	$(ECHO_E)
	$(ECHO_E) "Authors: Please, have a look to file's headers"
	$(ECHO_E)
	$(ECHO_E) "For any bugs, requests, or patch:"
	$(ECHO_E) "https://github.com/Kev-J/ausbee"
	$(ECHO_E) "Maintainer: Kevin JOLY <joly.kevin25@gmail.com>"
	$(ECHO_E)
	$(ECHO_E) "This tool enable the user to build a complete STM32 binary file."
	$(ECHO_E) "Have a look to the user manual for further informations: \"make doc\"."
	$(ECHO_E) "You will need pdflatex. The output document will be provided in Documentation" #TODO fix the output
	$(ECHO_E)
	$(ECHO_E) "  all                - build your project (only after configuring)."
	$(ECHO_E)
	$(ECHO_E) "Configuration:"
	$(ECHO_E) "  BOARD-defconfig    - load the configuration file for your BOARD"
	$(ECHO_E) "  alldefconfig       - load the default configuration"
	$(ECHO_E) "  config             - open the config menu in console"
	$(ECHO_E) "  menuconfig         - open the config menu in ncurses mode"
	$(ECHO_E) "  nconfig            - open the config menu in ncurses mode (bis)"
	$(ECHO_E) "  xconfig            - open the config menu in GUI mode (Qt)"
	$(ECHO_E) "  gconfig            - open the config menu in GUI mode (GTK)"
	$(ECHO_E)
	$(ECHO_E) "Programming:"
	$(ECHO_E) "  program            - load the output .hex file in your stm32"
	$(ECHO_E)
	$(ECHO_E) "Cleaning:"
	$(ECHO_E) "  clean              - remove all object files"
	$(ECHO_E) "  dirclean           - reset all the project (/!\\ Remove configuration)"
	$(ECHO_E)
	$(ECHO_E) "Help:"
	$(ECHO_E) "  help               - Display this help"
