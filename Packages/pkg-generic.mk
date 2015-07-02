# This file is part of AUSBEE.
#
# Copyright (C) 2015 AUSBEE Developers <ausbee@googlegroups.com>
#
# AUSBEE is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# AUSBEE is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with AUSBEE.  If not, see <http://www.gnu.org/licenses/>.

define pkg-generic =

# Generate includes
$(1)_INCLUDES=$$($(1)_INCLUDE_PATH:%=-I"$$($(1)_BUILD_PATH)/%")

# Get dependencies includes
$(1)_DEPENDENCIES_INCLUDES=$(foreach inc,$(shell echo $($(1)_DEPENDENCIES:%=%_INCLUDES) | tr a-z A-Z),$$($(inc)))

# Add to packages includes
PACKAGES_INCLUDES+=$$($(1)_INCLUDES)

$(1)_BUILD_PATH = $(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z)
$(1)_SRC_FILES_BUILD = $$($(1)_SRC_FILES:%=$$($(1)_BUILD_PATH)/%)
$(1)_OBJ_FILES+=$$($(1)_SRC_FILES_BUILD:.c=.o)

# Add to global dependencies
OBJ_FILES+=$$($(1)_OBJ_FILES)

PACKAGES_CLEAN_GOALS+=$(1)-clean

$$($(1)_OBJ_FILES): %.o: %.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(HOST_CC) -o $$@ $(HOST_CFLAGS) $$($(1)_INCLUDES) $$($(1)_DEPENDENCIES_INCLUDES) $(HOST_OPTIMISATION) -c $$<

ifeq ($$(CONFIG_$(1)_USE_GIT),y)
$$($(1)_SRC_FILES_BUILD): $$($(1)_BUILD_PATH)/.cloned
# Add to extracted list for dependencies
PACKAGES_EXTRACTED += $$($(1)_BUILD_PATH)/.cloned
else
$$($(1)_SRC_FILES_BUILD): $$($(1)_BUILD_PATH)/.extracted
# Add to extracted list for dependencies
PACKAGES_EXTRACTED += $$($(1)_BUILD_PATH)/.extracted
endif

$$($(1)_BUILD_PATH)/.extracted: $$($(1)_BUILD_PATH)/.downloaded
	$(MKDIR_P) $$($(1)_BUILD_PATH)
	$(call pkg-extract,$(CONFIG_DOWNLOADS_DIR)/$($(1)_ARCHIVE), $$($(1)_BUILD_PATH))
	touch $$@

$$($(1)_BUILD_PATH)/.downloaded:
	$(MKDIR_P) $$($(1)_BUILD_PATH)
	$(call pkg_download,$($(1)_URL),$($(1)_ARCHIVE))
	touch $$@

$$($(1)_BUILD_PATH)/.cloned:
	$(MKDIR_P) $$($(1)_BUILD_PATH)
	$(GIT_CLONE) $$($(1)_GIT_UPSTREAM_URL) $$($(1)_BUILD_PATH)/git
	touch $$@
.PHONY: $(1)-clean

$(1)-clean:
	rm -rf $$($(1)_BUILD_PATH)/.downloaded $$($(1)_BUILD_PATH)/.extracted $$($(1)_BUILD_PATH)/.cloned
	rm -rf $$($(1)_OBJ_FILES)

endef
