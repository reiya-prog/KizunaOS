#include "main.h"

EFI::CHAR16 getc(EFI *efi)
{
    EFI::EFI_INPUT_KEY key;
    unsigned long long waitidx;
    efi->getSystemTable()->BootServices->WaitForEvent(1, &(efi->getSystemTable()->ConIn->WaitForKey), &waitidx);
    efi->getSystemTable()->ConIn->ReadKeyStroke(efi->getSystemTable()->ConIn, &key);
    return key.UnicodeChar | key.ScanCode;
}

unsigned int gets(EFI *efi, unsigned short *buf, unsigned int buf_size)
{
    unsigned int i;
    for (i = 0; i < buf_size; ++i)
    {
        buf[i] = getc(efi);
        putc(efi, buf[i]);
    }
    buf[i] = L'\0';
    return i;
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

void puts(EFI *efi, EFI::CHAR16 *string){
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, string);
}

int strcmp(const unsigned short *s1, const unsigned short *s2)
{
	char is_equal = 1;

	for (; (*s1 != L'\0') && (*s2 != L'\0'); s1++, s2++) {
		if (*s1 != *s2) {
			is_equal = 0;
			break;
		}
	}

	if (is_equal) {
		if (*s1 != L'\0') {
			return 1;
		} else if (*s2 != L'\0') {
			return -1;
		} else {
			return 0;
		}
	} else {
		return (int)(*s1 - *s2);
	}
}

void strncpy(unsigned int *dst, unsigned int *src, unsigned long long n)
{
	while (n--)
		*dst++ = *src++;
}