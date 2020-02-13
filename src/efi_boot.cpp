#include "efi.h"

EFI_STATUS EFIAPI efi_boot_loader(
    IN EFI_HANDLE ImageHandle  __attribute__ ((unused)),
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"Hello KizunaOS!\n");
    while (1);
    return 0;
}