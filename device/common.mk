

MK := mkdir
RM := rm -rf

OUTPUT_FILENAME := firmware
GNU_PREFIX := arm-none-eabi
GNU_INSTALL_ROOT := /usr

MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) ) 

# Toolchain commands
CC              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc'
AS              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as'
AR              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar' -r
LD              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld'
NM              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm'
OBJDUMP         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump'
OBJCOPY         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy'
SIZE            := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size'

#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))

C_SOURCE_FILES ?=
C_SOURCE_FILES += \
$(abspath $(SDK_PATH)/components/drivers_nrf/delay/nrf_delay.c) \

INC_PATHS  ?= 
INC_PATHS  += -I$(abspath .)
INC_PATHS  += -I$(abspath ../../src/)
INC_PATHS  += -I$(abspath $(TEMPLATE_PATH))
INC_PATHS  += -I$(abspath $(SDK_PATH)/components/toolchain/CMSIS/Include)
INC_PATHS  += -I$(abspath $(SDK_PATH)/components/drivers_nrf/delay)
INC_PATHS  += -I$(abspath $(SDK_PATH)/components/drivers_nrf/hal)

ASMFLAGS ?=
ASMFLAGS += -x assembler-with-cpp

OBJECT_DIRECTORY ?= _build
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = $(OBJECT_DIRECTORY)

BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )
