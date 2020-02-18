#pragma once

#include "main.h"
#include "efi.h"

EFI::EFI_STATUS EFIAPI BootLoader(IN EFI::EFI_HANDLE ImageHandle, IN EFI::EFI_SYSTEM_TABLE *SystemTable);