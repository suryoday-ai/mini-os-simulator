#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h>   // Windows directory functions

#include "include/process.h"
#include "include/memory.h"
#include "include/file.h"
#include "include/directory.h"

void shell() {
    char command[50];
    char text[200];
    char path[260];
    int a, b;
    char op;

    printf("Launching Mini OS Shell...\n");
    printf("Welcome to Mini OS Shell\n");
    printf("Type 'help' to see available commands\n\n");

    while (1) {
        printf("MiniOS> ");
        scanf("%s", command);

        /* ================= HELP ================= */
        if (strcmp(command, "help") == 0) {
            printf("\nAvailable commands:\n");
            printf("help           - Show help menu\n");
            printf("clear / cls    - Clear screen\n");
            printf("about          - About Mini OS\n");
            printf("time           - Show system time\n");
            printf("date           - Show system date\n");
            printf("whoami         - Show current user\n\n");

            printf("ps / pl        - Process list\n");
            printf("createp        - Create new process\n");
            printf("killp          - Kill a process\n");
            printf("runp           - Run process (basic priority)\n");
            printf("waitp          - Move process to waiting\n");
            printf("resumep        - Resume waiting process\n\n");

            printf("fcfs           - FCFS CPU Scheduling\n");
            printf("priority       - Priority CPU Scheduling\n");
            printf("sjf            - Shortest Job First Scheduling\n");
            printf("rr             - Round Robin CPU Scheduling\n\n");

            printf("mem            - Show memory status\n");
            printf("alloc          - Allocate memory\n");
            printf("free           - Free memory\n\n");

            printf("touch          - Create file\n");
            printf("ls             - List files\n");
            printf("rm             - Delete file\n\n");

            printf("mkdir          - Create MiniOS directory\n");
            printf("rmdir          - Delete MiniOS directory\n");
            printf("cd             - Change MiniOS directory\n");
            printf("pwd            - Show MiniOS directory\n");
            printf("lsd            - List MiniOS directories\n\n");

            printf("cdw            - Change Windows directory\n");
            printf("pwdw           - Show Windows directory\n\n");
            printf("echo           - Print text\n");
            printf("calc           - Simple calculator (a + b)\n\n");
            printf("color green     - change text color to green\n");
            printf("color white     - change text color to white\n\n");



            printf("restart        - Restart shell\n");
            printf("reboot         - Reboot Mini OS\n");
            printf("logout         - Logout user\n");
            printf("shutdown       - Shutdown Mini OS\n");
            printf("exit           - Exit shell\n\n");
        }

        /* ================= BASIC ================= */
        else if (strcmp(command, "clear") == 0 || strcmp(command, "cls") == 0) {
            system("cls");
        }
        else if (strcmp(command, "about") == 0) {
            printf("\nMini Operating System Simulator\n");
            printf("Developed in C Language\n");
            printf("Command Driven Shell\n\n");
        }
        else if (strcmp(command, "time") == 0) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char buffer[20];

        strftime(buffer, sizeof(buffer), "%I:%M:%S %p", &tm);
        printf("Current Time: %s\n", buffer);
        }
        else if (strcmp(command, "date") == 0) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char buffer[40];
            strftime(buffer,sizeof(buffer),"%a %b %d %Y",&tm);
            printf("Current Date: %s\n",buffer);
        }
        else if (strcmp(command, "whoami") == 0) {
            printf("User: admin\n\n");
        }

        /* ================= PROCESS ================= */
        else if (strcmp(command, "ps") == 0 || strcmp(command, "pl") == 0) {
            show_processes();
        }
        else if (strcmp(command, "createp") == 0) {
            create_process();
        }
        else if (strcmp(command, "killp") == 0) {
            kill_process();
        }
        else if (strcmp(command, "runp") == 0) {
            run_process();
        }
        else if (strcmp(command, "waitp") == 0) {
            wait_process();
        }
        else if (strcmp(command, "resumep") == 0) {
            resume_process();
        }

        /* ================= MEMORY ================= */
        else if (strcmp(command, "mem") == 0) {
            show_memory();
        }
        else if (strcmp(command, "alloc") == 0) {
            alloc_memory();
        }
        else if (strcmp(command, "free") == 0) {
            free_memory();
        }

        /* ================= FILE ================= */
        else if (strcmp(command, "touch") == 0) {
            create_file();
        }
        else if (strcmp(command, "ls") == 0) {
            list_files();
        }
        else if (strcmp(command, "rm") == 0) {
            delete_file();
        }

        /* ================= CPU SCHEDULING ================= */
        else if (strcmp(command, "rr") == 0) {
            round_robin();
        }
        else if (strcmp(command, "fcfs") == 0) {
            fcfs_scheduling();
        }
        else if (strcmp(command, "priority") == 0) {
            priority_scheduling();
        }
        else if (strcmp(command, "sjf") == 0) {
            sjf_scheduling();
        }

        /* ================= DIRECTORY (MiniOS) ================= */
        else if (strcmp(command, "mkdir") == 0) {
            mkdir_dir();
        }
        else if (strcmp(command, "rmdir") == 0) {
            rmdir_dir();
        }
        else if (strcmp(command, "cd") == 0) {
            cd_dir();
        }
        else if (strcmp(command, "pwd") == 0) {
            pwd_dir();
        }
        else if (strcmp(command, "lsd") == 0) {
            ls_dir();
        }

        /* ================= DIRECTORY (WINDOWS) ================= */
        else if (strcmp(command, "cdw") == 0) {
            char folder[100];
            scanf("%s", folder);
            if (_chdir(folder) == 0)
                printf("Windows directory changed\n\n");
            else
                printf("Directory not found\n\n");
        }
        else if (strcmp(command, "pwdw") == 0) {
            if (_getcwd(path, sizeof(path)) != NULL)
                printf("Windows Directory: %s\n\n", path);
            else
                printf("Error getting directory\n\n");
        }

        /* ================= text print ================= */
        else if (strcmp(command, "echo") == 0) {
            getchar();
            printf("Enter text: ");
            fgets(text, sizeof(text), stdin);
            printf("%s\n", text);
        }
        else if (strcmp(command, "calc") == 0) {
            printf("Enter expression (a + b): ");
            scanf("%d %c %d", &a, &op, &b);

            if (op == '+') printf("Result: %d\n\n", a + b);
            else if (op == '-') printf("Result: %d\n\n", a - b);
            else if (op == '*') printf("Result: %d\n\n", a * b);
            else if (op == '/') printf("Result: %d\n\n", a / b);
            else printf("Invalid operator\n\n");
        }
            //text color 
            else if (strcmp(command, "color") == 0) {
            char c[10];
            scanf("%s", c);

            if (strcmp(c, "green") == 0) {
            system("color 0A");   // Green text
            }
            else if (strcmp(c, "white") == 0) {
            system("color 07");   // White text
            }
            else {
            printf("Usage: color green | color white\n");
            }
            }


        /* ================= EXIT ================= */
        else if (strcmp(command, "restart") == 0) {
        printf("Restarting Mini OS...\n\n");

        reset_processes();
        reset_memory();
        reset_files();
        reset_directories();

        printf("System restarted successfully\n\n");
        continue;
        }


        else if (strcmp(command, "reboot") == 0) {
            printf("Rebooting Mini OS...\n\n");
            continue;
        }
        else if (strcmp(command, "logout") == 0) {
            printf("Logging out...\n");
            break;
        }
        else if (strcmp(command, "shutdown") == 0) {
            printf("System shutting down...\n");
            exit(0);
        }
        else if (strcmp(command, "exit") == 0) {
            printf("Exiting Mini OS...\n");
            break;
        }

        /* ================= UNKNOWN ================= */
        else {
            printf("Unknown command: %s\n", command);
            printf("Type 'help' for list\n\n");
        }
    }
}
