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

TOOLCHAIN_ARCHIVE=$(subst $(DQUOTE),,$(CONFIG_DOWNLOADS_DIR)/$(TOOLCHAIN_ARCHIVE_NAME))

$(TOOLCHAIN_EXTRACTED): $(TOOLCHAIN_ARCHIVE)
	$(MKDIR_P) $(TOOLCHAIN_EXTRACTED_PATH)
	tar xvf $< -C $(TOOLCHAIN_EXTRACTED_PATH) --strip-components=1
	touch $@

$(TOOLCHAIN_ARCHIVE):
	$(MKDIR_P) $(CONFIG_DOWNLOADS_DIR)
	$(WGET) -O $@ $(CONFIG_TOOLCHAIN_MIRROR)

toolchain-dirclean:
	$(RM_RF) $(TOOLCHAIN_EXTRACTED_PATH) $(TOOLCHAIN_EXTRACTED)
