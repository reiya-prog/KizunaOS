#pragma once

#include "efi.h"
#include <stdarg.h>

#define min(a, b) a > b ? b : a
#define max(a, b) a > b ? a : b

extern unsigned char font_map[256][16][8];

void putc(FrameBuffer *fb, char chara);
void putc(FrameBuffer *fb, char chara, PixelFormat back_color);
void putc(FrameBuffer *fb, char chara, PixelFormat back_color, PixelFormat chara_color);
void puts(FrameBuffer *fb, char *str);
void puts(FrameBuffer *fb, char *str, PixelFormat back_color);
void puts(FrameBuffer *fb, char *str, PixelFormat back_color, PixelFormat chara_color);
void puts_font(FrameBuffer *fb, char *str, PixelFormat back_color, PixelFormat chara_color);
int dec_to_asc(char *str, int dec);
int hex_to_asc(char *str, int dec);
void sprintf(char *str, char *format, ...);