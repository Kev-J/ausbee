# Load all AUSBEE makefiles within the Libraries
# These makefiles will add their includes dir in LIBRARIES_INCLUDES_DIR
# and add their object files in LIBRARIES_OBJ_FILES.

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
include $(LIBRARIES_PATH)/STM32F10x_StdPeriph_Driver/stm32f10x_stdperiph_driver.mk
LIBRARIES_CLEAN_GOALS+=stm32f10x_stdperiph_driver-clean
LIBRARIES_DOCUMENTATION_GOALS+=stm32f10x_stdperiph_driver-doc
endif

ifeq ($(CONFIG_STM32F4XX_STDPERIPH_DRIVER),y)
include $(LIBRARIES_PATH)/STM32F4xx_StdPeriph_Driver/stm32f4xx_stdperiph_driver.mk
LIBRARIES_CLEAN_GOALS+=stm32f4xx_stdperiph_driver-clean
LIBRARIES_DOCUMENTATION_GOALS+=stm32f4xx_stdperiph_driver-doc
endif

ifeq ($(CONFIG_LIBAUSBEE),y)
include $(LIBRARIES_PATH)/libausbee/libausbee.mk
LIBRARIES_CLEAN_GOALS+=libausbee-clean
LIBRARIES_DOCUMENTATION_GOALS+=libausbee-doc
endif

libraries-clean: $(LIBRARIES_CLEAN_GOALS)
libraries-doc: $(LIBRARIES_DOCUMENTATION_GOALS)
