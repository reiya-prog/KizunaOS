#pragma once

#define Key_ESC 0x1b
#define Key_Backspace 0x08
#define Key_Tab 0x09
#define Key_Enter 0x0a
#define Key_Ctrl_L 0x00
#define Key_Shift_L 0x00
#define Key_Shift_R 0x00
#define Key_Alt_L 0x00
#define Key_CapsLock 0x00
#define Key_F1 0x00
#define Key_F2 0x00
#define Key_F3 0x00
#define Key_F4 0x00
#define Key_F5 0x00
#define Key_F6 0x00
#define Key_F7 0x00
#define Key_F8 0x00
#define Key_F9 0x00
#define Key_F10 0x00
#define Key_NumLock 0x00
#define Key_ScrollLock 0x00

extern const char keycode_map[];

void init_kbc(void);