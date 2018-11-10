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
	$(ECHO_E) "$(ECHO_ESC)[32mBuild $(ECHO_ESC)[1m$1$(ECHO_ESC)[0m$(ECHO_ESC)[32m file: $(ECHO_ESC)[1m$2$(ECHO_ESC)[0m"
endef
define print_gen
	$(ECHO_E) "$(ECHO_ESC)[34mGenerate $(ECHO_ESC)[1m$1$(ECHO_ESC)[0m$(ECHO_ESC)[34m file:$(ECHO_ESC)[1m $2$(ECHO_ESC)[0m"
endef

######################################################################
# Build target

all: $(OUTPUT_TARGET_BIN) $(OUTPUT_TARGET_HEX) size_after_build
sim: $(OUTPUT_TARGET_SIM)

include $(TOOLCHAIN_PATH)/toolchain.mk
include $(PACKAGES_PATH)/packages.mk
ifneq ($(SYSTEM_PATH),)
include $(SYSTEM_PATH)/system.mk
endif
include $(PLATFORMS_PATH)/platforms.mk
include $(OPERATING_SYSTEMS_PATH)/operating_systems.mk
include $(PROJECTS_PATH)/projects.mk

size_after_build: $(OUTPUT_TARGET_ELF)
	$(TARGET_SIZE) $^

$(OUTPUT_TARGET_HEX): $(OUTPUT_TARGET_ELF)
	$(call print_gen,$(PROJECT_NAME),$(notdir $@))
	$(TARGET_OBJCPY) -O ihex $^ $@

$(OUTPUT_TARGET_BIN): $(OUTPUT_TARGET_ELF)
	$(call print_gen,$(PROJECT_NAME),$(notdir $@))
	$(TARGET_OBJCPY) -O binary $^ $@

ifneq ($(SYSTEM_PATH),)
$(OUTPUT_TARGET_ELF): $(PACKAGES_EXTRACTED) $(TARGET_OBJ_FILES) $(LIB_FILES) $(LINKER_SCRIPT)
	$(call print_gen,$(PROJECT_NAME),$(notdir $@))
	$(MKDIR_P) $(OUTPUT_PATH)
	$(TARGET_CC) -o $@ -T$(LINKER_SCRIPT) $(TARGET_OBJ_FILES) $(TARGET_LDFLAGS) $(GLOBAL_LDFLAGS)
else
$(OUTPUT_TARGET_ELF): $(PACKAGES_EXTRACTED) $(TARGET_OBJ_FILES) $(LIB_FILES)
	$(call print_gen,$(PROJECT_NAME),$(notdir $@))
	$(MKDIR_P) $(OUTPUT_PATH)
	$(TARGET_CC) -o $@ $(TARGET_OBJ_FILES) $(TARGET_LDFLAGS) $(GLOBAL_LDFLAGS)
endif

$(OUTPUT_TARGET_SIM): $(PACKAGES_EXTRACTED) $(SIM_OBJ_FILES)
	$(call print_gen,$(CONFIG_PROJECT_NAME),$(notdir $@))
	$(MKDIR_P) $(OUTPUT_PATH)
	$(SIM_CC) -o $@ $(SIM_OBJ_FILES) $(SIM_LDFLAGS) $(GLOBAL_LDFLAGS)


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
program: $(OUTPUT_TARGET_ELF)
	/usr/bin/openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg -c "program $(<) verify reset"
#program: $(OUTPUT_TARGET_BIN)
	#$(ST_FLASH) --reset write $(<) 0x08000000
endif
ifeq ($(CONFIG_PROGRAMMING_AVRDUDE_WITH_ISP2),y)
program: $(OUTPUT_TARGET_HEX)
	avrdude -p x16a4 -c avrisp2 -U flash:w:$(OUTPUT_TARGET_HEX)
endif
endif

######################################################################
# Debug/Chip info
.PHONY: chip-info debug
chip-info:
ifeq ($(CONFIG_PROGRAMMING_STLINK),y)
	@$(ECHO_E) "$(ECHO_ESC)[107;30mDevice description\033[0m"
	@$(ST_INFO) --descr
	@$(ECHO_E)
	@$(ECHO_E) "$(ECHO_ESC)[107;30mFlash size\033[0m"
	@$(ST_INFO) --flash
	@x=$$($(PRINTF) "%d" `st-info --flash`) ; $(ECHO_E) $$((x/1024))K
	@$(ECHO_E)
	@$(ECHO_E) "$(ECHO_ESC)[107;30mSRAM size\033[0m"
	@$(ST_INFO) --sram
	@x=$$($(PRINTF) "%d" `st-info --sram`) ; $(ECHO_E) $$((x/1024))K
else
	@$(ECHO_E) STLink not configured to be your programmer.
endif

debug: $(TOOLCHAIN_EXTRACTED) $(OUTPUT_TARGET_ELF)
ifeq ($(CONFIG_PROGRAMMING_STLINK),y)
	@$(ECHO_E) "$(ECHO_ESC)[107;30mStarting debugger\033[0m"
	@$(ST_UTIL) & echo $$! > .debug.PID
	@$(SLEEP) 3
	@$(TARGET_GDB) -x $(TOOLCHAIN_DEBUG_CMD_FILE) $(OUTPUT_TARGET_ELF)
	@$(KILL2) `cat .debug.PID` && rm .debug.PID
else
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
	$(RM_RF) $(SIM_OBJ_FILES) $(TARGET_OBJ_FILES) $(SIM_DEP_FILES) $(TARGET_DEP_FILES)

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
	$(ECHO_E) "Programming/Debugging:"
	$(ECHO_E) "  program            - load the output .hex file in your stm32"
	$(ECHO_E) "  chip-info          - display chip informations (only with ST-Link)"
	$(ECHO_E)
	$(ECHO_E) "Cleaning:"
	$(ECHO_E) "  clean              - remove all object files"
	$(ECHO_E) "  dirclean           - reset all the project (/!\\ Remove configuration)"
	$(ECHO_E)
	$(ECHO_E) "Help:"
	$(ECHO_E) "  help               - Display this help"
