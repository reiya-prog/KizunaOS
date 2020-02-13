#include "efi.h"

extern "C"{
    void efi_main(
        IN EFI_HANDLE ImageHandle,
        IN EFI_SYSTEM_TABLE *SystemTable
        )
    {
        efi_boot_loader(ImageHandle, SystemTable);
    }
}