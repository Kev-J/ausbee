CMSIS_DEVICE_SUPPORT_PATH=$(SYSTEM_PATH)/CMSIS/CM3/DeviceSupport/ST/STM32F10x
CMSIS_CORE_SUPPORT_PATH=$(SYSTEM_PATH)/CMSIS/CM3/CoreSupport

LINKER_SCRIPT=$(SYSTEM_PATH)/link.ld
LINKER_SCRIPT_INPUT=$(LINKER_SCRIPT).in

SYSTEM_INCLUDES_DIR=-I"$(CMSIS_DEVICE_SUPPORT_PATH)"
SYSTEM_INCLUDES_DIR+=-I"$(CMSIS_CORE_SUPPORT_PATH)"
SYSTEM_INCLUDES_DIR+=-I"$(SYSTEM_PATH)/include"

SYSTEM_SRC_FILES=$(CMSIS_CORE_SUPPORT_PATH)/core_cm3.c
SYSTEM_SRC_FILES+=$(CMSIS_DEVICE_SUPPORT_PATH)/system_stm32f10x.c
#SYSTEM_SRC_FILES+=$(SYSTEM_PATH)/startup.c
SYSTEM_SRC_FILES+=$(SYSTEM_PATH)/syscalls.c
SYSTEM_S_SRC_FILES+=$(CMSIS_DEVICE_SUPPORT_PATH)/startup/gcc_ride7/startup_$(shell echo $(DEVICE_NAME) | tr A-Z a-z).s

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
SYSTEM_SRC_FILES+=$(SYSTEM_PATH)/stm32f10x_conf.c
endif

# Object files list
SYSTEM_OBJ_FILES=$(SYSTEM_SRC_FILES:.c=.o)
SYSTEM_S_OBJ_FILES=$(SYSTEM_S_SRC_FILES:.s=.o)

# Add object files to the global obj files list
OBJ_FILES+=$(SYSTEM_OBJ_FILES) $(SYSTEM_S_OBJ_FILES)

# Force to preprocess linker script
#XXX but tell me if you have a better solution?
$(LINKER_SCRIPT): $(LINKER_SCRIPT_INPUT) force
	$(HOST_CC) -x c -P -C -DRAM_LENGTH=$(RAM_LENGTH) -DFLASH_LENGTH=$(FLASH_LENGTH) -E $< -o $@
force:

# Build objects
$(SYSTEM_OBJ_FILES): %.o :%.c $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(SYSTEM_INCLUDES_DIR) -c $<

$(SYSTEM_S_OBJ_FILES): %.o :%.s $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(SYSTEM_INCLUDES_DIR) -c $<

.PHONY: system-clean
system-clean:
	$(RM_RF) $(SYSTEM_OBJ_FILES) $(SYSTEM_S_OBJ_FILES) $(LINKER_SCRIPT)
