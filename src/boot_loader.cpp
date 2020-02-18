#include "main.h"
#include "graphics.h"
#include "efi.h"

EFI::EFI_STATUS EFIAPI BootLoader(
    IN EFI::EFI_HANDLE ImageHandle __attribute__ ((unused)),
    IN EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    RECT r = {10, 10, 100, 200};
    EFI efi_sub;
    efi_sub.setSystemTable(SystemTable);
    EFI *efi = &efi_sub;
    efi->getSystemTable()->ConOut->ClearScreen(efi->getSystemTable()->ConOut);
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Linking to you, access our connection!\r\nKizunaOS, boot up!!\n\r\n");
    draw_rect(r, white, efi);
    while(1){
        EFI::CHAR16 c = getc(efi);
        putc(efi, c);
    }
    return 0;
}