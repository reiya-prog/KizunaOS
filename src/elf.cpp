#include "main.h"

#define ELF_FILE_NAME KizunaOS.ELF

void load_kernel(EFI *efi, FrameBuffer *FrameBuffer){



    jmp_kernel(EntryPoint, FrameBuffer);
}