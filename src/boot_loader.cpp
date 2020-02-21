#include "main.h"

EFI::EFI_STATUS EFIAPI BootLoader(
    IN EFI::EFI_HANDLE ImageHandle __attribute__ ((unused)),
    IN EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    RECT r = {10, 10, 100, 200};
    EFI efi(SystemTable);
    efi.EFIBootInit();
    efi.getSystemTable()->ConOut->ClearScreen(efi.getSystemTable()->ConOut);

    efi.getSystemTable()->ConOut->OutputString(efi.getSystemTable()->ConOut, (EFI::CHAR16 *)L"Linking to you, access our connection!\r\nKizunaOS, boot up!!\n\r\n");

    unsigned long long Status;
    EFI::EFI_SIMPLE_POINTER_STATE State;
    unsigned int px = 0, py = 0;
    unsigned long long Waitidx;

    draw_rect(r, color_white, &efi);
    while(true){
        put_cursor(px, py, &efi);
        efi.getSystemTable()->BootServices->WaitForEvent(1, &(efi.getSimplePointerProtocol()->WaitForInput), &Waitidx);
        Status = efi.getSimplePointerProtocol()->GetState(efi.getSimplePointerProtocol(), &State);
        putc(&efi, L'c');
        if(!Status){
            px += State.RelativeMovementX >> 13;
            px = max(0, px);
            px = min(efi.getGraphicsOutputProtocol()->Mode->Info->HorizontalResolution-6, px);
            py += State.RelativeMovementY >> 13;
            py = max(0, py);
            py = min(efi.getGraphicsOutputProtocol()->Mode->Info->VerticalResolution-6, py);

        }
    }
    return 0;
}