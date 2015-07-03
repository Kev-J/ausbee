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

PLATFORM_AUSBEE_MAIN_BOARD_V0_1_PATH=$(PLATFORMS_PATH)/ausbee_servo_module_v0.1

PLATFORMS_INCLUDES_DIR=-I"$(PLATFORM_AUSBEE_MAIN_BOARD_V0_1_PATH)"

PLATFORM_SRC_FILES+=$(PLATFORM_AUSBEE_MAIN_BOARD_V0_1_PATH)/platform.c
PLATFORM_OBJ_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.o,${PLATFORM_SRC_FILES})
PLATFORM_DEP_FILES=$(patsubst ${AUSBEE_DIR}/%.c,${OUTPUT_PATH}/%.d,${PLATFORM_SRC_FILES})

OBJ_FILES+=$(PLATFORM_OBJ_FILES)
DEP_FILES+=$(PLATFORM_DEP_FILES)

$(PLATFORM_OBJ_FILES): $(OUTPUT_PATH)/%.o :$(AUSBEE_DIR)/%.c $(TOOLCHAIN_EXTRACTED) $(CONFIG_DEPS)
	@mkdir -p $(dir $@)
	$(HOST_CC) $(HOST_CFLAGS) $(LIBRARIES_INCLUDES_DIR) $(SYSTEM_INCLUDES_DIR) $(HOST_OPTIMISATION) -MF"$(@:.o=.d)" -MG -MM -MP -MT"$@" "$<"
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(LIBRARIES_INCLUDES_DIR) $(SYSTEM_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

.PHONY:platform_ausbee_servo_module_v0_1-clean
platform_ausbee_servo_module_v0_1-clean:
	$(RM_RF) $(OBJ_FILES)

-include $(PLATFORM_DEP_FILES)
