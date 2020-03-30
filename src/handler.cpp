#include "main.h"

void do_kbc_handler()
{
    io_write_8(PIC0_OCW2_ADDR, 0x61);
    if (!(io_read_8(KBC_STATUS_ADDR) & KBC_STATUS_OBF))
    {
        return;
    }
    unsigned char keycode = io_read_8(KBC_DATA_ADDR);
    key_buf.push(keycode);
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
        case 0x21:
            do_kbc_handler();
            break;
        default:
            break;
        }
    }
}