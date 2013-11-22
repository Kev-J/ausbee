DEVICE_SUPPORT_PATH=$(CURDIR)/project/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CORE_SUPPORT_PATH=$(CURDIR)/project/CMSIS/CM3/CoreSupport

PROJECT_INCLUDES_DIR = -I"$(DEVICE_SUPPORT_PATH)"
PROJECT_INCLUDES_DIR += -I"$(CORE_SUPPORT_PATH)"
PROJECT_INCLUDES_DIR += -I"$(FREERTOS_PATH)/FreeRTOS/Source/include/"
PROJECT_INCLUDES_DIR += -I"$(FREERTOS_PORT_PATH)"
PROJECT_INCLUDES_DIR += -I"$(CURDIR)/project/src"

LINKER_SCRIPT=$(CURDIR)/project/link.ld


PROJECT_SRC=$(wildcard $(CURDIR)/project/src/*.cpp)

FREERTOS_SRC=$(wildcard $(FREERTOS_PATH)/FreeRTOS/Source/*.c)
FREERTOS_SRC+=$(wildcard $(FREERTOS_PORT_PATH)/*.c)
FREERTOS_SRC+=$(FREERTOS_PATH)/FreeRTOS/Source/portable/MemMang/heap_1.c

PROJECT_OBJ=$(PROJECT_SRC:.cpp=.cpp.o)
FREERTOS_OBJ=$(FREERTOS_SRC:.c=.c.o)

$(OUTPUT_TARGET_HEX): $(OUTPUT_TARGET_ELF)
	$(HOST_OBJCPY) -O ihex $^ $@
	$(HOST_SIZE) $@

$(OUTPUT_TARGET_ELF): 	$(PROJECT_OBJ) \
			$(CURDIR)/project/startup.o \
			$(CURDIR)/project/syscalls.o \
			$(DEVICE_SUPPORT_PATH)/system_stm32f10x.o \
			$(CORE_SUPPORT_PATH)/core_cm3.o \
			$(FREERTOS_OBJ)
	$(MKDIR_P) $(OUTPUT_TARGET_BIN_PATH)
	$(HOST_CXX) -o $@ $^ $(HOST_LDFLAGS)

# System related. Do not optimise
$(CORE_SUPPORT_PATH)/core_cm3.o: $(CORE_SUPPORT_PATH)/core_cm3.c
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES_DIR) -c $<

$(DEVICE_SUPPORT_PATH)/system_stm32f10x.o: $(DEVICE_SUPPORT_PATH)/system_stm32f10x.c
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES_DIR) -c $<

$(CURDIR)/project/startup.o: project/startup.c
	$(HOST_CC) -o $@ $(HOST_CFLAGS) -I"$(DEVICE_SUPPORT_PATH)" -I"$(CORE_SUPPORT_PATH)" -c $<

$(CURDIR)/project/syscalls.o: project/syscalls.c
	$(HOST_CC) -o $@ $(HOST_CFLAGS) -I"$(DEVICE_SUPPORT_PATH)" -I"$(CORE_SUPPORT_PATH)" -c $<

%.cpp.o: %.cpp $(PROJECT_DEPENDENCIES)
	$(HOST_CXX) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

%.c.o: %.c $(PROJECT_DEPENDENCIES)
	$(HOST_CC) -o $@ $(HOST_CFLAGS) $(PROJECT_INCLUDES_DIR) $(HOST_OPTIMISATION) -c $<

project-clean:
	$(RM_RF) $(PROJECT_OBJ) $(FREERTOS_OBJ) $(CURDIR)/project/startup.o $(DEVICE_SUPPORT_PATH)/system_stm32f10x.o $(CORE_SUPPORT_PATH)/core_cm3.o $(DEVICE_SUPPORT_PATH)/system_stm32f10x.o $(OUTPUT_TARGET_HEX) $(OUTPUT_TARGET_ELF)
