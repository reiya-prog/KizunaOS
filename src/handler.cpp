#include "main.h"

void do_kbc_handler()
{
    if (!(io_read_8(KBC_STATUS_ADDR) & KBC_STATUS_OBF))
    {
        io_write_8(PIC0_OCW2_ADDR, 0x61);
        return;
    }
    unsigned char keycode = io_read_8(KBC_DATA_ADDR);
    if (keycode & KBC_DATA_PRESSED)
    {
        io_write_8(PIC0_OCW2_ADDR, 0x61);
        return;
    }
    g_chara = keycode_map[keycode];
    io_write_8(PIC0_OCW2_ADDR, 0x61);
    return;
}

void do_mouse_handler()
{
    return;
}

extern "C"
{
    void do_default_handler(unsigned int handler_no)
    {
        switch (handler_no)
        {
        case 0x21: // キーボード入力
            do_kbc_handler();
            break;
        case 0x2c: // マウス入力
            do_mouse_handler();
            break;
        default: // 上記以外
            break;
        }
    }
}