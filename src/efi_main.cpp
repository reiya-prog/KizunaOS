#include "main.h"

extern "C"{
    void efi_main(
        IN EFI::EFI_HANDLE ImageHandle,
        IN EFI::EFI_SYSTEM_TABLE *SystemTable
        )
    {
        boot_loader(ImageHandle, SystemTable);
    }
}