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

    load_kernel(ImageHandle, &efi, FrameBuffer);
}