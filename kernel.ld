ENTRY(kernel_start)

SECTIONS
{
    . += 0x101000;
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
        *(.rodata)
    }
    .bss : {
        *(.bss)
    }
}