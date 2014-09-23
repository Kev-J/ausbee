define pkg-generic =

# Generate includes
$(1)_INCLUDES=$$($(1)_INCLUDE_PATH:%=-I"$$($(1)_BUILD_PATH)/%")

# Get dependencies includes
$(1)_DEPENDENCIES_INCLUDES=$(foreach inc,$(shell echo $($(1)_DEPENDENCIES:%=%_INCLUDES) | tr a-z A-Z),$$($(inc)))

# Add to packages includes
PACKAGES_INCLUDES+=$$($(1)_INCLUDES)

# Add to extracted list for dependencies
PACKAGES_EXTRACTED += $$($(1)_BUILD_PATH)/.extracted

$(1)_BUILD_PATH = $(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z)
$(1)_SRC_FILES_BUILD = $$($(1)_SRC_FILES:%=$$($(1)_BUILD_PATH)/%)
$(1)_OBJ_FILES+=$$($(1)_SRC_FILES_BUILD:.c=.o)

# Add to global dependencies
OBJ_FILES+=$$($(1)_OBJ_FILES)

PACKAGES_CLEAN_GOALS+=$(1)-clean

$$($(1)_OBJ_FILES): %.o: %.c $(TOOLCHAIN_EXTRACTED)
	$(HOST_CC) -o $$@ $(HOST_CFLAGS) $$($(1)_INCLUDES) $$($(1)_DEPENDENCIES_INCLUDES) $(HOST_OPTIMISATION) -c $$<

$$($(1)_SRC_FILES_BUILD): $$($(1)_BUILD_PATH)/.extracted

$$($(1)_BUILD_PATH)/.extracted: $$($(1)_BUILD_PATH)/.downloaded
	$(MKDIR_P) $$($(1)_BUILD_PATH)
	$(call pkg-extract,$(CONFIG_DOWNLOADS_DIR)/$($(1)_ARCHIVE), $$($(1)_BUILD_PATH))
	touch $$@

$$($(1)_BUILD_PATH)/.downloaded:
	$(MKDIR_P) $$($(1)_BUILD_PATH)
	$(call pkg_download,$($(1)_URL),$($(1)_ARCHIVE))
	touch $$@

.PHONY: $(1)-clean

$(1)-clean:
	rm -rf $$($(1)_BUILD_PATH)/.downloaded $$($(1)_BUILD_PATH)/.extracted
	rm -rf $$($(1)_OBJ_FILES)

endef
