LIBAUSBEE_PATH=$(LIBRARIES_PATH)/libausbee
LIBAUSBEE_SRC_PATH=$(LIBAUSBEE_PATH)/src

# Include files
LIBAUSBEE_INC_PATH=-I"$(LIBAUSBEE_PATH)/include"

# Add the include directory to the libraries include dir
LIBRARIES_INCLUDES_DIR+=$(LIBAUSBEE_INC_PATH)

# Add source files
ifeq ($(CONFIG_LIBAUSBEE_LIDAR),y)
LIBAUSBEE_SRC_FILES+=$(LIBAUSBEE_SRC_PATH)/lidar/piccolo-lidar.cpp
endif

# Object files list
LIBAUSBEE_OBJ_FILES=$(LIBAUSBEE_SRC_FILES:.cpp=.o)

# Add the object files to the libraries object files
LIBRARIES_OBJ_FILES+=$(LIBAUSBEE_OBJ_FILES)

# Build objects
$(LIBAUSBEE_OBJ_FILES): %.o :%.cpp $(TOOLCHAIN_EXTRACTED)
	$(HOST_CXX) -o $@ $(HOST_CFLAGS) $(LIBAUSBEE_INC_PATH) $(SYSTEM_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

.PHONY:libausbee-clean
libausbee-clean:
	$(RM_RF) $(LIBRARIES_OBJ_FILES)
