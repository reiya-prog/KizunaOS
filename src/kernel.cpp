#include "main.h"

extern "C"{
    void kernel_start(BootStruct* BootStruct){
        kernel(&BootStruct->frameBuffer);
    }
}

void kernel(FrameBuffer *FrameBuffer){
    puts(FrameBuffer, "KizunaOS boot up!\n");
    sleep_hlt();
}