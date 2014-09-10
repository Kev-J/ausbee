# Choose source files directory
PROJECT_SRC_DIR?=src

# Get subproject configuration file if it exists
# The main purpose of this sub config file is to provide a way to have
# source files in subdirectories and still be able to add them in
# PROJECT_SRC_FILES
SUBPROJECT_CONFIG_FILE=$(PROJECT_PATH)/$(PROJECT_SRC_DIR)/subproject.mk
ifneq ("$(wildcard $(SUBPROJECT_CONFIG_FILE))", "")
include $(SUBPROJECT_CONFIG_FILE)
endif

PROJECT_INCLUDES_DIR = $(FREERTOS_INCLUDES_DIR) # Add FREERTOS include files
PROJECT_INCLUDES_DIR += $(PLATFORMS_INCLUDES_DIR)
PROJECT_INCLUDES_DIR += $(LIBRARIES_INCLUDES_DIR)
PROJECT_INCLUDES_DIR += $(SYSTEM_INCLUDES_DIR)

# Additional source files might have been defined in a subproject config file
PROJECT_SRC_FILES+=$(wildcard $(PROJECT_PATH)/$(PROJECT_SRC_DIR)/*.c)
PROJECT_OBJ_FILES=$(patsubst %.c,%.o,${PROJECT_SRC_FILES})

# Add project obj files to the global obj files list
OBJ_FILES+=$(PROJECT_OBJ_FILES)

$(OUTPUT_TARGET_HEX): $(OUTPUT_TARGET_ELF)
	$(HOST_OBJCPY) -O ihex $^ $@
	$(HOST_SIZE) $@

$(OUTPUT_TARGET_BIN): $(OUTPUT_TARGET_ELF)
	$(HOST_OBJCPY) -O binary $^ $@

$(OUTPUT_TARGET_ELF): 	$(OBJ_FILES) $(LINKER_SCRIPT)
	$(MKDIR_P) $(OUTPUT_PATH)
	$(HOST_CC) -o $@ -T$(LINKER_SCRIPT) $(OBJ_FILES) $(HOST_LDFLAGS) 

$(PROJECT_OBJ_FILES): %.o: %.c $(PROJECT_DEPENDENCIES) $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

.PHONY:project-clean
project-clean:
	$(RM_RF) $(PROJECT_OBJ_FILES) $(OUTPUT_TARGET_HEX) $(OUTPUT_TARGET_ELF) $(OUTPUT_TARGET_BIN)
