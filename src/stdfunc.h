#pragma once

#include "efi.h"

#define min(a, b) a > b ? b : a
#define max(a, b) a > b ? a : b

EFI::CHAR16 getc(EFI *efi);
void putc(EFI *efi, EFI::CHAR16 chara);
void puth(unsigned long long val, unsigned char num_digits, EFI *efi);
