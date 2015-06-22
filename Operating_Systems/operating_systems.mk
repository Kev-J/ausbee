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

ifeq ($(CONFIG_OS_USE_FREERTOS),y)
include $(OPERATING_SYSTEMS_PATH)/FreeRTOS/freertos.mk
OPERATING_SYSTEMS_CLEAN_GOALS+=freertos-clean
OPERATING_SYSTEMS_DIRCLEAN_GOALS+=freertos-dirclean
endif

operating_systems-clean: $(OPERATING_SYSTEMS_CLEAN_GOALS)
operating_systems-dirclean: $(OPERATING_SYSTEMS_DIRCLEAN_GOALS)
