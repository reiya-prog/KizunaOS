#pragma once

#include "efi.h"

#define min(a, b) a > b ? b : a
#define max(a, b) a > b ? a : b

EFI::CHAR16 getc(EFI *efi);
void putc(FrameBuffer *fb, char chara);
void puts(FrameBuffer *fb, char *str);
void puts_font(FrameBuffer *fb, char *str);