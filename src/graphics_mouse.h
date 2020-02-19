#pragma once

#include "graphics.h"

void draw_mouse(int x, int y, EFI *efi);
void save_cursor_area(int x, int y, EFI *efi);
void load_cursor_area(int x, int y, EFI *efi);
void put_cursor(int x, int y, EFI *efi);