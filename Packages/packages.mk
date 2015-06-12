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

# Load all AUSBEE makefiles within the Libraries
# These makefiles will add their includes dir in LIBRARIES_INCLUDES_DIR
# and add their object files in LIBRARIES_OBJ_FILES.

include $(PACKAGES_PATH)/pkg-download.mk
include $(PACKAGES_PATH)/pkg-generic.mk
include $(PACKAGES_PATH)/pkg-extract.mk

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
include $(PACKAGES_PATH)/stm32f10x_stdperiph_driver/stm32f10x_stdperiph_driver.mk
endif

ifeq ($(CONFIG_STM32F4XX_STDPERIPH_DRIVER),y)
include $(PACKAGES_PATH)/stm32f4xx_stdperiph_driver/stm32f4xx_stdperiph_driver.mk
endif

ifeq ($(CONFIG_LIBAUSBEE),y)
include $(PACKAGES_PATH)/libausbee/libausbee.mk
endif
