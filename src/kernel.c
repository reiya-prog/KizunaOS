#include <stdint.h>

int a = 0xaa;
uint64_t i;

uint8_t f() {
    return a;
}

int _start(uint8_t *frame_buffer, uint64_t size) {
    for (i = 0; i < size; i ++) {
        frame_buffer[i] = f();
    }

    while (1) {
        __asm__ volatile ("hlt");
    }
}