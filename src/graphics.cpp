#include "main.h"

EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_white = {0x00, 0x00, 0xff, 0xff};
EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_black = {0x00, 0x00, 0x00, 0xff};
EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_blue  = {0xff, 0x00, 0x00, 0xff};
EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_green = {0x00, 0xff, 0x00, 0xff};
EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_red   = {0x00, 0x00, 0xff, 0xff};

void draw_pixel(unsigned int x, unsigned int y, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color, EFI *efi)
{
    unsigned int HorizontalResolution = efi->getGraphicsOutputProtocol()->Mode->Info->HorizontalResolution;
    EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = reinterpret_cast<EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *>(efi->getGraphicsOutputProtocol()->Mode->FrameBufferBase);
    EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *point = base + (HorizontalResolution * y) + x;

    point->Blue = color.Blue;
    point->Green = color.Green;
    point->Red = color.Red;
    point->Reserved = color.Reserved;
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

EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(unsigned int x, unsigned int y, EFI *efi)
{
    unsigned int HorizontalResolution = efi->getGraphicsOutputProtocol()->Mode->Info->HorizontalResolution;
    EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = reinterpret_cast<EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *>(efi->getGraphicsOutputProtocol()->Mode->FrameBufferBase);
    EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL *point = base + (HorizontalResolution * y) + x;

    return *point;
}