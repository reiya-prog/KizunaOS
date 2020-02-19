PROGNAME := BOOTX64.EFI
SRCDIR := src
OBJDIR := build
OUTDIR := app
APPDIR := $(OUTDIR)/EFI/BOOT
HOMEDIR := $(shell echo $$HOME)

CC = clang++
CPPFLAGS = \
	-MMD -MP\
	-I $(HOMEDIR)/x86_64-elf/include -I $(HOMEDIR)/x86_64-elf/include/c++v1 \
	-D__ELF__ -D_LIBCPP_HAS_NO_THREADS \
	--target=x86_64-pc-win32-coff \
	-fno-stack-protector -fshort-wchar \
	-nostdlibinc -mno-red-zone \
	-Wall -Wextra -Wpedantic \
	-fno-builtin \
	-std=c++17

LD = /usr/bin/lld-link-6.0
LDFLAGS = \
	-subsystem:efi_application -nodefaultlib \
	-entry:efi_main

QEMU = qemu-system-x86_64
OVMF = ovmf/bios64.bin
QEMUflags = \
	-nographic -bios $(OVMF) -drive format=raw,file=fat:rw:$(OUTDIR)

TARGET = $(APPDIR)/$(PROGNAME)

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix $(OBJDIR)/,$(patsubst $(SRCDIR)/%.cpp,%.o,$(SRCS)))
DEPS := $(addprefix $(OBJDIR)/,$(patsubst $(SRCDIR)/%.cpp,%.d,$(SRCS)))

.PHONY: all clean
all: $(TARGET) Makefile

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -o $@ -c $<

$(TARGET): $(OBJS)
	mkdir -p $(APPDIR)
	$(LD) $(LDFLAGS) -out:$(TARGET) $(OBJS)

run: $(TARGET)
	$(QEMU) $(QEMUflags)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)

-include $(DEPS)