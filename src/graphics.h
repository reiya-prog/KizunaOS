#pragma once

#include "efi.h"

typedef struct{
    unsigned int x, y;
    unsigned int w, h;
} RECT;

typedef struct
{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reserved;
} PixelFormat;

typedef struct
{
    unsigned long long *FrameBufferBase;
    unsigned long long FrameBufferSize;
    unsigned int ResolutionH;
    unsigned int ResolutionV;
} FrameBuffer;

extern PixelFormat Color_White;
extern PixelFormat Color_Black;
extern PixelFormat Color_Blue;
extern PixelFormat Color_Green;
extern PixelFormat Color_Red;

void draw_pixel(unsigned int x, unsigned int y, PixelFormat color, FrameBuffer *fb);
void draw_rect(RECT rect, PixelFormat bltPixel, FrameBuffer *fb);
PixelFormat get_pixel(unsigned int x, unsigned int y, FrameBuffer *fb);