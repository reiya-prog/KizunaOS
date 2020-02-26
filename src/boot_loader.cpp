#include "main.h"

void BootLoader(EFI::EFI_HANDLE ImageHandle, EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    /* UEFI initialize */
    EFI efi(SystemTable);
    efi.initEFI();
    efi.getSystemTable()->ConOut->ClearScreen(efi.getSystemTable()->ConOut);

    /*  */
    initGDTR();
    initIDTR();

    efi.getSystemTable()->ConOut->OutputString(efi.getSystemTable()->ConOut, (EFI::CHAR16 *)L"Linking to you, access our connection!\r\nKizunaOS, boot up!!\n\r\n");

    /* Ready For ExitBootServices() */
    EFI::EFI_STATUS status;
    EFI::EFI_MEMORY_DESCRIPTOR *MemoryMap = nullptr;
    EFI::UINTN MemoryMapSize = 0;
    EFI::UINTN MapKey, DescriptorSize;
    EFI::UINT32 DescriptorVersion;
    do
    {
        status = efi.getSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
        while (status == EFI::EFI_BUFFER_TOO_SMALL)
        {
            if (MemoryMap)
            {
                efi.getSystemTable()->BootServices->FreePool(MemoryMap);
            }
            status = efi.getSystemTable()->BootServices->AllocatePool(EFI::EfiLoaderData, MemoryMapSize, reinterpret_cast<EFI::VOID **>(&MemoryMap));
            status = efi.getSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
        }
        status = efi.getSystemTable()->BootServices->ExitBootServices(ImageHandle, MapKey);
    } while (status != EFI::EFI_SUCCESS);

    /* Kernel Start */

}