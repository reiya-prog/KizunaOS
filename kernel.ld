ENTRY(kernel_start)

SECTIONS
{
    .text ALIGN(0x1000): {
        *(.text)
    }
    . += 0x10000;
    .data ALIGN(0x1000): {
        *(.data)
    }
    .got : {
        *(.got)
    }
}