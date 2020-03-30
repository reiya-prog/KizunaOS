#include "main.h"

extern "C"
{
    void kernel_start(BootStruct *boot_info)
    {
        init_kernel();
        kernel(&boot_info->frame_buffer);
    }
}

void init_kernel()
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
        io_cli();
        if(key_buf.empty()) continue;
        char write_data = key_buf.front();
        key_buf.pop();
        io_sti();
        putc(frame_buffer, write_data);
    }
    io_hlt();
}