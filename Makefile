PROGNAME := /EFI/BOOT/BOOTX64.EFI
SRCDIR := src
OUTDIR := App

CC = x86_64-w64-mingw32-g++
Cflags = \
	-Wall -Wextra \
	-nostdinc -nostdlib \
	-fno-builtin -Wl,--subsystem,10

QEMU = qemu-system-x86_64
OVMF = ovmf/bios64.bin
QEMUflags = \
	-bios $(OVMF) -hda fat:App -nographic -curses

TARGET = $(OUTDIR)/$(PROGNAME)

SRCS := $(wildcard $(SRCDIR)/*.cpp)

all : $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p App/EFI/BOOT
	$(CC) $(Cflags) -o $@ $^

run: $(TARGET)
	$(QEMU) $(QEMUflags)

clean:
	rm -rf $(OUTDIR)