MAKEFILE_NAME := $(MAKEFILE_LIST)

SDK_PATH := /usr/lib/nordic/nrf5-sdk/11
TEMPLATE_PATH = /usr/lib/nordic/nrf5-mdk-gcc/default
LINKER_SCRIPT=nrf52840_xxaa.ld
DEVFAMILY=NRF52
DUT ?= 0
LED0_GPIO := 13
UART_TX_PIN := 6
UART_RTS_PIN := 5
UART_CTS_PIN := 7

ifeq ($(DUT), 1)
	MAINPROG := ../../src/dut.c
else
	MAINPROG := ../../src/tester.c
endif

DEVKITID ?= 683957460

include ../common.mk

CFLAGS ?=
CFLAGS += -DNRF52840_XXAA
CFLAGS += -DHAS_UARTE
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

ASMFLAGS ?=
ASMFLAGS += -DNRF52840_XXAA

LDFLAGS ?=
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

C_SOURCE_FILES += \
../../src/shared.c \
$(MAINPROG) \
$(abspath $(TEMPLATE_PATH)/system_nrf52840.c) \

ASM_SOURCE_FILES  = $(abspath $(TEMPLATE_PATH)/gcc_startup_nrf52840.S)

include ../common-m4.mk


include ../common-bottom.mk


