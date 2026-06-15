#ifndef PROCESS_H
#define PROCESS_H
#include "../core/types.h"
#define MAX_PROCESSES 16
#define PROC_NAME_LEN 32
typedef enum { PROC_READY=0, PROC_RUNNING=1, PROC_BLOCKED=2, PROC_TERMINATED=3 } process_state_t;
typedef struct { uint32_t pid; char name[PROC_NAME_LEN]; process_state_t state; uint32_t priority; uint32_t cpu_time; void (*entry_point)(void); } process_t;
void proc_init(void);
int proc_create(const char* name, void (*entry)(void), uint32_t priority);
void proc_list_all(void);
#endif
