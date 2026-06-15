#include "process.h"
#include "../../libc/string.h"
#include "../../libc/stdio.h"
#include "../drivers/display/vga.h"
static process_t procs[MAX_PROCESSES];
static int count=0;
void proc_init(void){memset(procs,0,sizeof(procs));count=0;proc_create("Kernel",0,0);proc_create("MemMgr",0,1);proc_create("FileSrv",0,1);proc_create("Shell",0,1);proc_create("Idle",0,0);kprint_color("[PROC] Scheduler ready (FCFS+RR)\n",VGA_GREEN);}
int proc_create(const char* n,void (*e)(void),uint32_t p){if(count>=MAX_PROCESSES)return-1;procs[count].pid=count+1;strncpy(procs[count].name,n,PROC_NAME_LEN-1);procs[count].state=(count==0)?PROC_RUNNING:PROC_READY;procs[count].priority=p;count++;return procs[count-1].pid;}
void proc_list_all(void){kprint("\n  PID  NAME           STATE\n");kprint("  ---------------------------\n");for(int i=0;i<count;i++){kprint("  ");kprint_int(procs[i].pid);kprint("   ");kprint(procs[i].name);kprint("            ");kprint(procs[i].state==PROC_RUNNING?"RUNNING":"READY");kprint("\n");}kprint("\n");}
