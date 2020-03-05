#include "main.h"

extern "C"{
    void kernel_start(FrameBuffer *FrameBuffer){
        kernel(FrameBuffer);
    }
}

void kernel(FrameBuffer *FrameBuffer){
    puts(FrameBuffer, "Linking to you, access our connection!\nKizunaOS, boot up!!\n\n", Color_Black);
    while(1);
}