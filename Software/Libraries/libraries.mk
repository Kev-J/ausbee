# Load all AUSBEE makefiles within the Libraries
# These makefiles will add their includes dir in LIBRARIES_INCLUDES_DIR
# and add their object files in LIBRARIES_OBJ_FILES.
# TODO what about create .a archives?

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
include $(LIBRARIES_PATH)/STM32F10x_StdPeriph_Driver/stm32f10x_stdperiph_driver.mk
LIBRARIES_CLEAR_GOALS+=stm32f10x_stdperiph_driver-clean
endif

ifeq ($(CONFIG_LIBAUSBEE),y)
include $(LIBRARIES_PATH)/libausbee/libausbee.mk
LIBRARIES_CLEAR_GOALS+=libausbee-clean
endif

libraries-clean: $(LIBRARIES_CLEAR_GOALS)
