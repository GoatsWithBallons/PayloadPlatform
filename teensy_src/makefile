#########################################################################################
#
# Teensy Makefile
#
# Desc:
#		A makefile for building all the teensy source code.
#
# Usage:
#		make BUILD_LOC=[location of build dir] OBJECT_LOC=[project build path]
#
#		BUILD_LOC: Set the location of the build directory in relation to this makefile.
#
#		OBJECT_LOC: The location of the build directory in relation to the linker. This is
#					appended onto the names of the object files in the tmp file so the
#					linker can find them.
#	
#########################################################################################


#####################################################################
# FLAGS

CPU=cortex-m4

CFLAGS= -Wall -g -fno-common -mthumb -mcpu=$(CPU) -std=c99
ASFLAGS= -mcpu=$(CPU)


#####################################################################
# Files

OBJECT_FILE = $(BUILD_LOC)/teensy_objects.tmp

# Source files
BOARD_C_SRC = arm_cm4.c sysinit.c uart.c io.c pwm.c spi.c
BOARD_S_SRC = crt0.s

# Final output
BOARD_OBJECTS =  $(addprefix $(BUILD_LOC)/, $(BOARD_C_SRC:.c=.o) $(BOARD_S_SRC:.s=.o) $(BOARD_CXX_SRC:.cxx=.o) )

# Objects in relation to the rest of the project
OBJECTS = $(addprefix $(OBJECT_LOC)/, $(BOARD_C_SRC:.c=.o) $(BOARD_S_SRC:.s=.o) $(BOARD_CXX_SRC:.cxx=.o) )


#####################################################################
# Tools

MKDIR_P = mkdir -p

AS = arm-none-eabi-as
CC = arm-none-eabi-gcc


#####################################################################
# Rules

.phony: obj_file

all: obj_file $(BOARD_OBJECTS)

obj_file: $(BUILD_LOC)
	rm -f $(OBJECT_FILE)
	echo -n " " $(OBJECTS) >> $(OBJECT_FILE)

# Builds C files
$(BUILD_LOC)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Builds assembly files
$(BUILD_LOC)/%.o: %.s
	$(AS) $(ASFLAGS) -c -o $@ $<

# Creates the output directory
$(BUILD_LOC):
	$(MKDIR_P) $(BUILD_LOC)
