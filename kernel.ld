ENTRY(kernel_start)

SECTIONS
{
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
        *(.rodata)
    }
    .got : {
        *(.got)
    }
    .bss : {
        *(.bss)
    }
}