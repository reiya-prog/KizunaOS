#pragma once

#include "efi.h"
#include "graphics.h"

extern "C"{
    __attribute__((ms_abi)) void sleep_hlt(void);
}