#pragma once

#include "efi.h"
#include "graphics.h"
#include "stdfunc.h"

typedef struct {
    FrameBuffer frameBuffer;
} BootStruct;

extern "C" void kernel_start(EFI* efi, BootStruct* BootStruct);
void kernel(FrameBuffer *FrameBuffer);