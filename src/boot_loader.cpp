#include "main.h"

FrameBuffer *initFrameBuffer(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP)
{
    FrameBuffer *fb = nullptr;
    fb->FrameBufferBase = reinterpret_cast<unsigned long long *>(GOP->Mode->FrameBufferBase);
    fb->FrameBufferSize = static_cast<unsigned long long>(GOP->Mode->FrameBufferSize);
    fb->ResolutionH = static_cast<unsigned int>(GOP->Mode->Info->HorizontalResolution);
    fb->ResolutionV = static_cast<unsigned int>(GOP->Mode->Info->VerticalResolution);

    return fb;
}

void boot_loader(EFI::EFI_HANDLE ImageHandle, EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    /* UEFI initialize */
    EFI efi(SystemTable);
    efi.initEFI();

    /*  /
     initGDTR();
     initIDTR();
     */

    FrameBuffer *FrameBuffer = initFrameBuffer(efi.getGraphicsOutputProtocol());

    /* Ready For ExitBootServices() */
    efi.getSystemTable()->ConOut->ClearScreen(efi.getSystemTable()->ConOut);
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
    // load_kernel(&efi, FrameBuffer);
    kernel_start(FrameBuffer);
}