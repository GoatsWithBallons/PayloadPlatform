#########################################################################################
#
# Main Makefile
#
# Desc:
#		Builds the whole system, provides commands for uploading the resulting elf.
#
#########################################################################################




#####################################################################
# Files

# Directories
BUILD_DIR = build
SRC_DIR = src/
TEENSY_SRC_DIR = teensy_src/


# Sources
SRC = main.cpp

INC = -I. -Iinc/

SRC_FILES = $(addprefix src/, $(SRC))

# Object files
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))

# Target Output
TARGET = payload
OBJECT_FILE = $(BUILD_DIR)/objects.tmp
TEENSY_OBJECTS = $(BUILD_DIR)/teensy_objects.tmp


#####################################################################
# Compile Tools

CPU=cortex-m4
MCU=mk20dx256 # For teensy_loader_cli

CFLAGS= -Wall -g -fno-common -mthumb -mcpu=$(CPU) -std=c99
CXXFLAGS = -Wall -g -fno-common -mthumb -mcpu=$(CPU) -fno-exceptions -fno-rtti -mfloat-abi=soft -nostdlib


LDSCRIPT= $(TEENSY_SRC_DIR)Teensy31_flash.ld
LDFLAGS= -nostartfiles -T$(LDSCRIPT) -mthumb -mcpu=$(CPU) -nostdlib

# Tools
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
UPLOAD = teensy_loader_cli

MKDIR_P = mkdir -p

#####################################################################
# Build Rules

.PHONY: clean flash dump teensy $(TARGET) stats

all: $(TARGET) stats

teensy:
	$(MAKE) -C $(TEENSY_SRC_DIR) BUILD_LOC=../build OBJECT_LOC=./build
	
$(TARGET): $(BUILD_DIR) | $(OBJECTS) teensy
	rm -f $(OBJECT_FILE)
	echo -n " " $(OBJECTS) >> $(OBJECT_FILE)
	$(CXX) $(LDFLAGS) @$(TEENSY_OBJECTS) @$(OBJECT_FILE) -o $@.elf
	$(OBJCOPY) -R .stack -O ihex $@.elf $@.hex

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.cpp
	@echo Compiling $@
	$(CXX) -c $(CXXFLAGS) $(INC) -o $@ $<
 
$(BUILD_DIR)/%.o: %.c
	@echo Compiling $@
	@$(CXX) -c $(CXXFLAGS) $(INC) -o $@ $<

$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

#####################################################################
# Tool Rules

dump:
	$(OBJDUMP) -S -D $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).S

stats:$(TARGET).elf
	$(SIZE) $(TARGET).elf

flash:$(TARGET).hex
	$(UPLOAD) -v -w --mcu=${MCU} $<

clean:
	rm -f -r build
	rm -f $(TARGET).hex $(TARGET).elf
