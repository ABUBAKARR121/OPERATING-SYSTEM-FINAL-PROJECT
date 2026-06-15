#ifndef SHELL_H
#define SHELL_H
#include "../core/types.h"
void shell_init(void);
void shell_run(void);
void shell_execute(char* input);
void shell_prompt(void);
#endif
