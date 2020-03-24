#pragma once

#include "main.h"
#include "efi.h"
#include "elf_loader.h"

typedef struct
{
    short limit_low, base_low;
    char base_mid, access_right;
    char limit_high, base_high;
} SEGMENT_DESCRIPTOR;

typedef struct
{
    short offset_low, selector;
    char dw_count, access_right;
    short offset_high;
} GATE_DESCRIPTOR;

void init_gdt();
void init_idt();
void set_gdt(SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);
void set_idt(GATE_DESCRIPTOR *gd, int offset, int selector, int ar);
void boot_loader(EFI::EFI_HANDLE ImageHandle, EFI::EFI_SYSTEM_TABLE *SystemTable);