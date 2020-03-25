#include "main.h"

const char keycode_map[] =
{
    0x00, Key_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '^', Key_Backspace, \
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '@', '[', Key_Enter, Key_Ctrl_L, \
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', ':', 0x00, Key_Shift_L, ']', \
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', Key_Shift_R, '*', Key_Alt_L, ' ', \
    Key_CapsLock, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_NumLock, Key_ScrollLock, \
};

void init_kbc(){
    IDT::get_instance().set_interrupt_handler(0x21, int21_handler);
    set_pic(0x21);
}