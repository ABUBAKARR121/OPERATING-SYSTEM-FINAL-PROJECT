#include "shell.h"
#include "commands.h"
#include "../drivers/display/vga.h"
#include "../drivers/input/keyboard.h"
#include "../../libc/string.h"
#include "../../libc/stdio.h"

typedef struct { char* name; void (*func)(int,char**); } cmd_t;
static cmd_t cmds[]={
    {"help",cmd_help},{"clear",cmd_clear},{"ps",cmd_ps},{"mem",cmd_mem},{"ls",cmd_ls},
    {"create",cmd_create},{"touch",cmd_create},{"read",cmd_read},{"cat",cmd_read},{"type",cmd_read},
    {"write",cmd_write},{"delete",cmd_delete},{"del",cmd_delete},{"rm",cmd_delete},
    {"about",cmd_about},{"sysinfo",cmd_sysinfo},{"reboot",cmd_reboot},{"logo",cmd_logo},
    {0,0}
};

void shell_init(void){kprint_color("[SHELL] Command interpreter ready\n",VGA_GREEN);}
void shell_prompt(void){kprint_color("\nSLeOS> ",VGA_GREEN);}

void shell_execute(char* in){
    if(!in||strlen(in)==0)return;
    char* av[MAX_ARGS];
    int ac=0;
    char* p=in;

    while(*p){
        while(*p==' ')p++;   /* skip spaces */
        if(!*p)break;

        /* quoted string? */
        if(*p=='"'){
            p++;
            av[ac++]=p;
            while(*p&&*p!='"')p++;
            if(*p) *p++='\0';
        } else {
            av[ac++]=p;
            while(*p&&*p!=' ')p++;
            if(*p) *p++='\0';
        }
        if(ac>=MAX_ARGS)break;
    }
    av[ac]=0;
    if(ac==0)return;

    for(int i=0;cmds[i].name;i++){
        if(strcmp(av[0],cmds[i].name)==0){
            cmds[i].func(ac,av);
            return;
        }
    }
    kprint_color("  Unknown command. Type 'help'\n", VGA_RED);
}

void shell_run(void){
    char in[MAX_CMD_LEN];
    while(1){ shell_prompt(); keyboard_read_line(in,MAX_CMD_LEN); shell_execute(in); }
}
