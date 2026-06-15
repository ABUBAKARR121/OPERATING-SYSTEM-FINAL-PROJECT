#ifndef COMMANDS_H
#define COMMANDS_H

#include "../core/types.h"

#define MAX_CMD_LEN 64
#define MAX_ARGS    8

void cmd_help(int argc, char* argv[]);
void cmd_clear(int argc, char* argv[]);
void cmd_ps(int argc, char* argv[]);
void cmd_mem(int argc, char* argv[]);
void cmd_ls(int argc, char* argv[]);
void cmd_create(int argc, char* argv[]);
void cmd_read(int argc, char* argv[]);
void cmd_write(int argc, char* argv[]);
void cmd_delete(int argc, char* argv[]);
void cmd_about(int argc, char* argv[]);
void cmd_sysinfo(int argc, char* argv[]);
void cmd_reboot(int argc, char* argv[]);
void cmd_logo(int argc, char* argv[]);

#endif
