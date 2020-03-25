#include "main.h"

int g_basey = 1;

void putc(FrameBuffer *fb, char chara)
{
    putc(fb, chara, Color_Black, Color_White);
}

void putc(FrameBuffer *fb, char chara, PixelFormat back_color)
{
    putc(fb, chara, back_color, Color_White);
}

void putc(FrameBuffer *fb, char chara, PixelFormat back_color, PixelFormat chara_color)
{
    char *str = nullptr;
    if (chara == '\r')
    {
        str[0] = '\n';
        str[1] = '\0';
    }
    else if (chara == '\b')
    {
        str[0] = '\b';
        str[1] = ' ';
        str[2] = '\b';
        str[3] = '\0';
    }
    else
    {
        str[0] = chara;
        str[1] = '\0';
    }
    puts_font(fb, str, back_color, chara_color);
}

void puts(FrameBuffer *fb, char *str)
{
    puts_font(fb, str, Color_Black, Color_White);
}

void puts(FrameBuffer *fb, char *str, PixelFormat back_color)
{
    puts_font(fb, str, back_color, Color_White);
}

void puts(FrameBuffer *fb, char *str, PixelFormat back_color, PixelFormat chara_color)
{
    puts_font(fb, str, back_color, chara_color);
}

void puts_font(FrameBuffer *fb, char *str, PixelFormat back_color, PixelFormat chara_color)
{
    int basex = 1, basey = g_basey;
    for (; *str != '\0'; ++str)
    {
        if (*str == '\n')
        {
            basex = 1;
            basey += 19;
            continue;
        }
        for (int y = 0; y < 16; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                if (font_map[*str][y][x])
                {
                    draw_pixel(basex + x, basey + y, chara_color, fb);
                }
                else
                {
                    draw_pixel(basex + x, basey + y, back_color, fb);
                }
            }
        }
        basex += 9;
    }
    g_basey = basey;
}

int dec_to_asc(char *str, int dec)
{
    int len = 0, len_buf;
    int buf[10];
    while (1)
    {
        buf[len++] = dec % 10;
        if (dec < 10)
            break;
        dec /= 10;
    }
    len_buf = len;
    while (len)
    {
        *(str++) = buf[--len] + 0x30;
    }
    return len_buf;
}

int hex_to_asc(char *str, int dec)
{
    int len = 0, len_buf;
    int buf[10];
    while (1)
    {
        buf[len++] = dec % 16;
        if (dec < 16)
            break;
        dec /= 16;
    }
    len_buf = len;
    while (len)
    {
        len--;
        *(str++) = (buf[len] < 10) ? (buf[len] + 0x30) : (buf[len] - 9 + 0x60);
    }
    return len_buf;
}

void sprintf(char *str, char *format, ...)
{
    va_list list;
    int i, len;
    va_start(list, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'd':
                len = dec_to_asc(str, va_arg(list, int));
                break;
            case 'x':
                len = hex_to_asc(str, va_arg(list, int));
                break;
            }
            str += len;
            format++;
        }
        else
        {
            *(str++) = *(format++);
        }
    }
    *str = 0x00;
    va_end(list);
}