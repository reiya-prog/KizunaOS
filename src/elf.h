#pragma once

#include <elf.h>
#include "efi.h"

void load_kernel(EFI *efi, FrameBuffer *fb);
extern void jmp_kernel( EntryPoint, FrameBuffer *FrameBuffer);