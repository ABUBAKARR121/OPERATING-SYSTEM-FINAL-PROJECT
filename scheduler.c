#include "scheduler.h"
#include "../../libc/stdio.h"
#include "../drivers/display/vga.h"
void scheduler_init(void){proc_init();kprint_color("[SCHED] RR+FCFS ready\n",VGA_GREEN);}
void scheduler_display(void){proc_list_all();}
