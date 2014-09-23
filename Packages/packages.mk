# Load all AUSBEE makefiles within the Libraries
# These makefiles will add their includes dir in LIBRARIES_INCLUDES_DIR
# and add their object files in LIBRARIES_OBJ_FILES.

include $(PACKAGES_PATH)/pkg-download.mk
include $(PACKAGES_PATH)/pkg-generic.mk
include $(PACKAGES_PATH)/pkg-extract.mk

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
include $(PACKAGES_PATH)/stm32f10x_stdperiph_driver/stm32f10x_stdperiph_driver.mk
endif

ifeq ($(CONFIG_STM32F4XX_STDPERIPH_DRIVER),y)
include $(PACKAGES_PATH)/stm32f4xx_stdperiph_driver/stm32f4xx_stdperiph_driver.mk
endif

ifeq ($(CONFIG_LIBAUSBEE),y)
include $(PACKAGES_PATH)/libausbee/libausbee.mk
endif
