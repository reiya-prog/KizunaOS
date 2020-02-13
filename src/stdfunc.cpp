#include "main.h"

EFI::CHAR16 getc(EFI::EFI_SYSTEM_TABLE *SystemTable)
{
    EFI::EFI_INPUT_KEY key;
    unsigned long long waitidx;
    SystemTable->BootServices->WaitForEvent(1, &(SystemTable->ConIn->WaitForKey), &waitidx);
    SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key);
    return key.UnicodeChar;
}

void putc(EFI::EFI_SYSTEM_TABLE *SystemTable, EFI::CHAR16 chara)
{
    unsigned short str[3];
    if (chara != L'\r')
    {
        str[0] = chara;
        str[1] = L'\0';
    }
    else
    {
        str[0] = L'\r';
        str[1] = L'\n';
        str[2] = L'\0';
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
}