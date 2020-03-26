#include "main.h"

void init_pic()
{
    io_write_8(PIC0_ICW1_ADDR, 0x11);
    io_write_8(PIC0_ICW2_ADDR, 0x20);
    io_write_8(PIC0_ICW3_ADDR, 0x04);
    io_write_8(PIC0_ICW4_ADDR, 0x01);
    io_write_8(PIC0_OCW1_ADDR, 0xff);

    io_write_8(PIC1_ICW1_ADDR, 0x11);
    io_write_8(PIC1_ICW2_ADDR, 0x28);
    io_write_8(PIC1_ICW3_ADDR, 0x02);
    io_write_8(PIC1_ICW4_ADDR, 0x01);
    io_write_8(PIC1_OCW1_ADDR, 0xff);
}

void set_pic(unsigned int idt_no)
{
    if (idt_no < 0x28)
    {
        unsigned char idt_set_bit = 1U << (idt_no - 0x20);
        if (!(io_read_8(PIC0_IMR_ADDR) & idt_set_bit))
            return;
        io_write_8(PIC0_OCW1_ADDR, io_read_8(PIC0_IMR_ADDR) - idt_set_bit);
    }
    else
    {
        unsigned char idt_set_bit = 1 << (idt_no - 0x28);
        if(!(io_read_8(PIC1_IMR_ADDR) & idt_set_bit))
            return;
        io_write_8(PIC1_OCW1_ADDR, io_read_8(PIC1_IMR_ADDR) - idt_set_bit);
    }
}