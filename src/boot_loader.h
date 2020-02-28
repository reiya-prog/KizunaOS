#pragma once

#include "main.h"
#include "efi.h"
#include "elf.h"

void boot_loader(EFI::EFI_HANDLE ImageHandle, EFI::EFI_SYSTEM_TABLE *SystemTable);