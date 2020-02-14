#include "main.h"

void efi_boot_init(IN EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
}

EFI::EFI_STATUS EFIAPI efi_boot_loader(
    IN EFI::EFI_HANDLE ImageHandle  __attribute__ ((unused)),
    IN EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (EFI::CHAR16 *)L"KizunaOS boot up!\r\n");
    while(1){
        EFI::CHAR16 c = getc(SystemTable);
        putc(SystemTable, c);
    }
    return 0;
}