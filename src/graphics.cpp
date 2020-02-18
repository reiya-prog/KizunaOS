#include "main.h"
#include "graphics.h"
#include "efi.h"

EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL black = {0xff, 0xff, 0xff, 0xff};
EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff, 0xff, 0xff, 0xff};

void draw_pixel(unsigned int x, unsigned int y, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color, EFI *efi)
{
    unsigned int HorizontalResolution = efi->getGraphicsOutputProtocol()->Mode->Info->HorizontalResolution;
    EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = reinterpret_cast<EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *>(efi->getGraphicsOutputProtocol()->Mode->FrameBufferBase);
    EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *point = base + (HorizontalResolution * y) + x;

    point->Blue = 0xff;
    point->Green = 0xff;
    point->Red = 0xff;
    point->Reserved = 0xff;
}

void draw_rect(RECT rect, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color, EFI *efi)
{
    unsigned int i;
    for (i = rect.x; i < (rect.x + rect.w); ++i)
        draw_pixel(i, rect.y, color, efi);
    for (i = rect.x; i < (rect.x + rect.w); ++i)
        draw_pixel(i, rect.y + rect.h - 1, color, efi);

    for (i = rect.y; i < (rect.y + rect.h); ++i)
        draw_pixel(rect.x, i, color, efi);
    for (i = rect.y; i < (rect.y + rect.h); ++i)
        draw_pixel(rect.x + rect.w - 1, i, color, efi);
}
