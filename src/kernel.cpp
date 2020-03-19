#include "main.h"

int p = 100;

extern "C"{
    void kernel_start(BootStruct* BootStruct){
        kernel(&BootStruct->frameBuffer);
    }
}

void kernel(FrameBuffer *FrameBuffer){
    puts(FrameBuffer, "Linking to you, access our connection!\nKizunaOS, boot up!\n");
    sleep_hlt();
}