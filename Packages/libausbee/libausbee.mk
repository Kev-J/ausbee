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

LIBAUSBEE_VERSION = 1.2
LIBAUSBEE_URL = https://github.com/Kev-J/libausbee/archive/$(LIBAUSBEE_VERSION).tar.gz
LIBAUSBEE_ARCHIVE =$(LIBAUSBEE_FILE_PATH).tar.gz
LIBAUSBEE_GIT_UPSTREAM_URL = git@github.com:Kev-J/libausbee.git

# File path
ifeq ($(CONFIG_LIBAUSBEE_USE_GIT),y)
LIBAUSBEE_FILE_PATH=git
else
LIBAUSBEE_FILE_PATH=libausbee-$(LIBAUSBEE_VERSION)
endif

# Include files
LIBAUSBEE_INCLUDE_PATH=$(LIBAUSBEE_FILE_PATH)/include/

ifeq ($(CONFIG_LIBAUSBEE_DRIVERS),y)
LIBAUSBEE_SRC_FILES=$(LIBAUSBEE_FILE_PATH)/src/drivers/lidar.c \
	$(LIBAUSBEE_FILE_PATH)/src/drivers/ax12.c \
	$(LIBAUSBEE_FILE_PATH)/src/drivers/encoder.c \
	$(LIBAUSBEE_FILE_PATH)/src/drivers/l298_driver.c \
	$(LIBAUSBEE_FILE_PATH)/src/drivers/servo.c \
	$(LIBAUSBEE_FILE_PATH)/src/drivers/gp2.c
endif

ifeq ($(CONFIG_LIBAUSBEE_CONTROL_SYSTEM),y)
LIBAUSBEE_SRC_FILES+=$(LIBAUSBEE_FILE_PATH)/src/control_system/control_system_manager.c \
	$(LIBAUSBEE_FILE_PATH)/src/control_system/controller/pid.c \
	$(LIBAUSBEE_FILE_PATH)/src/control_system/filters/diff.c \
	$(LIBAUSBEE_FILE_PATH)/src/control_system/filters/quadramp.c
endif

$(eval $(call pkg-generic,LIBAUSBEE))
