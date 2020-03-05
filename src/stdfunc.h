#pragma once

#include "efi.h"

#define min(a, b) a > b ? b : a
#define max(a, b) a > b ? a : b

void putc(FrameBuffer *fb, char chara);
void putc(FrameBuffer *fb, char chara, PixelFormat back_color);
void putc(FrameBuffer *fb, char chara, PixelFormat back_color, PixelFormat chara_color);
void puts(FrameBuffer *fb, char *str);
void puts(FrameBuffer *fb, char *str, PixelFormat back_color);
void puts(FrameBuffer *fb, char *str, PixelFormat back_color, PixelFormat chara_color);
void puts_font(FrameBuffer *fb, char *str, PixelFormat back_color, PixelFormat chara_color);