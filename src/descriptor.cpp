#include "main.h"

void init_gdt()
{
    const unsigned long long gdt[] = {
        0x0000000000000000,
        0x00af9a000000ffff,
        0x00cf93000000ffff};
    unsigned long long gdtr[2];
    gdtr[0] = (reinterpret_cast<unsigned long long>(gdt) << 16) | (sizeof(gdt) - 1);
    gdtr[1] = (reinterpret_cast<unsigned long long>(gdt) >> 48);
    load_gdt(gdtr);
    unsigned short cs, ds, ss;
    cs = 1 << 3;
    ds = 2 << 3;
    ss = 0;
    unsigned short selector = cs;
    unsigned long long dummy;
    asm volatile("pushq %[selector];"
                 "leaq ret_label(%%rip), %[dummy];"
                 "pushq %[dummy];"
                 "lretq;"
                 "ret_label:"
                 : [ dummy ] "=r"(dummy)
                 : [ selector ] "m"(selector));
    write_ss_selector(ss);
    write_ds_selector(ds);
}

void init_idt()
{
    
}