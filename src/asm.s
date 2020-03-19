.intel_syntax noprefix

.global check_hlt
check_hlt:
    hlt
    jmp check_hlt

.global sleep_hlt
sleep_hlt:
    hlt
    jmp sleep_hlt

.global jump_entry
jump_entry:
    push rbp
    mov rbp, rsp
    mov rsp, r8
    mov rdi, rcx
    call rdx
    mov rsp, rbp
    pop rbp
    ret