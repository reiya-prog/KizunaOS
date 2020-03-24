#pragma once

#include "efi.h"
#include "graphics.h"
#include "kernel.h"

extern "C"{
    __attribute__((ms_abi)) void sleep_hlt(void);
    __attribute__((ms_abi)) void load_gdt(unsigned long long gdtr[2]);
    __attribute__((ms_abi)) void write_ss_selector(unsigned short ss);
    __attribute__((ms_abi)) void write_ds_selector(unsigned short ds);
    __attribute__((ms_abi)) void write_cs_selector(unsigned short cs);
    __attribute__((ms_abi)) void jump_entry(BootStruct *bootStruct, unsigned long long entry_addr, unsigned long long stack_pointer);
}