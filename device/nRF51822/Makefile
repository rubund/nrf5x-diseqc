MAKEFILE_NAME := $(MAKEFILE_LIST)

SDK_PATH := /usr/lib/nordic/nrf5-sdk/11
TEMPLATE_PATH = /usr/lib/nordic/nrf5-mdk-gcc/default
LINKER_SCRIPT=nrf51_xxaa.ld
DEVFAMILY=NRF51
DUT ?= 0
LED0_GPIO := 18
UART_TX_PIN := 9

ifeq ($(DUT), 1)
	MAINPROG := ../../src/dut.c
else
	MAINPROG := ../../src/tester.c
endif

DEVKITID ?= 480202020

include ../common.mk

CFLAGS ?=
CFLAGS += -DNRF51

ASMFLAGS ?=
ASMFLAGS += -DNRF51

C_SOURCE_FILES += \
../../src/shared.c \
$(MAINPROG) \
$(abspath $(TEMPLATE_PATH)/system_nrf51.c) \

ASM_SOURCE_FILES  = $(abspath $(TEMPLATE_PATH)/gcc_startup_nrf51.S)

include ../common-m0.mk


include ../common-bottom.mk


