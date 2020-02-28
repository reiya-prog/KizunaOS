BIOS_NAME := BOOTX64.EFI
KERNEL_NAME := KizunaOS.ELF
SRCDIR := src
OBJDIR := build
OUTDIR := app
APPDIR := $(OUTDIR)/EFI/BOOT
HOMEDIR := $(shell echo $$HOME)

BIOS_TARGET = $(APPDIR)/$(BIOS_NAME)
KERNEL_TARGET = $(OUTDIR)/$(KERNEL_NAME)

CC = clang++
BIOS_CPPFLAGS = \
	-MMD -MP \
	-D__ELF__ -D_LIBCPP_HAS_NO_THREADS \
	--target=x86_64-pc-win32-coff \
	-fno-stack-protector -fshort-wchar \
	-nostdlibinc -mno-red-zone \
	-Wall -Wextra -Wpedantic \
	-fno-builtin \
	-std=c++17

KERNEL_CPPFLAGS = \
	-MMD -MP \
	-I $(HOMEDIR)/x86_64-elf/include -I $(HOMEDIR)/x86_64-elf/include/c++v1 \
	-D__ELF__ -D_LIBCPP_HAS_NO_THREADS \
	--target=x86_64-unknown-none-elf \
	-fno-stack-protector -fshort-wchar \
	-nostdlibinc -mno-red-zone \
	-Wall -Wextra -Wpedantic \
	-fno-builtin \
	-std=c++17

LD_LINK = /usr/bin/lld-link-6.0
LD_LLD = /usr/bin/ld.lld
BIOS_LDFLAGS = \
	-subsystem:efi_application -nodefaultlib \
	-entry:efi_main

KERNEL_LDFLAGS = \
	-e kernel_start -static -T kernel.ld

QEMU = qemu-system-x86_64
OVMF = ovmf/bios64.bin
QEMUflags = \
	-nographic -bios $(OVMF) -drive format=raw,file=fat:rw:$(OUTDIR)

BIOS_SRCS = \
	boot_loader.cpp efi_main.cpp efi.cpp graphics.cpp kernel.cpp stdfunc.cpp
KERNEL_SRCS = \
	kernel.cpp graphics.cpp stdfunc.cpp

SRCS = $(wildcard $(SRCDIR)/*.cpp)
BIOS_OBJS := $(addprefix $(OBJDIR)/,$(addsuffix .o, $(basename $(BIOS_SRCS))))
KERNEL_OBJS := $(addprefix $(OBJDIR)/,$(addsuffix .elf.o, $(basename $(KERNEL_SRCS))))
DEPS := $(addprefix $(OBJDIR)/,$(patsubst $(SRCDIR)/%.cpp,%.d,$(SRCS)))

.PHONY: all clean
all: $(BIOS_TARGET) $(KERNEL_TARGET) Makefile

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(BIOS_CPPFLAGS) -o $@ -c $<

$(OBJDIR)/%.elf.o:$(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(KERNEL_CPPFLAGS) -o $@ -c $<

$(BIOS_TARGET): $(BIOS_OBJS)
	mkdir -p $(APPDIR)
	$(LD_LINK) $(BIOS_LDFLAGS) -out:$(BIOS_TARGET) $(BIOS_OBJS)

$(KERNEL_TARGET): $(KERNEL_OBJS) kernel.ld
	mkdir -p $(APPDIR)
	$(LD_LLD) $(KERNEL_LDFLAGS) -o $(KERNEL_TARGET) $(KERNEL_OBJS)

run: $(TARGET)
	$(QEMU) $(QEMUflags)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)

-include $(DEPS)