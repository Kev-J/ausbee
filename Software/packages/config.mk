include packages/libausbee/config.mk
include packages/FreeRTOS/config.mk

# Mandatory packages
PACKAGES_TARGET += $(FREERTOS_DONE)
PACKAGES_TARGET += $(LIBAUSBEE_DONE) #TODO make it not mandatory
