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
PROJECT_INCLUDES += $(OPERATING_SYSTEMS_INCLUDES)
PROJECT_INCLUDES += $(PACKAGES_INCLUDES)
PROJECT_INCLUDES += $(SYSTEM_INCLUDES)

# Additional source files might have been defined in a subproject config file
PROJECT_SRC_FILES+=$(wildcard $(PROJECT_PATH)/$(PROJECT_SRC_DIR)/*.c)
PROJECT_OBJ_FILES=$(patsubst %.c,%.o,${PROJECT_SRC_FILES})
PROJECT_DEP_FILES=$(patsubst %.c,%.d,${PROJECT_SRC_FILES})

# Add project obj files to the global obj files list
OBJ_FILES+=$(PROJECT_OBJ_FILES)

$(PROJECT_OBJ_FILES): %.o: %.c $(PACKAGES_EXTRACTED) $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES) $(HOST_OPTIMISATION) -c $<

$(PROJECT_DEP_FILES): %.d: %.c $(PACKAGES_EXTRACTED) $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(PROJECT_INCLUDES) $(HOST_OPTIMISATION) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.c=.o)" "$<"

-include $(PROJECT_DEP_FILES)
