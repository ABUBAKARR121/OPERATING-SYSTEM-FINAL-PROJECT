#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../core/types.h"
void keyboard_init(void);
char keyboard_getchar(void);
void keyboard_read_line(char* buffer, int max_len);
#endif
