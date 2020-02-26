#include "main.h"
#include "file.h"

EFI::EFI_STATUS EFIAPI BootLoader(
    IN EFI::EFI_HANDLE ImageHandle __attribute__ ((unused)),
    IN EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    RECT r = {10, 10, 100, 200};
    EFI EfiMain(SystemTable);
    EfiMain.EFIBootInit();
    EfiMain.getSystemTable()->ConOut->ClearScreen(EfiMain.getSystemTable()->ConOut);

    EfiMain.getSystemTable()->ConOut->OutputString(EfiMain.getSystemTable()->ConOut, (EFI::CHAR16 *)L"Linking to you, access our connection!\r\nKizunaOS, boot up!!\n\r\n");
    draw_rect(r, color_white, &EfiMain);

    unsigned long long Status;
    EFI::EFI_SIMPLE_POINTER_STATE State;
    unsigned int px = 0, py = 0;
    unsigned long long Waitidx;
    EFI::EFI_FILE_PROTOCOL *root;
    EfiMain.getSimpleFileSystemProtocol()->OpenVolume(EfiMain.getSimpleFileSystemProtocol(), &root);
    ls(&EfiMain);
    while(true){
        getc(&EfiMain);
    }
    return 0;
}