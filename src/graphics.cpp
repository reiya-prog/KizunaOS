#include "main.h"

PixelFormat Color_White = {0xff, 0xff, 0xff, 0xff};
PixelFormat Color_Black = {0x00, 0x00, 0x00, 0xff};
PixelFormat Color_Blue = {0xff, 0x00, 0x00, 0xff};
PixelFormat Color_Green = {0x00, 0xff, 0x00, 0xff};
PixelFormat Color_Red = {0x00, 0x00, 0xff, 0xff};

void draw_pixel(unsigned int x, unsigned int y, PixelFormat color, FrameBuffer *fb)
{
    PixelFormat *base = reinterpret_cast<PixelFormat *>(fb->FrameBufferBase);
    PixelFormat *point = base + (fb->ResolutionH * y) + x;

    point->Blue = color.Blue;
    point->Green = color.Green;
    point->Red = color.Red;
    point->Reserved = color.Reserved;
}

void draw_rect(RECT rect, PixelFormat color, FrameBuffer *fb)
{
    unsigned int i;
    for (i = rect.x; i < (rect.x + rect.w); ++i)
        draw_pixel(i, rect.y, color, fb);
    for (i = rect.x; i < (rect.x + rect.w); ++i)
        draw_pixel(i, rect.y + rect.h - 1, color, fb);

    for (i = rect.y; i < (rect.y + rect.h); ++i)
        draw_pixel(rect.x, i, color, fb);
    for (i = rect.y; i < (rect.y + rect.h); ++i)
        draw_pixel(rect.x + rect.w - 1, i, color, fb);
}

PixelFormat get_pixel(unsigned int x, unsigned int y, FrameBuffer *fb)
{
    PixelFormat *base = reinterpret_cast<PixelFormat *>(fb->FrameBufferBase);
    PixelFormat *point = base + (fb->ResolutionH * y) + x;

    return *point;
}