###########################################################
# Makefile for configuring and building an AUSBEE project #
#                                                         #
# Author: Kevin JOLY <joly.kevin25@gmail.com>             #
#                                                         #
# EIRBOT ENSEIRB-MATMECA Robotics club 2013               #
#                                                         #
###########################################################

include config.mk

include packages/config.mk

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
all: $(PACKAGES_TARGET) $(OUTPUT_TARGET_HEX)

include project/project.mk
include packages/packages.mk

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
# Clean, and other stuffs
.PHONY: clean
clean: project-clean

.PHONY: dirclean
dirclean:
	$(RM_RF) .config .config.old $(KCONFIG_BUILD_PATH) $(BUILD_PATH)
