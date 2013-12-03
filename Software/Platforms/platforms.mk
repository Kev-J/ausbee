ifeq ($(CONFIG_PLATFORM_AUSBEE_MAIN_BOARD_V0.1),y)
include $(PLATFORMS_PATH)/ausbee_main_board_v0.1/platform.mk
PLATFORM_CLEAN_GOAL+=platform_ausbee_main_board_v0_1-clean
endif

.PHONY: platforms-clean
platforms-clean: $(PLATFORM_CLEAN_GOAL)
