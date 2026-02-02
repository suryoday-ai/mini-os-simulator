#include <stdio.h>
#include <string.h>
#include "include/process.h"

#define MAX_PROCESS 10

typedef struct {
    int pid;
    char name[20];
    int priority;
    int burst_time;
    int memory;
    char state[20];   // READY, RUNNING, WAITING, TERMINATED
} Process;

Process plist[MAX_PROCESS];
int pcount = 0;
int next_pid = 1;

/* ---------------- PROCESS FUNCTIONS ---------------- */

void show_processes() {
    if (pcount == 0) {
        printf("\nNo processes available\n\n");
        return;
    }

    printf("\nPID\tNAME\tBURST\tPRIORITY\tSTATE\n");
    for (int i = 0; i < pcount; i++) {
        printf("%d\t%-6s\t%d\t%d\t\t%s\n",
               plist[i].pid,
               plist[i].name,
               plist[i].burst_time,
               plist[i].priority,
               plist[i].state);
    }
    printf("\n");
}

void create_process() {
    if (pcount >= MAX_PROCESS) {
        printf("Process limit reached\n\n");
        return;
    }

    plist[pcount].pid = next_pid++;

    printf("Enter process name: ");
    scanf("%s", plist[pcount].name);

    printf("Enter priority (1-10): ");
    scanf("%d", &plist[pcount].priority);

    printf("Enter CPU burst time: ");
    scanf("%d", &plist[pcount].burst_time);

    printf("Enter memory required (MB): ");
    scanf("%d", &plist[pcount].memory);

    strcpy(plist[pcount].state, "READY");
    pcount++;

    printf("Process created successfully (READY)\n\n");
}

/* ---------------- BASIC PRIORITY RUN (EXISTING LOGIC) ---------------- */
void run_process() {
    int maxIndex = -1, maxPriority = -1;

    for (int i = 0; i < pcount; i++) {
        if (strcmp(plist[i].state, "READY") == 0 &&
            plist[i].priority > maxPriority) {

            maxPriority = plist[i].priority;
            maxIndex = i;
        }
    }

    if (maxIndex == -1) {
        printf("No READY process found\n\n");
        return;
    }

    strcpy(plist[maxIndex].state, "RUNNING");

    printf("Process %d (%s) is RUNNING\n\n",
           plist[maxIndex].pid,
           plist[maxIndex].name);
}

/* ---------------- CPU SCHEDULING ---------------- */

/* FCFS */
void fcfs_scheduling() {
    int time = 0;

    if (pcount == 0) {
        printf("No processes available\n\n");
        return;
    }

    printf("\n--- FCFS Scheduling ---\n");
    printf("PID\tBURST\tSTART\tEND\n");

    for (int i = 0; i < pcount; i++) {
        printf("P%d\t%d\t%d\t%d\n",
               plist[i].pid,
               plist[i].burst_time,
               time,
               time + plist[i].burst_time);

        time += plist[i].burst_time;
    }
    printf("\n");
}

/* PRIORITY SCHEDULING */
void priority_scheduling() {
    Process temp;

    for (int i = 0; i < pcount - 1; i++) {
        for (int j = i + 1; j < pcount; j++) {
            if (plist[i].priority < plist[j].priority) {
                temp = plist[i];
                plist[i] = plist[j];
                plist[j] = temp;
            }
        }
    }

    int time = 0;
    printf("\n--- Priority Scheduling ---\n");
    printf("PID\tPRIORITY\tSTART\tEND\n");

    for (int i = 0; i < pcount; i++) {
        printf("P%d\t%d\t\t%d\t%d\n",
               plist[i].pid,
               plist[i].priority,
               time,
               time + plist[i].burst_time);

        time += plist[i].burst_time;
    }
    printf("\n");
}

/* SJF */
void sjf_scheduling() {
    Process temp;

    for (int i = 0; i < pcount - 1; i++) {
        for (int j = i + 1; j < pcount; j++) {
            if (plist[i].burst_time > plist[j].burst_time) {
                temp = plist[i];
                plist[i] = plist[j];
                plist[j] = temp;
            }
        }
    }

    int time = 0;
    printf("\n--- SJF Scheduling ---\n");
    printf("PID\tBURST\tSTART\tEND\n");

    for (int i = 0; i < pcount; i++) {
        printf("P%d\t%d\t%d\t%d\n",
               plist[i].pid,
               plist[i].burst_time,
               time,
               time + plist[i].burst_time);

        time += plist[i].burst_time;
    }
    printf("\n");
}

/* ROUND ROBIN (UNCHANGED) */
void round_robin() {
    int time_quantum;
    int remaining[MAX_PROCESS];
    int completed = 0;
    int time = 0;

    if (pcount == 0) {
        printf("No processes available\n\n");
        return;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    for (int i = 0; i < pcount; i++) {
        remaining[i] = plist[i].burst_time;
        strcpy(plist[i].state, "READY");
    }

    printf("\n--- Round Robin Scheduling ---\n");

    while (completed < pcount) {
        for (int i = 0; i < pcount; i++) {
            if (remaining[i] > 0) {
                strcpy(plist[i].state, "RUNNING");

                if (remaining[i] > time_quantum) {
                    printf("Process %s running for %d units\n",
                           plist[i].name, time_quantum);

                    remaining[i] -= time_quantum;
                    time += time_quantum;
                    strcpy(plist[i].state, "READY");
                } else {
                    printf("Process %s running for %d units (COMPLETED)\n",
                           plist[i].name, remaining[i]);

                    time += remaining[i];
                    remaining[i] = 0;
                    completed++;
                    strcpy(plist[i].state, "TERMINATED");
                }
            }
        }
    }

    printf("\nAll processes completed in %d time units\n\n", time);
}
/* ---------------- PROCESS CONTROL ---------------- */

void kill_process() {
    int pid, index = -1;

    printf("Enter PID to kill: ");
    scanf("%d", &pid);

    for (int i = 0; i < pcount; i++) {
        if (plist[i].pid == pid) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Process not found\n\n");
        return;
    }

    for (int i = index; i < pcount - 1; i++) {
        plist[i] = plist[i + 1];
    }

    pcount--;
    printf("Process %d TERMINATED\n\n", pid);
}

void wait_process() {
    int pid;
    printf("Enter PID to wait: ");
    scanf("%d", &pid);

    for (int i = 0; i < pcount; i++) {
        if (plist[i].pid == pid) {
            strcpy(plist[i].state, "WAITING");
            printf("Process %d moved to WAITING\n\n", pid);
            return;
        }
    }

    printf("Process not found\n\n");
}

void resume_process() {
    int pid;
    printf("Enter PID to resume: ");
    scanf("%d", &pid);

    for (int i = 0; i < pcount; i++) {
        if (plist[i].pid == pid &&
            strcmp(plist[i].state, "WAITING") == 0) {

            strcpy(plist[i].state, "READY");
            printf("Process %d resumed\n\n", pid);
            return;
        }
    }


    printf("Invalid PID or process not in WAITING state\n\n");
}
   /* ---------------- RESET PROCESS LIST ---------------- */

void reset_processes() {
    pcount = 0;
    next_pid = 1;
    printf("All processes cleared\n");
}

