#include "main.h"

FrameBuffer *init_fb(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP)
{
    FrameBuffer *fb = nullptr;
    fb->frame_buffer_base = reinterpret_cast<unsigned long long *>(GOP->Mode->FrameBufferBase);
    fb->frame_buffer_size = static_cast<unsigned long long>(GOP->Mode->FrameBufferSize);
    fb->resolution_H = static_cast<unsigned int>(GOP->Mode->Info->HorizontalResolution);
    fb->resolution_V = static_cast<unsigned int>(GOP->Mode->Info->VerticalResolution);

    return fb;
}

void boot_loader(EFI::EFI_HANDLE ImageHandle, EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    /* UEFI initialize */
    EFI efi(SystemTable);
    efi.initEFI();
    FrameBuffer *frame_buffer = init_fb(efi.getGraphicsOutputProtocol());

    load_kernel(ImageHandle, &efi, frame_buffer);
}