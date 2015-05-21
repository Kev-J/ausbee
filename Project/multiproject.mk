#Generate object list from project source file list
PROJECT_OBJ_FILES=$(patsubst %.c,%.o,${PROJECT_SRC_FILES})

#Add project object file to global object file list
OBJ_FILES+=$(PROJECT_OBJ_FILES)

#Generate special include list
PROJECT_INCLUDES = $(PLATFORM_INCLUDES)
PROJECT_INCLUDES += $(OPERATING_SYSTEMS_INCLUDES)
PROJECT_INCLUDES += $(PACKAGES_INCLUDES)
PROJECT_INCLUDES += $(SYSTEM_INCLUDES)

#Generate project object files
$(PROJECT_OBJ_FILES): %.o: %.c $(PACKAGES_EXTRACTED) $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES) $(HOST_OPTIMISATION) -c $<
