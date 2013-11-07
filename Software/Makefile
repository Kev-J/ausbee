###########################################################
# Makefile for configuring and building an AUSBEE project #
#                                                         #
# Author: Kevin JOLY <joly.kevin25@gmail.com>             #
#                                                         #
# EIRBOT ENSEIRB-MATMECA Robotics club 2013               #
#                                                         #
###########################################################

# If we are not configuring, include the configuration file
noconfig_goals= %-defconfig config menuconfig nconfig xconfig gconfig alldefconfig clean dirclean
ifeq ($(filter $(noconfig_goals),$(MAKECMDGOALS)),)
include .config
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
CONFIGS_PATH=$(CURDIR)/configs
BUILD_PATH=$(CURDIR)/build

######################################################################
# Filename variables
DQUOTE="
# Remove highlighting problem"
ARCHIVE_FREERTOS=$(subst $(DQUOTE),,$(CONFIG_DOWNLOADS_DIR)/FreeRTOSV$(CONFIG_FREERTOS_VERSION_DOWNLOAD).zip)


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
all:$(FREERTOS_PATH)/.extracted

# Extract files
$(FREERTOS_PATH)/.extracted:$(ARCHIVE_FREERTOS)
	$(UNZIP) -d $(BUILD_PATH) $<
	$(TOUCH) $@

# Download requested files
$(ARCHIVE_FREERTOS):
	$(MKDIR_P) $(CONFIG_DOWNLOADS_DIR)
	$(WGET) -O $@ $(CONFIG_FREERTOS_URL_DOWNLOAD)

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
clean:

.PHONY: dirclean
dirclean:
	$(RM_RF) .config .config.old $(KCONFIG_BUILD_PATH) $(BUILD_PATH)
