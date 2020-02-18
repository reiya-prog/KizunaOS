#include "main.h"

EFI::CHAR16 getc(EFI *efi)
{
    EFI::EFI_INPUT_KEY key;
    unsigned long long waitidx;
    efi->getSystemTable()->BootServices->WaitForEvent(1, &(efi->getSystemTable()->ConIn->WaitForKey), &waitidx);
    efi->getSystemTable()->ConIn->ReadKeyStroke(efi->getSystemTable()->ConIn, &key);
    return key.UnicodeChar | key.ScanCode;
}

void putc(EFI *efi, EFI::CHAR16 chara)
{
    unsigned short str[4];
    if (chara == L'\r')
    {
        str[0] = L'\r';
        str[1] = L'\n';
        str[2] = L'\0';
    }
    else if (chara == L'\b')
    {
        str[0] = L'\b';
        str[1] = L' ';
        str[2] = L'\b';
        str[3] = L'\0';
    }
    else
    {
        str[0] = chara;
        str[1] = L'\0';
    }
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, str);
}