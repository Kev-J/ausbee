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
# You should have received a copy of the GNU General Public License# along with AUSBEE.  If not, see <http://www.gnu.org/licenses/>.

# Path
CONFIG_FREERTOS_USE_HTTP=y
FREERTOS_VERSION=$(subst $(DQUOTE),,$(CONFIG_FREERTOS_VERSION_DOWNLOAD))
FREERTOS_URL=$(CONFIG_FREERTOS_URL_DOWNLOAD)
FREERTOS_ARCHIVE=FreeRTOS_V$(FREERTOS_VERSION).zip
FREERTOS_LOCAL_FILE_PATH=$(OPERATING_SYSTEMS_PATH)/FreeRTOS

FREERTOS_INCLUDE_PATH=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/include
FREERTOS_LOCAL_INCLUDE_PATH=include

ifeq ($(CONFIG_ARM_CORE_CORTEX_M4),y)
FREERTOS_TARGET_INCLUDE_PATH=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM4F
FREERTOS_TARGET_SRC_FILES=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
else ifeq ($(CONFIG_ARM_CORE_CORTEX_M3),y)
FREERTOS_TARGET_INCLUDE_PATH=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM3
FREERTOS_TARGET_SRC_FILES=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
endif 

FREERTOS_SIM_LOCAL_SRC_FILES=port/originalPosix/port.c
FREERTOS_SIM_LOCAL_INCLUDE_PATH=port/originalPosix
SIM_LDFLAGS+=-lpthread

FREERTOS_SRC_FILES= FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/tasks.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/croutine.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/list.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/queue.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/timers.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/event_groups.c
FREERTOS_SRC_FILES+=FreeRTOSV$(FREERTOS_VERSION)/FreeRTOS/Source/portable/MemMang/heap_1.c # TODO make it configurable

$(eval $(call pkg-generic,FREERTOS))
