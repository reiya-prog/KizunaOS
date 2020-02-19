#include "main.h"
#include "graphics.h"
#include "efi.h"

EFI::EFI_STATUS EFIAPI BootLoader(
    IN EFI::EFI_HANDLE ImageHandle __attribute__ ((unused)),
    IN EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    RECT r = {10, 10, 100, 200};
    EFI efi_sub(SystemTable);
    efi_sub.EFIBootInit();
    efi_sub.getSystemTable()->ConOut->ClearScreen(efi_sub.getSystemTable()->ConOut);
    efi_sub.getSystemTable()->ConOut->OutputString(efi_sub.getSystemTable()->ConOut, (EFI::CHAR16 *)L"Linking to you, access our connection!\r\nKizunaOS, boot up!!\n\r\n");
    draw_rect(r, white, &efi_sub);
    // efi_sub.getGraphicsOutputProtocol()->Blt(efi_sub.getGraphicsOutputProtocol(), nullptr, EFI::EfiBltVideoFill, 10, 10, 110, 210, 100, 200, 0);
    while(1){
        EFI::CHAR16 c = getc(&efi_sub);
        putc(&efi_sub, c);
    }
    return 0;
}