.intel_syntax noprefix

.global sleep_hlt
sleep_hlt:
    hlt
    jmp sleep_hlt

.global jump_kernel
jump_kernel:
    push rbp
    mov rbp, rsp
    call rax
    mov rsp, rbp
    pop rbp
    ret