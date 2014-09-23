#param 1 : archive path
#param 2 : destination directory
define pkg-extract =

ifeq ($(suffix $(1)),.gz)
	$(CD) $(2); \
	tar xvf $(1)
else ifeq ($(suffix $(1)),.zip)
	$(CD) $(2); \
	unzip -u $(1)
endif

endef
