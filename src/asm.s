.intel_syntax noprefix

.global jump_kernel
jump_kernel:
    push rbp
    mov rbp, rsp
    call rax
    mov rsp, rbp
    pop rbp
    ret