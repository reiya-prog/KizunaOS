#include "main.h"

const char keymap[] = 
{
    0x00, Key_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', ';', Key_Backspace, Key_Tab,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', Key_Enter, Key_Ctrl_L, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ':', '^', 0x00, Key_Shift_L, Key_Backslash, 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', Key_Shift_R, '*', Key_Alt_L, ' ', 0x00, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5,
    Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, 0x00, 0x00, 0x00, Key_PgUp, 0x00, 0x00, Key_Home, 0x00, Key_End, 0x00, 0x00,
    Key_PgDn, 0x00, Key_Insert, Key_Delete, 0x00, 0x00, 0x00, Key_F11, Key_F12, 0x00, 0x00, Key_Windows, 0x00, 0x00, 0x00, 0x00
};

const char keymap_shift[] =
{
    0x00, Key_ESC, '!', '"', '#', '$', '%', '&', 0x27, '(', ')', 0x00, '=', '+', Key_Backspace, Key_Tab,
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', Key_Enter, Key_Ctrl_L, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', '*', '~', 0x00, Key_Shift_L, '|', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<', '>', '?', Key_Shift_R, '*', Key_Alt_L, ' ', 0x00, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5,
    Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, 0x00, 0x00, 0x00, Key_PgUp, 0x00, 0x00, Key_Home, 0x00, Key_End, 0x00, 0x00,
    Key_PgDn, 0x00, Key_Insert, Key_Delete, 0x00, 0x00, 0x00, Key_F11, Key_F12, 0x00, 0x00, Key_Windows, 0x00, 0x00, 0x00, 0x00
};

void init_kbc()
{
    set_interrupt_handler(0x21, int21_handler);
    set_pic(0x21);
}