# param 1 : url
# param 2 : local archive name
define pkg_download =
	$(MKDIR_P) $(CONFIG_DOWNLOADS_DIR)
ifeq (,$(wildcard $(subst $(DQUOTE),,$(CONFIG_DOWNLOADS_DIR)/$2)))
	$(WGET) -O $(subst $(DQUOTE),,$(CONFIG_DOWNLOADS_DIR)/$2) $1
endif
endef
