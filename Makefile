PROGNAME := BOOTX64.EFI
SRCDIR := src
OBJDIR := build
OUTDIR := app
APPDIR := $(OUTDIR)/EFI/BOOT
HOMEDIR := $(shell echo $$HOME)

CC = clang++
CPPFLAGS = \
	-I $(HOMEDIR)/x86_64-elf/include -I $(HOMEDIR)/x86_64-elf/include/c++/v1 \
	-D__ELF__ -D_LIBCPP_HAS_NO_THREADS \
	-O2 \
	--target=x86_64-elf \
	-Wall -Wextra \
	-nostdlibinc -nostdlib \
	-fno-builtin

LD = ld.lld
LDFLAGS = \
	--entry efi_main

QEMU = qemu-system-x86_64
OVMF = ovmf/bios64.bin
QEMUflags = \
	-bios $(OVMF) -hda fat:$(OUTDIR) -nographic -curses

TARGET = $(APPDIR)/$(PROGNAME)

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix $(OBJDIR)/,$(patsubst $(SRCDIR)/%.cpp,%.o,$(SRCS)))

.PHONY: all clean
all: $(TARGET)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -o $@ -c $<

$(TARGET): $(OBJS)
	mkdir -p $(APPDIR)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

run: $(TARGET)
	$(QEMU) $(QEMUflags)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)