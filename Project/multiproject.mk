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
PROJECT_OBJ_FILES=$(patsubst %.c,${PROJECT_OUTPUT_PATH}/%.o,${PROJECT_SRC_FILES})

#Add project object file to global object file list
OBJ_FILES+=$(PROJECT_OBJ_FILES)

#Generate special include list
PROJECT_INCLUDES = $(PLATFORM_INCLUDES)
PROJECT_INCLUDES += $(OPERATING_SYSTEMS_INCLUDES)
PROJECT_INCLUDES += $(PACKAGES_INCLUDES)
PROJECT_INCLUDES += $(SYSTEM_INCLUDES)

#Generate project object files
$(PROJECT_OBJ_FILES): ${PROJECT_OUTPUT_PATH}/%.o: %.c $(PACKAGES_EXTRACTED) $(TOOLCHAIN_EXTRACTED)
	@mkdir -p $(dir $@)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES) $(HOST_OPTIMISATION) -c $<
