PROGNAME := BOOTX64.EFI
SRCDIR := src
OBJDIR := build
OUTDIR := app
APPDIR := $(OUTDIR)/EFI/BOOT
HOMEDIR := $(shell echo $$HOME)

CC = clang++
CPPFLAGS = \
	-O2 \
	--target=x86_64-pc-win32-coff \
	-fno-stack-protector -fshort-wchar \
	-nostdlibinc -mno-red-zone \
	-Wall -Wextra -Wpedantic \
	-fno-builtin \
	-fuse-ld=ld

LD = ld.lld
LDFLAGS = \
	--target=x86_64-pc-win32-coff \
	--entry=efi_main \
	-fuse-ld=lld

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
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

run: $(TARGET)
	$(QEMU) $(QEMUflags)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)