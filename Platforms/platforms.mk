ifeq ($(CONFIG_PLATFORM_AUSBEE_MAIN_BOARD_V0_1),y)
include $(PLATFORMS_PATH)/ausbee_main_board_v0.1/platform.mk
PLATFORM_CLEAN_GOAL+=platform_ausbee_main_board_v0_1-clean
endif
ifeq ($(CONFIG_PLATFORM_STM32F4DISCOVERY),y)
include $(PLATFORMS_PATH)/stm32f4discovery/platform.mk
PLATFORM_CLEAN_GOAL+=platform_stm32f4discovery-clean
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
