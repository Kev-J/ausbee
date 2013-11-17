$(FREERTOS_DONE):$(FREERTOS_PATH)/.extracted
	$(TOUCH) $@

# Extract files
$(FREERTOS_PATH)/.extracted:$(ARCHIVE_FREERTOS_PATH)
	$(UNZIP) -d $(BUILD_PATH) $<
	$(TOUCH) $@

#TODO ifeq for choosing if FreeRTOS must be downloaded or not
# Download requested files
$(ARCHIVE_FREERTOS_PATH):
	$(MKDIR_P) $(CONFIG_DOWNLOADS_DIR)
	$(WGET) -O $@ $(CONFIG_FREERTOS_URL_DOWNLOAD)
