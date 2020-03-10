.intel_syntax noprefix

.global sleep_hlt
sleep_hlt:
    hlt
    jmp sleep_hlt

.global jump_entry
jump_entry:
    call rdx