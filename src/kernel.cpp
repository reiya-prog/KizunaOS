#include "main.h"

extern "C"{
    void kernel_start(BootStruct* boot_info){
        kernel_init();
        kernel(&boot_info->frame_buffer);
    }
}

void kernel_init(){
    init_gdt();
    IDT::get_instance().init_idt();
}

void kernel(FrameBuffer *frame_buffer){
    puts(frame_buffer, "Linking to you, access our connection!\nKizunaOS, boot up!\n");
    char *str = nullptr;
    sprintf(str, "resolution H:%d\nresolution V:%d",frame_buffer->resolution_H, frame_buffer->resolution_V);
    puts(frame_buffer, str);
    RECT r1 = {50, 50, 250, 400};
    RECT r2 = {75, 75, 250, 400};
    RECT r3 = {100, 100, 250, 400};
    draw_box(r1, Color_Red, frame_buffer);
    draw_box(r2, Color_Blue, frame_buffer);
    draw_box(r3, Color_Green, frame_buffer);
    sleep_hlt();
}