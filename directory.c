#include <stdio.h>
#include <string.h>
#include "include/directory.h"

#define MAX_DIR 20
#define NAME_LEN 20

typedef struct {
    char name[NAME_LEN];
} Directory;

Directory dlist[MAX_DIR];
int dcount = 0;
char current_dir[50] = "root";

/* Create directory */
void mkdir_dir() {
    if (dcount >= MAX_DIR) {
        printf("Directory limit reached\n\n");
        return;
    }

    printf("Enter directory name: ");
    scanf("%s", dlist[dcount].name);

    dcount++;
    printf("Directory created successfully\n\n");
}

/* Remove directory */
void rmdir_dir() {
    char name[NAME_LEN];
    int index = -1;

    printf("Enter directory name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < dcount; i++) {
        if (strcmp(dlist[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Directory not found\n\n");
        return;
    }

    for (int i = index; i < dcount - 1; i++) {
        dlist[i] = dlist[i + 1];
    }

    dcount--;
    printf("Directory deleted successfully\n\n");
}

/* Change directory */
void cd_dir() {
    char name[NAME_LEN];

    printf("Enter directory name: ");
    scanf("%s", name);

    if (strcmp(name, "..") == 0) {
        strcpy(current_dir, "root");
        printf("Moved to root directory\n\n");
        return;
    }

    for (int i = 0; i < dcount; i++) {
        if (strcmp(dlist[i].name, name) == 0) {
            strcpy(current_dir, name);
            printf("Current directory: %s\n\n", current_dir);
            return;
        }
    }

    printf("Directory not found\n\n");
}

/* Print working directory */
void pwd_dir() {
    printf("Current directory: %s\n\n", current_dir);
}

/* List directories */
void ls_dir() {
    if (dcount == 0) {
        printf("No directories available\n\n");
        return;
    }

        printf("\nDirectories in %s:\n", current_dir);

    if (strcmp(current_dir, "root") == 0) {
    for (int i = 0; i < dcount; i++)
    printf("%s\n", dlist[i].name);
    } else {
    printf("(no sub directories)\n");
    }
    printf("\n");
    }
   /*directory reset function*/

void reset_directories() {
    dcount = 0;
    strcpy(current_dir, "root");
    printf("All directories cleared\n");
}
