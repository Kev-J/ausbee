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

PKG_GENERIC_FID=0

define pkg-generic-handle-source =
PKG_GENERIC_FID:=$(shell echo $$(($(PKG_GENERIC_FID) + 1)))
PKG_GENERIC_$(PKG_GENERIC_FID)_SRC:=$(3)
PKG_GENERIC_$(PKG_GENERIC_FID)_SRC_PATH:=$(2)/$(3)
PKG_GENERIC_$(PKG_GENERIC_FID)_OBJ:=$$(PKG_GENERIC_$(PKG_GENERIC_FID)_SRC:%.$(5)=$(BUILD_PATH)/objs/$(1)/%.$(4).o)
PKG_GENERIC_$(PKG_GENERIC_FID)_DEP:=$$(PKG_GENERIC_$(PKG_GENERIC_FID)_SRC:%.$(5)=$(BUILD_PATH)/objs/$(1)/%.$(4).d)
$(4)_OBJ_FILES+=$$(PKG_GENERIC_$(PKG_GENERIC_FID)_OBJ)
$(4)_DEP_FILES+=$$(PKG_GENERIC_$(PKG_GENERIC_FID)_DEP)

$$(PKG_GENERIC_$(PKG_GENERIC_FID)_OBJ): $$(PKG_GENERIC_$(PKG_GENERIC_FID)_SRC_PATH) $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(call print_build,$(1),$$(subst $(2)/,,$$<))
	$$(MKDIR_P) $$(dir $$@)
	$$($(4)_CC) $$($(4)_CFLAGS) $$(GLOBAL_CFLAGS) $$($(4)_INCLUDES) $$(GLOBAL_OPTIMISATION) -MF"$$(@:.o=.d)" -MG -MM -MP -MT"$$@" "$$<"
	$$($(4)_CC) -o $$@ $$($(4)_CFLAGS) $$(GLOBAL_CFLAGS) $$($(4)_INCLUDES) $$(GLOBAL_OPTIMISATION) -c $$<

-include $$(PKG_GENERIC_$(PKG_GENERIC_FID)_DEP)
endef

define pkg-generic =
$(1)_BUILD_SRC = $(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z)
$(1)_INCLUDES=$$($(1)_INCLUDE_PATH:%=-I"$$($(1)_BUILD_SRC)/%") $$($(1)_LOCAL_INCLUDE_PATH:%=-I"$$($(1)_LOCAL_FILE_PATH)/%")
$(1)_SIM_INCLUDES=$$($(1)_SIM_INCLUDE_PATH:%=-I"$$($(1)_BUILD_SRC)/%") $$($(1)_SIM_LOCAL_INCLUDE_PATH:%=-I"$$($(1)_LOCAL_FILE_PATH)/%")
$(1)_TARGET_INCLUDES=$$($(1)_TARGET_INCLUDE_PATH:%=-I"$$($(1)_BUILD_SRC)/%") $$($(1)_TARGET_LOCAL_INCLUDE_PATH:%=-I"$$($(1)_LOCAL_FILE_PATH)/%")


TARGET_INCLUDES+= $$($(1)_INCLUDES) $$($(1)_TARGET_INCLUDES)
SIM_INCLUDES+= $$($(1)_INCLUDES) $$($(1)_SIM_INCLUDES)

ifeq ($$(CONFIG_$(1)_USE_GIT),y)
PACKAGES_EXTRACTED += $$($(1)_BUILD_SRC)/.cloned
endif
ifeq ($$(CONFIG_$(1)_USE_HTTP),y)
PACKAGES_EXTRACTED += $$($(1)_BUILD_SRC)/.extracted
endif

$$($(1)_BUILD_SRC)/.extracted: $$($(1)_BUILD_SRC)/.downloaded
	$(MKDIR_P) $$($(1)_BUILD_SRC)
	$(call pkg-extract,$(CONFIG_DOWNLOADS_DIR)/$($(1)_ARCHIVE), $$($(1)_BUILD_SRC))
	touch $$@

$$($(1)_BUILD_SRC)/.downloaded:
	$(MKDIR_P) $$($(1)_BUILD_SRC)
	$(call pkg_download,$($(1)_URL),$($(1)_ARCHIVE))
	touch $$@

$$($(1)_BUILD_SRC)/.cloned:
	$(MKDIR_P) $$($(1)_BUILD_SRC)
	$(GIT_CLONE) $$($(1)_GIT_UPSTREAM_URL) $$($(1)_BUILD_SRC)/git
	touch $$@


$(foreach src,$($(1)_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),SIM,c)))
$(foreach src,$($(1)_SIM_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),SIM,c)))
$(foreach src,$($(1)_LOCAL_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),SIM,c)))
$(foreach src,$($(1)_SIM_LOCAL_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),SIM,c)))

$(foreach src,$($(1)_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),TARGET,c)))
$(foreach src,$($(1)_TARGET_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),TARGET,c)))
$(foreach src,$($(1)_LOCAL_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),TARGET,c)))
$(foreach src,$($(1)_TARGET_LOCAL_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),TARGET,c)))

$(foreach src,$($(1)_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),SIM,s)))
$(foreach src,$($(1)_SIM_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),SIM,s)))
$(foreach src,$($(1)_LOCAL_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),SIM,s)))
$(foreach src,$($(1)_SIM_LOCAL_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),SIM,s)))

$(foreach src,$($(1)_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),TARGET,s)))
$(foreach src,$($(1)_TARGET_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z),$(src),TARGET,s)))
$(foreach src,$($(1)_LOCAL_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),TARGET,s)))
$(foreach src,$($(1)_TARGET_LOCAL_S_SRC_FILES),$(eval $(call pkg-generic-handle-source,$(1),$($(1)_LOCAL_FILE_PATH),$(src),TARGET,s)))

endef

define pkg-generic-old =

$(1)_BUILD_PATH = $(BUILD_PATH)/$(shell echo $(1) | tr A-Z a-z)
$(1)_SRC_FILES_BUILD = $$($(1)_SRC_FILES:%=$$($(1)_BUILD_PATH)/%)
$(1)_INCLUDES=$$($(1)_INCLUDE_PATH:%=-I"$$($(1)_BUILD_PATH)/%")
$(1)_SIM_INCLUDES=$$($(1)_SIM_INCLUDE_PATH:%=-I"$$($(1)_BUILD_PATH)/%")
$(1)_TARGET_INCLUDES=$$($(1)_TARGET_INCLUDE_PATH:%=-I"$$($(1)_BUILD_PATH)/%")


# Load dependancies rule
$(1)_DEPENDENCIES_DOWNLOADED=$(foreach dep,$(shell echo $($(1)_DEPENDENCIES) | tr a-z A-Z),$$($(dep)_LOAD))

# Add to packages includes
TARGET_INCLUDES+= $$($(1)_INCLUDES) $$($(1)_TARGET_INCLUDES)
SIM_INCLUDES+= $$($(1)_INCLUDES) $$($(1)_SIM_INCLUDES)


$(1)_TARGET_SRC_FILES_BUILD = $$($(1)_TARGET_SRC_FILES:%=$$($(1)_BUILD_PATH)/%)
$(1)_SIM_SRC_FILES_BUILD = $$($(1)_SIM_SRC_FILES:%=$$($(1)_BUILD_PATH)/%)

$(1)_TARGET_OBJ_FILES=$$($(1)_SRC_FILES:%.c=$$($(1)_BUILD_PATH)/%.$(TARGET_ARCH).o)
$(1)_TARGET_DEP_FILES=$$($(1)_SRC_FILES:%.c=$$($(1)_BUILD_PATH)/%.$(TARGET_ARCH).d)
$(1)_SIM_OBJ_FILES=$$($(1)_SRC_FILES:%.c=$$($(1)_BUILD_PATH)/%.sim.o)
$(1)_SIM_DEP_FILES=$$($(1)_SRC_FILES:%.c=$$($(1)_BUILD_PATH)/%.sim.d)
$(1)_TARGET_OBJ_FILES+=$$($(1)_TARGET_SRC_FILES_BUILD:.c=.$(TARGET_ARCH).o)
$(1)_TARGET_DEP_FILES+=$$($(1)_TARGET_SRC_FILES_BUILD:.c=.$(TARGET_ARCH).d)
$(1)_SIM_OBJ_FILES+=$$($(1)_SIM_SRC_FILES_BUILD:.c=.sim.o)
$(1)_SIM_DEP_FILES+=$$($(1)_SIM_SRC_FILES_BUILD:.c=.sim.d)

# Add to global dependencies
TARGET_OBJ_FILES+=$$($(1)_TARGET_OBJ_FILES)
TARGET_DEP_FILES+=$$($(1)_TARGET_DEP_FILES)
SIM_OBJ_FILES+=$$($(1)_SIM_OBJ_FILES)
SIM_DEP_FILES+=$$($(1)_SIM_DEP_FILES)

PACKAGES_CLEAN_GOALS+=$(1)-clean

$$($(1)_TARGET_OBJ_FILES): %.$(TARGET_ARCH).o: %.c $(TOOLCHAIN_EXTRACTED) $$($(1)_DEPENDENCIES_DOWNLOADED) $(CONFIG_DEPS)
	$(call print_build,$(1),$$(subst $$($(1)_BUILD_PATH)/,,$$<))
	$$(TARGET_CC) $$(TARGET_CFLAGS) $$(GLOBAL_CFLAGS) $$(TARGET_INCLUDES) $$(GLOBAL_OPTIMISATION) -MF"$$(@:.o=.d)" -MG -MM -MP -MT"$$@" "$$<"
	$$(TARGET_CC) -o $$@ $$(TARGET_CFLAGS) $$(GLOBAL_CFLAGS) $$(TARGET_INCLUDES) $$(GLOBAL_OPTIMISATION) -c $$<

$$($(1)_SIM_OBJ_FILES): %.sim.o: %.c $(TOOLCHAIN_EXTRACTED) $$($(1)_DEPENDENCIES_DOWNLOADED) $(CONFIG_DEPS)
	$(call print_build,$(1),$$(subst $$($(1)_BUILD_PATH)/,,$$<))
	$$(SIM_CC) $$(SIM_CFLAGS) $$(GLOBAL_CFLAGS) $$(SIM_INCLUDES) $$(GLOBAL_OPTIMISATION) -MF"$$(@:.o=.d)" -MG -MM -MP -MT"$$@" "$$<"
	$$(SIM_CC) -o $$@ $$(SIM_CFLAGS) $$(GLOBAL_CFLAGS) $$(SIM_INCLUDES) $$(GLOBAL_OPTIMISATION) -c $$<


ifeq ($$(CONFIG_$(1)_USE_GIT),y)
$(1)_LOAD=$$($(1)_BUILD_PATH)/.cloned
$$($(1)_SRC_FILES_BUILD): $$($(1)_BUILD_PATH)/.cloned
# Add to extracted list for dependencies
PACKAGES_EXTRACTED += $$($(1)_BUILD_PATH)/.cloned
else
$(1)_LOAD=$$($(1)_BUILD_PATH)/.extracted
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

-include $$($(1)_DEP_FILES)

endef
