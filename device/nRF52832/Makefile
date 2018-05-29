MAKEFILE_NAME := $(MAKEFILE_LIST)

SDK_PATH := /usr/lib/nordic/nrf5-sdk/11
TEMPLATE_PATH = /usr/lib/nordic/nrf5-mdk-gcc/default
LINKER_SCRIPT=nrf52_xxaa.ld
DEVFAMILY=NRF52
DUT ?= 0
LED0_GPIO := 17
UART_TX_PIN := 6

ifeq ($(DUT), 1)
	MAINPROG := ../../src/dut.c
else
	MAINPROG := ../../src/tester.c
endif

DEVKITID ?= 682684386

include ../common.mk

CFLAGS ?=
CFLAGS += -DNRF52
CFLAGS += -DHAS_UARTE
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

ASMFLAGS ?=
ASMFLAGS += -DNRF52

LDFLAGS ?=
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

C_SOURCE_FILES += \
../../src/shared.c \
$(MAINPROG) \
$(abspath $(TEMPLATE_PATH)/system_nrf52.c) \

ASM_SOURCE_FILES  = $(abspath $(TEMPLATE_PATH)/gcc_startup_nrf52.S)

include ../common-m4.mk


include ../common-bottom.mk


