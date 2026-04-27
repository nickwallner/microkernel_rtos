TARGET = realtime_scheduler

### Build Variables ###
# 0 = no debug, 1 = debug
DEBUG := 0

### Build File Path ###
BUILD_DIR = build

### C Sources, Defines, and Includes ###
C_INCLUDES := -Imicrokernel/include \
			  -Imicrokernel/port/arm/cm4f \
              -Ihal/ \
			  -Ihal/stm32f446xx/include

SOURCES := 	demo1.c \
			microkernel/port/arm/cm4f/port.c \
			hal/startup.c \
           	$(wildcard microkernel/src/*.c) \
           	$(wildcard hal/stm32f446xx/src/*.c)

OBJECTS := $(addprefix $(BUILD_DIR)/, $(SOURCES:.c=.o))
DEPS := $(OBJECTS:.o=.d)

C_DEFS := 
 
### Binaries ###
PREFIX = ./arm-none-eabi-toolchain/bin/arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

### MCU Options ###
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
ABI = -mfloat-abi=hard

MCU = $(CPU) $(FPU) $(ABI) -mthumb

### Compiler Flags ###
# optimization flags
OPT := -Os

# Notes:
# -Os: optimize for size
# -flto: allows the compiler to see across translation units
#        for more efficient inlining and elimination of unused code

EXTRA_C_FLAGS := -fdata-sections \
			     -ffunction-sections \
				 -fno-common \
                 -W \
				 -Wall \
				 -Wextra \
				 -Wundef \
				 -Wshadow \
				 -Wdouble-promotion \
				 -Wformat-truncation \
				 -Wconversion \
				 -mgeneral-regs-only \
				 -MMD \
				 -MP

# Notes:
# -fdata-sections: places each global variable in its own linker section
# -ffunction-sections: places each function in its own linker section
# -fno-common: places uninitialized variables in .bss section
# These options allow the --gc-sections linker option to be used to reduce executable size

# generate debugger symbols and optimize for debugging if debug build
ifeq ($(DEBUG), 1)
    EXTRA_C_FLAGS += -g
    OPT += -Og
endif

C_FLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) $(EXTRA_C_FLAGS)

### Linker ###
LDSCRIPT = STM32F446XX_FLASH.ld

LIBS := -lc \
        -lgcc

EXTRA_LD_FLAGS := -nostartfiles \
                  -nostdlib \
				  --specs nano.specs \
				  --specs nosys.specs \
				  -Wl,--gc-sections \
				  -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# Notes:
# --specs nano.specs: use libc_nano (c standard library optimized for size) instead of libc
# --gc-sections: garbage collect unused sections

LD_FLAGS = -T $(LDSCRIPT) $(LIBS) $(EXTRA_LD_FLAGS)

### Build Targets ###
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	$(SZ) --format=GNU $<

# build .elf executable
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(C_FLAGS) $(LD_FLAGS) -o $@

# generate .hex file from .elf file
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(HEX) $< $@

# generate .bin file from .elf file
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(BIN) $< $@

# pattern rule for object files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(C_FLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
