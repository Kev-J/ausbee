ifeq ($(CONFIG_PLATFORM_AUSBEE_MAIN_BOARD_V0.1),y)
include $(PLATFORMS_PATH)/ausbee_main_board_v0.1/platform.mk
PLATFORM_CLEAN_GOAL+=platform_ausbee_main_board_v0_1-clean
endif
ifeq ($(CONFIG_PLATFORM_STM32F4DISCOVERY),y)
include $(PLATFORMS_PATH)/stm32f4discovery/platform.mk
PLATFORM_CLEAN_GOAL+=platform_stm32f4discovery-clean
endif
ifeq ($(CONFIG_PLATFORM_AUSBEE_SERVO_MODULE_V0.1),y)
include $(PLATFORMS_PATH)/ausbee_servo_module_v0.1/platform.mk
PLATFORM_CLEAN_GOAL+=platform_ausbee_servo_module_v0_1-clean
endif

.PHONY: platforms-clean
platforms-clean: $(PLATFORM_CLEAN_GOAL)
