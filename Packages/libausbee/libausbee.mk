LIBAUSBEE_VERSION = 1.2
LIBAUSBEE_URL = https://github.com/Kev-J/libausbee/archive/$(LIBAUSBEE_VERSION).tar.gz
LIBAUSBEE_ARCHIVE =libausbee-$(LIBAUSBEE_VERSION).tar.gz

ifeq ($(CONFIG_STM32F4XX_STDPERIPH_DRIVER),y)
LIBAUSBEE_DEPENDENCIES=stm32f4xx_stdperiph_driver system
endif

ifeq ($(CONFIG_STM32F10X_STDPERIPH_DRIVER),y)
LIBAUSBEE_DEPENDENCIES=stm32f10x_stdperiph_driver system
endif

# Include files
LIBAUSBEE_INCLUDE_PATH=libausbee-$(LIBAUSBEE_VERSION)/include/

ifeq ($(CONFIG_LIBAUSBEE_DRIVERS),y)
LIBAUSBEE_SRC_FILES=libausbee-$(LIBAUSBEE_VERSION)/src/drivers/lidar.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/drivers/ax12.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/drivers/encoder.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/drivers/l298_driver.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/drivers/servo.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/drivers/gp2.c
endif

ifeq ($(CONFIG_LIBAUSBEE_CONTROL_SYSTEM),y)
LIBAUSBEE_SRC_FILES+=libausbee-$(LIBAUSBEE_VERSION)/src/control_system/control_system_manager.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/control_system/controller/pid.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/control_system/filters/diff.c \
	libausbee-$(LIBAUSBEE_VERSION)/src/control_system/filters/quadramp.c
endif

$(eval $(call pkg-generic,LIBAUSBEE))
