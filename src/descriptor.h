#pragma once


typedef struct
{
    uint16_t offset_low, selector;
    uint8_t ist, type_attr;
    uint16_t offset_middle;
    uint32_t offset_high, zero;
} INTERRUPT_DESCRIPTOR;

void init_gdt();
void init_idt();
void set_interrupt_handler(unsigned int idt_no, __attribute__((ms_abi)) void (*handler)());;

extern INTERRUPT_DESCRIPTOR descriptors[256];