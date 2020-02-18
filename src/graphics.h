#pragma once

#include "main.h"
#include "efi.h"

typedef struct{
    unsigned int x, y;
    unsigned int w, h;
} RECT;

extern EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL white;

void draw_pixel(unsigned int x, unsigned int y, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color, EFI *efi);
void draw_rect(RECT rect, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL bltPixel, EFI *efi);