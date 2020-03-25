#include "main.h"

char g_chara = 0;

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
    IDT::get_instance().init_idt();
    init_pic();
}

unsigned char get_kbc_data(void)
{
    /* ステータスレジスタの OBF がセットされるまで待つ */
    while (!(io_read_8(KBC_STATUS_ADDR) & 0x01))
        ;
    return io_read_8(KBC_DATA_ADDR);
}
unsigned char get_keycode(void)
{
    unsigned char keycode;
    /* make 状態 (brake ビットがセットされていない状態) まで待つ */
    while ((keycode = get_kbc_data()) & 0x80)
        ;
    return keycode;
}

void kernel(FrameBuffer *frame_buffer)
{
    puts(frame_buffer, "Linking to you, access our connection!\nKizunaOS, boot up!\n");
    char *str = nullptr;
    sprintf(str, "resolution H:%d\nresolution V:%d", frame_buffer->resolution_H, frame_buffer->resolution_V);
    puts(frame_buffer, str);
    RECT r1 = {75, 100, 250, 400};
    RECT r2 = {100, 125, 250, 400};
    RECT r3 = {125, 150, 250, 400};
    while (1)
    {
        char c = keycode_map[get_keycode()];
        putc(frame_buffer, c);
    }
    io_hlt();
}