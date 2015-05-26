# Set the source path of this platform
PLATFORM_AUSBEE_MAIN_BOARD_V0_1_PATH=$(PLATFORMS_PATH)/ausbee_main_board_v0.1

# Includes of this platform
PLATFORM_INCLUDES=-I"$(PLATFORM_AUSBEE_MAIN_BOARD_V0_1_PATH)"

# Search the source file and generate the object list
PLATFORM_SRC_FILES+=$(PLATFORM_AUSBEE_MAIN_BOARD_V0_1_PATH)/platform.c
PLATFORM_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${PLATFORM_SRC_FILES})

#Add the object file list to the global object list
OBJ_FILES+=$(PLATFORM_OBJ_FILES)

$(PLATFORM_OBJ_FILES): $(OUTPUT_PATH)/%.o :$(AUSBEE_DIR)/%.c $(TOOLCHAIN_EXTRACTED)
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(STM32F4XX_STDPERIPH_DRIVER_INCLUDES) $(SYSTEM_INCLUDES) $(HOST_OPTIMISATION) -c $<
