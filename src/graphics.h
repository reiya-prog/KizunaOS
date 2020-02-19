#pragma once

#include "efi.h"

typedef struct{
    unsigned int x, y;
    unsigned int w, h;
} RECT;

extern EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_white;
extern EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_black;
extern EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_blue;
extern EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_green;
extern EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color_red;

void draw_pixel(unsigned int x, unsigned int y, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color, EFI *efi);
void draw_rect(RECT rect, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL bltPixel, EFI *efi);
EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(unsigned int x, unsigned int y, EFI *efi);