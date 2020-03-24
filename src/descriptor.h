#pragma once

void init_gdt();
extern void default_handler(void);

class IDT
{
public:
    typedef struct
    {
        uint16_t offset_low, selector;
        uint8_t ist, type_attr;
        uint16_t offset_middle;
        uint32_t offset_high, zero;
    } INTERRUPT_DESCRIPTOR;

    IDT(const IDT &) = delete;
    IDT &operator=(const IDT &) = delete;
    IDT(IDT &&) = delete;
    IDT &operator=(IDT &&) = delete;
    static IDT &get_instance()
    {
        static IDT instance;
        return instance;
    }

    void init_idt();
    void set_interrupt_handler(unsigned int idt_no, __attribute__((ms_abi)) void (*handler)());

private:
    IDT() = default;
    ~IDT() = default;
    INTERRUPT_DESCRIPTOR descriptors[256];
};