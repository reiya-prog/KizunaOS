#pragma once

#define KBC_DATA_ADDR 0x0060
#define KBC_DATA_PRESSED 0x80
#define KBC_STATUS_ADDR 0x0064
#define KBC_STATUS_OBF 0x01
#define KBC_STATUS_IBF 0x02

void do_kbc_handler(void);
extern "C" void do_default_handler(unsigned int handler_no);