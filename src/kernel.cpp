#include "main.h"

extern "C"{
    void kernel_start(FrameBuffer *FrameBuffer){
        kernel(FrameBuffer);
    }
}

void kernel(FrameBuffer *FrameBuffer){
    puts_font(FrameBuffer, "Linking to you, access our connection!\nKizunaOS, boot up!!\n\n");
    while(1);
}