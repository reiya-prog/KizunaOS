#pragma once

#include "efi.h"
#include "graphics.h"
#include "kernel.h"

extern "C"{
    __attribute__((ms_abi)) void sleep_hlt(void);
    __attribute__((ms_abi)) void check_hlt(int a, int b, int *c);
    __attribute__((ms_abi)) void jump_entry(BootStruct *bootStruct, unsigned long long entry_addr, unsigned long long stack_pointer);
}