#pragma once

#define Key_CapsLock 0x00
#define Key_ESC 0x01
#define Key_Backspace 0x0e
#define Key_Tab 0x0f
#define Key_Enter 0x1c
#define Key_Ctrl_L 0x1d
#define Key_Shift_L 0x2b
#define Key_Backslash 0x2c
#define Key_Shift_R 0x36
#define Key_Alt_L 0x38
#define Key_F1 0x3b
#define Key_F2 0x3c
#define Key_F3 0x3d
#define Key_F4 0x3e
#define Key_F5 0x3f
#define Key_F6 0x40
#define Key_F7 0x41
#define Key_F8 0x42
#define Key_F9 0x43
#define Key_F10 0x44
#define Key_PgUp 0x48
#define Key_Home 0x4b
#define Key_End 0x4d
#define Key_PgDn 0x50
#define Key_Insert 0x52
#define Key_Delete 0x53
#define Key_F11 0x57
#define Key_F12 0x58
#define Key_Windows 0x5b

extern const char keymap[];
extern const char keymap_shift[];

void init_kbc(void);
unsigned char get_kbc_data(void);
unsigned char get_keycode(void);