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

# Set the source path of this platform
PLATFORM_AUSBEE_MAIN_BOARD_V0_1_LOCAL_FILE_PATH=$(PLATFORMS_PATH)/ausbee_main_board_v0.1
PLATFORM_AUSBEE_MAIN_BOARD_V0_1_LOCAL_INCLUDE_PATH=.
PLATFORM_AUSBEE_MAIN_BOARD_V0_1_SRC_FILES=platform.c

$(eval $(call pkg-generic,PLATFORM_AUSBEE_MAIN_BOARD_V0_1))
