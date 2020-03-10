#include "main.h"

extern "C"{
    void kernel_start(EFI* efi, BootStruct* BootStruct){
        efi->getSystemTable()->ConOut->ClearScreen(efi->getSystemTable()->ConOut);
        sleep_hlt();
        kernel(&BootStruct->frameBuffer);
    }
}

void kernel(FrameBuffer *FrameBuffer){
    puts(FrameBuffer, "KizunaOS boot up!\n");
    while(1);
}