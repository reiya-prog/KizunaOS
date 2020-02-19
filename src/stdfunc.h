#pragma once

EFI::CHAR16 getc(EFI *efi);
void putc(EFI *efi, EFI::CHAR16 chara);
void puth(unsigned long long val, unsigned char num_digits, EFI *efi);