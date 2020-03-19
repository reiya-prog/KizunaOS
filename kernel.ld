ENTRY(kernel_start)

SECTIONS
{
    .text : {
        *(.text)
    }
    . += 0x10000;
    .data : {
        *(.data)
        *(.rodata)
    }
    . += 0x10000;
    .got : {
        *(.got)
    }
    . += 0x10000;
    .bss : {
        *(.bss)
    }
}