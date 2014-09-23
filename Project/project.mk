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

PROJECT_INCLUDES = $(PLATFORM_INCLUDES)
PROJECT_INCLUDES += $(PACKAGES_INCLUDES)
PROJECT_INCLUDES += $(SYSTEM_INCLUDES)

# Additional source files might have been defined in a subproject config file
PROJECT_SRC_FILES+=$(wildcard $(PROJECT_PATH)/$(PROJECT_SRC_DIR)/*.c)
PROJECT_OBJ_FILES=$(patsubst %.c,%.o,${PROJECT_SRC_FILES})

# Add project obj files to the global obj files list
OBJ_FILES+=$(PROJECT_OBJ_FILES)

$(PROJECT_OBJ_FILES): %.o: %.c $(PACKAGES_EXTRACTED) $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES) $(HOST_OPTIMISATION) -c $<
