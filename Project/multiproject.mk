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

PROJECT_OUTPUT_PATH=$(OUTPUT_PATH)/Project

#Generate object list from project source file list
PROJECT_TAGRET_OBJ_FILES=$(patsubst %.c,${PROJECT_OUTPUT_PATH}/%.$(TARGET_ARCH).o,${PROJECT_SRC_FILES})
PROJECT_TAGRET_DEP_FILES=$(patsubst %.c,${PROJECT_OUTPUT_PATH}/%.$(TARGET_ARCH).d,${PROJECT_SRC_FILES})
PROJECT_SIM_OBJ_FILES=$(patsubst %.c,${PROJECT_OUTPUT_PATH}/%.sim.o,${PROJECT_SRC_FILES})
PROJECT_SIM_DEP_FILES=$(patsubst %.c,${PROJECT_OUTPUT_PATH}/%.sim.d,${PROJECT_SRC_FILES})

#Add project object file to global object file list
TARGET_OBJ_FILES+=$(PROJECT_TARGET_OBJ_FILES)
TARGET_DEP_FILES+=$(PROJECT_TARGET_DEP_FILES)
SIM_OBJ_FILES+=$(PROJECT_SIM_OBJ_FILES)
SIM_DEP_FILES+=$(PROJECT_SIM_DEP_FILES)

#Generate special include list
PROJECT_INCLUDES = $(PLATFORM_INCLUDES)
PROJECT_INCLUDES += $(OPERATING_SYSTEMS_INCLUDES)
PROJECT_INCLUDES += $(PACKAGES_INCLUDES)
PROJECT_INCLUDES += $(SYSTEM_INCLUDES)

#Generate project object files
$(PROJECT_TARGET_OBJ_FILES): ${PROJECT_OUTPUT_PATH}/%.$(TARGET_ARCH).o: %.c $(PACKAGES_EXTRACTED) $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(call print_build,$(CONFIG_PROJECT_NAME),$<)
	@mkdir -p $(dir $@)
	$(TARGET_CC) $(TARGET_CFLAGS) $(GLOBAL_CFLAGS) $(PROJECT_INCLUDES) $(GLOBAL_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	$(TARGET_CC) -o $@ $(TARGET_CFLAGS) $(GLOBAL_CFLAGS) $(PROJECT_INCLUDES) $(GLOBAL_OPTIMISATION) -c $<

$(PROJECT_SIM_OBJ_FILES): ${PROJECT_OUTPUT_PATH}/%.sim.o: %.c $(PACKAGES_EXTRACTED) $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(call print_build,$(CONFIG_PROJECT_NAME),$<)
	@mkdir -p $(dir $@)
	$(SIM_CC) $(SIM_CFLAGS) $(GLOBAL_CFLAGS) $(PROJECT_INCLUDES) $(GLOBAL_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	$(SIM_CC) -o $@ $(SIM_CFLAGS) $(GLOBAL_CFLAGS) $(PROJECT_INCLUDES) $(GLOBAL_OPTIMISATION) -c $<

-include $(PROJECT_DEP_FILES)
