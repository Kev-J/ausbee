# Path
ARCHIVE_FREERTOS_PATH=$(subst $(DQUOTE),,$(CONFIG_DOWNLOADS_DIR)/FreeRTOSV$(CONFIG_FREERTOS_VERSION_DOWNLOAD).zip)
FREERTOS_TOP_PATH=$(subst $(DQUOTE),,$(FREERTOS_PATH)/FreeRTOSV$(CONFIG_FREERTOS_VERSION_DOWNLOAD))
FREERTOS_SRC_PATH=$(FREERTOS_TOP_PATH)/FreeRTOS/Source
# TODO make it configurable
FREERTOS_SRC_PORT_PATH=$(FREERTOS_SRC_PATH)/portable/GCC/ARM_CM3

#FreeRTOS Includes
FREERTOS_INCLUDES_DIR=-I"$(CURDIR)/FreeRTOS/include"
FREERTOS_INCLUDES_DIR+=-I"$(FREERTOS_SRC_PATH)/include"
FREERTOS_INCLUDES_DIR+=-I"$(FREERTOS_SRC_PORT_PATH)"

#TODO make choice for user to remove unnecessary files
# Source files list
FREERTOS_SRC_FILES=$(FREERTOS_SRC_PATH)/tasks.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/croutine.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/list.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/queue.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/timers.c
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PATH)/portable/MemMang/heap_1.c # TODO make it configurable
FREERTOS_SRC_FILES+=$(FREERTOS_SRC_PORT_PATH)/port.c

# Object files list
FREERTOS_OBJ_FILES=$(FREERTOS_SRC_FILES:.c=.o)

# Add object files to the global object files list
OBJ_FILES+=$(FREERTOS_OBJ_FILES)

# Build objects
$(FREERTOS_OBJ_FILES): %.o :%.c $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(FREERTOS_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

# Make sure that the archive has been extracted
$(FREERTOS_SRC_FILES): $(FREERTOS_TOP_PATH)/.extracted

# Extract files
$(FREERTOS_TOP_PATH)/.extracted:$(ARCHIVE_FREERTOS_PATH)
	$(UNZIP) -d $(FREERTOS_PATH) $<
	$(TOUCH) $@

#TODO ifeq for choosing if FreeRTOS must be downloaded or not
# Download requested files
$(ARCHIVE_FREERTOS_PATH):
	$(MKDIR_P) $(CONFIG_DOWNLOADS_DIR)
	$(WGET) -O $@ $(CONFIG_FREERTOS_URL_DOWNLOAD)

.PHONY: freertos-clean freertos-dirclean
freertos-clean:
	$(RM_RF) $(FREERTOS_OBJ_FILES)

freertos-dirclean:
	$(RM_RF) $(FREERTOS_TOP_PATH)
