#pragma once

#include "efi.h"

#define min(a, b) a > b ? b : a
#define max(a, b) a > b ? a : b

EFI::CHAR16 getc(EFI *efi);
unsigned int gets(EFI *efi, unsigned short *buf, unsigned int buf_size);
void putc(EFI *efi, EFI::CHAR16 chara);
void puts(EFI *efi, EFI::CHAR16 *string);
void puth(EFI *efi, unsigned long long val, unsigned char num_digits);
int strcmp(const unsigned short *s1, const unsigned short *s2);
void strncpy(unsigned int *dst, unsigned int *src, unsigned long long n);