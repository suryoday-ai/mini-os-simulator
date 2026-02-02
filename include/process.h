#ifndef PROCESS_H
#define PROCESS_H

#define TOTAL_MEMORY 1024
extern int used_memory;

/* process functions */
void show_processes();
void create_process();
void kill_process();
void run_process();
void wait_process();
void resume_process();
void reset_processes();


/* scheduling */
void round_robin();
void fcfs_scheduling();
void priority_scheduling();
void sjf_scheduling();

/* memory */
void show_memory();
void alloc_memory();
void free_memory();

/* reset */ 
void reset_memory();
void reset_processes();


#endif
