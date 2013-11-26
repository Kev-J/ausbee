ifeq ($(CONFIG_OS_USE_FREERTOS),y)
include $(OPERATING_SYSTEMS_PATH)/FreeRTOS/freertos.mk
OPERATING_SYSTEMS_CLEAN_GOALS+=freertos-clean
OPERATING_SYSTEMS_DIRCLEAN_GOALS+=freertos-dirclean
endif

operating_systems-clean: $(OPERATING_SYSTEMS_CLEAN_GOALS)
operating_systems-dirclean: $(OPERATING_SYSTEMS_DIRCLEAN_GOALS)
