#include "main.h"
#include "boot_loader.h"

extern "C"{
    void efi_main(
        IN EFI::EFI_HANDLE ImageHandle,
        IN EFI::EFI_SYSTEM_TABLE *SystemTable
        )
    {
        BootLoader(ImageHandle, SystemTable);
    }
}