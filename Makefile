# Makefile for managing projects
#
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

AUSBEE_DIR=.

include $(AUSBEE_DIR)/config.mk

PROJECT_TEMPLATE_MAKEFILE = $(AUSBEE_DIR)/$(PROJECTS_PATH)/Makefile.template

create-project:
ifndef PROJECT_NAME
	$(error Variable PROJECT_NAME is not set. make create-project PROJECT_NAME=YOUR_PROJECT_NAME)
else
	@$(ECHO_E) Creating project $(PROJECT_NAME).
	@$(MKDIR_P) $(PROJECTS_PATH)/$(PROJECT_NAME)
	@$(CP) $(PROJECT_TEMPLATE_MAKEFILE) $(AUSBEE_DIR)/$(PROJECT_PATH)/$(PROJECT_NAME)/Makefile

endif
