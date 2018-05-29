CFLAGS ?=
CFLAGS += -mcpu=cortex-m0 -mthumb -mabi=aapcs --std=gnu99
CFLAGS += -Wall
CFLAGS += -mfloat-abi=soft

LDFLAGS ?=
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mcpu=cortex-m0 -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)

