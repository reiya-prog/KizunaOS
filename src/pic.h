#pragma once

#include "asm_kernel.h"

#define PIC0_ICW1_ADDR 0x0020
#define PIC0_ICW2_ADDR 0x0021
#define PIC0_ICW3_ADDR 0x0021
#define PIC0_ICW4_ADDR 0x0021
#define PIC0_OCW1_ADDR 0x0021
#define PIC0_OCW2_ADDR 0x0020
#define PIC0_IMR_ADDR 0x0021
#define PIC1_ICW1_ADDR 0x00a0
#define PIC1_ICW2_ADDR 0x00a1
#define PIC1_ICW3_ADDR 0x00a1
#define PIC1_ICW4_ADDR 0x00a1
#define PIC1_OCW1_ADDR 0x00a1
#define PIC1_OCW2_ADDR 0x00a0
#define PIC1_IMR_ADDR 0x00a1

void init_pic(void);
void set_pic(unsigned int idt_no);