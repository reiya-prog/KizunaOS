QEMU = qemu-system-x86_64
OVMF = ovmf/bios64.bin
QEMUflags = \
	-bios $(OVMF) -hda fat:App -nographic -curses
CC = x86_64-w64-mingw32-gcc
CCflags = \
	-Wall -Wextra \
	-e efi_main \
	-nostdinc -nostdlib \
	-fno-builtin -Wl,--subsystem,10 -o $@ $<
TARGET = App/EFI/BOOT/BOOTX64.EFI

run: $(TARGET)
	$(QEMU) $(QEMUflags)

$(TARGET): src/main.c
	mkdir -p App/EFI/BOOT
	$(CC) $(CCflags) 

clean:
	rm -rf EFI