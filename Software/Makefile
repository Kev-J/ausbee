###########################################################
# Makefile for configuring and building an AUSBEE project #
#                                                         #
# Author: Kevin JOLY <joly.kevin25@gmail.com>             #
#                                                         #
# EIRBOT ENSEIRB-MATMECA Robotics club 2013               #
#                                                         #
###########################################################

include config.mk

######################################################################
# KCONFIG variables
KCONFIG_SOURCES_PATH=$(CURDIR)/kconfig-frontends
KCONFIG_BUILD_PATH=$(KCONFIG_SOURCES_PATH)/build
CONF=$(KCONFIG_BUILD_PATH)/frontends/conf/conf
MCONF=$(KCONFIG_BUILD_PATH)/frontends/mconf/mconf
NCONF=$(KCONFIG_BUILD_PATH)/frontends/nconf/nconf
QCONF=$(KCONFIG_BUILD_PATH)/frontends/qconf/qconf
GCONF=$(KCONFIG_BUILD_PATH)/frontends/gconf/gconf

######################################################################
# Build target
all: $(OUTPUT_TARGET_HEX)

include $(TOOLCHAIN_PATH)/toolchain.mk
ifneq ($(SYSTEM_PATH),)
include $(SYSTEM_PATH)/system.mk
endif
include $(LIBRARIES_PATH)/libraries.mk
include $(OPERATING_SYSTEMS_PATH)/operating_systems.mk
include $(PLATFORMS_PATH)/platforms.mk
include $(PROJECT_PATH)/project.mk
######################################################################
# Configuration tool

# Load board configuration
#TODO make something like %-defconfig
.PHONY: main_board_v1-defconfig
main_board_v1-defconfig: $(CONF) 
	$(CONF) --defconfig=$(CONFIGS_PATH)/main_board_v1.config Kconfig

# Load default configuration
.PHONY: alldefconfig
alldefconfig: $(CONF)
	$(CONF) --alldefconfig Kconfig

.PHONY: config
config: $(CONF)
	$(CONF) Kconfig

.PHONY: menuconfig
menuconfig: $(MCONF)
	$(MCONF) Kconfig

.PHONY: nconfig
nconfig: $(NCONF)
	$(NCONF) Kconfig

.PHONY: xconfig
xconfig: $(QCONF)
	$(QCONF) Kconfig

.PHONY: gconfig
gconfig: $(GCONF)
	$(GCONF) Kconfig

# KCONFIG build
$(MCONF): $(CONF)
$(NCONF): $(CONF)
$(QCONF): $(CONF)
$(GCONF): $(CONF)

$(CONF): $(KCONFIG_BUILD_PATH)/Makefile
	$(MAKE) -C $(KCONFIG_BUILD_PATH)

$(KCONFIG_BUILD_PATH)/Makefile:
	$(MKDIR_P) $(KCONFIG_BUILD_PATH)
	$(CD) $(KCONFIG_BUILD_PATH) ; $(KCONFIG_SOURCES_PATH)/configure

######################################################################
# Program and run
.PHONY: program
program: $(OUTPUT_TARGET_HEX)
	$(STM32FLASH) -w $(<) -b $(BAUDRATE_SERIAL_INTERFACE) -v -g 0x0 $(PROGRAM_SERIAL_INTERFACE)


######################################################################
# Clean, and other stuffs
.PHONY: dirclean clean
dirclean: toolchain-dirclean operating_systems-dirclean clean
	$(RM_RF) .config .config.old $(KCONFIG_BUILD_PATH) $(BUILD_PATH)

ifneq ($(SYSTEM_PATH),)
clean: libraries-clean system-clean project-clean operating_systems-clean
else
clean: libraries-clean project-clean operating_systems-clean
endif

######################################################################
# Documentation
.PHONY: doc
doc:
	$(CD) $(DOCUMENTATION_PATH)/STM32F10x_StdPeriph_Driver ; \
	$(DOXYGEN) $(DOCUMENTATION_PATH)/STM32F10x_StdPeriph_Driver/Doxyfile
	$(CD) $(DOCUMENTATION_PATH)/STM32F4xx_StdPeriph_Driver ; \
	$(DOXYGEN) $(DOCUMENTATION_PATH)/STM32F4xx_StdPeriph_Driver/Doxyfile

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
	$(ECHO_E) "You will need pdflatex. The output documentwill be provided in Documentation" #TODO fix the output
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
	$(ECHO_E) "Documentation:"
	$(ECHO_E) "  doc                - generate manuals and doxygen documentation in the \"Documentation folder\""
	$(ECHO_E)
	$(ECHO_E) "Help:"
	$(ECHO_E) "  help               - Display this help"
