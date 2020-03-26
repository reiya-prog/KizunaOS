#include "main.h"

char g_chara = 0;
int check;

extern "C"
{
    void kernel_start(BootStruct *boot_info)
    {
        kernel_init();
        kernel(&boot_info->frame_buffer);
    }
}

void kernel_init()
{
    init_gdt();
    init_idt();
    init_pic();
    init_kbc();
}

void kernel(FrameBuffer *frame_buffer)
{
    puts(frame_buffer, "Linking to you, access our connection!\nKizunaOS, boot up!\n");
    char *str = nullptr;
    sprintf(str, "resolution H:%d\nresolution V:%d\n", frame_buffer->resolution_H, frame_buffer->resolution_V);
    puts(frame_buffer, str);
    RECT r1 = {75, 100, 250, 400};
    RECT r2 = {100, 125, 250, 400};
    RECT r3 = {125, 150, 250, 400};
    while (1)
    {
        io_stihlt();
        putc(frame_buffer, g_chara);
        g_chara = 0;
    }
    io_hlt();
}