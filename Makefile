# TARGET: name of the output file
TARGET = main
# MCU: part number to build for
MCU = TM4C123GH6PM
# SOURCES: list of input source sources
SOURCES = main.c bsp.c startup_tm4c_gnu.c
# INCLUDES: list of includes, by default, use Includes directory
INCLUDES = -I$(HOME)/embedded/cmsis/Include -I$(HOME)/embedded/include/tm4c
# OUTDIR: directory to use for output
OUTDIR = build
# TIVAWARE_PATH: path to tivaware folder
TIVAWARE_PATH = $(HOME)/embedded/tivaware/TivaWare_C_Series-2.1.4.178

# LD_SCRIPT: linker script
LD_SCRIPT = $(MCU).lds

FLOAT_ABI = hard

# flags
CFLAGS = -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=$(FLOAT_ABI)
CFLAGS +=-Os -ffunction-sections -fdata-sections -MD -std=c99 -Wall
CFLAGS += -pedantic -DPART_$(MCU) -c -I$(TIVAWARE_PATH) $(INCLUDES)
# SKIP_EXTERN_C is checked by the tm4c_cmsis.h include
CFLAGS += -DTARGET_IS_TM4C123_RB2 -D__FPU_PRESENT -DSKIP_EXTERN_C
LDFLAGS = -T $(LD_SCRIPT) --entry Reset_Handler
LDFLAGS += -L$(TIVAWARE_PATH)/driverlib/gcc/ -ldriver --specs=nosys.specs
LDFLAGS += -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=$(FLOAT_ABI) -mfloat-abi=$(FLOAT_ABI)

# binaries

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
RM      = rm -f
MKDIR	= mkdir -p


# list of object files, placed in the build directory regardless of source path
OBJECTS = $(addprefix $(OUTDIR)/,$(notdir $(SOURCES:.c=.o)))

# default: build bin
all: $(OUTDIR)/$(TARGET).bin

$(OUTDIR)/%.o: src/%.c | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/a.out: $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OUTDIR)/main.bin: $(OUTDIR)/a.out
	$(OBJCOPY) -O binary $< $@

# create the output directory
$(OUTDIR):
	$(MKDIR) $(OUTDIR)

clean:
	-$(RM) $(OUTDIR)/*

.PHONY: all clean
