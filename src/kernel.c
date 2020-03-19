#include <stdint.h>

int a = 0xaa;
uint64_t i;

uint8_t f() {
    return a;
}

int _start(uint8_t *frame_buffer) {
    for (i = 0; i < 1000; i ++) {
        frame_buffer[i] = f();
    }

    while (1) {
        __asm__ volatile ("hlt");
    }
}