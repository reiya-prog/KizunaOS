#pragma once

typedef struct {
    short offset, selector;
    char dw_count, access_right;
    short offset_high;
} GATE_DESCRIPTOR;

void init_gdt();
void init_idt();