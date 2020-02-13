#include "main.h"

extern "C"{
    void efi_main(
        IN EFI::EFI_HANDLE ImageHandle,
        IN EFI::EFI_SYSTEM_TABLE *SystemTable
        )
    {
        efi_boot_loader(ImageHandle, SystemTable);
    }
}