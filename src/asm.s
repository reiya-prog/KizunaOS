.intel_syntax noprefix

.global sleep_hlt
sleep_hlt:
    hlt
    jmp sleep_hlt

.global load_gdt
load_gdt:
    lgdt [rcx]
    ret

.global write_ss_selector
write_ss_selector:
    mov ss, cx
    ret

.global write_ds_selector
write_ds_selector:
    mov ds, cx
    ret

.global write_cs_selector
write_cs_selector:
    push rbp
    mov rbp, rsp
    lea rax, [rip + write_cs_end]
    push cx
    push rax
    ljmp [rax]
write_cs_end:
    add rsp, 8 + 2
    ret

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