#include "main.h"

EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL cursor_tmp = {0, 0, 0, 0};
int cursor_old_x;
int cursor_old_y;

void draw_cursor(int x, int y, EFI *efi)
{
    for(int i=y;i<y+20;++i){
        for(int j=x;j<x+20;++j){
            draw_pixel(i, j, color_blue, efi);
        }
    }
}

void save_cursor_area(int x, int y, EFI *efi)
{
    cursor_tmp = get_pixel(x, y, efi);
    cursor_tmp.Reserved = 0xff;
}

void load_cursor_area(int x, int y, EFI *efi)
{
    draw_pixel(x, y, cursor_tmp, efi);
}

void put_cursor(int x, int y, EFI *efi)
{
    if(cursor_tmp.Reserved) load_cursor_area(cursor_old_x, cursor_old_y, efi);
    save_cursor_area(x, y, efi);
    draw_cursor(x, y, efi);
    cursor_old_x = x;
    cursor_old_y = y;
}