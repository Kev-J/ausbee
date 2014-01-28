STM32F10X_STDPERIPH_DRIVER_PATH=$(LIBRARIES_PATH)/STM32F10x_StdPeriph_Driver
STM32F10X_STDPERIPH_DRIVER_SRC_PATH=$(STM32F10X_STDPERIPH_DRIVER_PATH)/src

# Include files
STM32F10X_STDPERIPH_DRIVER_INC_PATH=-I"$(STM32F10X_STDPERIPH_DRIVER_PATH)/inc"

# Add the include directory to the libraries include dir
LIBRARIES_INCLUDES_DIR+=$(STM32F10X_STDPERIPH_DRIVER_INC_PATH)

# Source files
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_CAN),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_can.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_RCC),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_rcc.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_GPIO),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_gpio.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_TIM),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_tim.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_USART),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/stm32f10x_usart.c
endif
ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER_MISC),y)
STM32F10X_STDPERIPH_DRIVER_SRC_FILES+=$(STM32F10X_STDPERIPH_DRIVER_SRC_PATH)/misc.c
endif
#TODO add others

# Object files list
STM32F10X_STDPERIPH_DRIVER_OBJ_FILES=$(STM32F10X_STDPERIPH_DRIVER_SRC_FILES:.c=.o)

# Add the object files to the global object files list
OBJ_FILES+=$(STM32F10X_STDPERIPH_DRIVER_OBJ_FILES)

# Build objects
$(STM32F10X_STDPERIPH_DRIVER_OBJ_FILES): %.o :%.c $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(STM32F10X_STDPERIPH_DRIVER_INC_PATH) $(SYSTEM_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

.PHONY:stm32f10x_stdperiph_driver-clean stm32f10x_stdperiph_driver-doc

stm32f10x_stdperiph_driver-clean:
	$(RM_RF) $(STM32F10X_STDPERIPH_DRIVER_OBJ_FILES)

stm32f10x_stdperiph_driver-doc:
	$(CD) $(DOCUMENTATION_PATH)/STM32F10x_StdPeriph_Driver ; \
	$(DOXYGEN) $(DOCUMENTATION_PATH)/STM32F10x_StdPeriph_Driver/Doxyfile
