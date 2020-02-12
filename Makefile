QEMU = qemu-system-x86_64
OVMF = ovmf/bios64.bin
QEMUflags = \
	-bios $(OVMF) -hda fat:App -nographic -curses
CC = x86_64-w64-mingw32-g++
CCflags = \
	-Wall -Wextra \
	-e efi_main \
	-nostdinc -nostdlib \
	-fno-builtin -Wl,--subsystem,10 -o $@ $<
TARGET = App/EFI/BOOT/BOOTX64.EFI

$(TARGET): src/main.cpp
	mkdir -p App/EFI/BOOT
	$(CC) $(CCflags) 

run: $(TARGET)
	$(QEMU) $(QEMUflags)

clean:
	rm -rf EFI