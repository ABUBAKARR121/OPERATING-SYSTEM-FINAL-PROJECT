#ifndef CONSOLE_H
#define CONSOLE_H
#include "vga.h"
void console_init(void);
void console_clear(void);
void console_write(const char* str);
void console_write_int(int n);
void console_write_colored(const char* str, uint8_t color);
void console_newline(void);
#endif
