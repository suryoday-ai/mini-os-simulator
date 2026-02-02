#include <stdio.h>
#include <string.h>

#include "include/file.h"
#include "include/process.h"
#include "include/directory.h"   // for current_dir

#define MAX_FILES 20


File flist[MAX_FILES];
int fcount = 0;

/* ---------------- CREATE FILE ---------------- */
void create_file() {
    if (fcount >= MAX_FILES) {
        printf("File limit reached\n\n");
        return;
    }

    printf("Enter file name: ");
    scanf("%s", flist[fcount].name);

    // link file to current directory
    strcpy(flist[fcount].directory, current_dir);

    printf("Enter file size (KB): ");
    scanf("%d", &flist[fcount].size);

    flist[fcount].mem_used = (flist[fcount].size / 1024) + 1;

    if (used_memory + flist[fcount].mem_used > TOTAL_MEMORY) {
        printf("Not enough memory for file\n\n");
        return;
    }

    used_memory += flist[fcount].mem_used;
    fcount++;

    printf("File created in directory '%s'\n", current_dir);
    printf("%d MB memory allocated\n\n", flist[fcount - 1].mem_used);
}

/* ---------------- LIST FILES ---------------- */
void list_files() {
    int found = 0;

    if (fcount == 0) {
        printf("No files available\n\n");
        return;
    }

    printf("\nFiles in directory: %s\n", current_dir);
    printf("NAME\tSIZE(KB)\tMEM(MB)\n");

    for (int i = 0; i < fcount; i++) {
        if (strcmp(flist[i].directory, current_dir) == 0) {
            printf("%s\t%d\t\t%d\n",
                   flist[i].name,
                   flist[i].size,
                   flist[i].mem_used);
            found = 1;
        }
    }

    if (!found) {
        printf("No files in this directory\n");
    }

    printf("\n");
}

/* ---------------- DELETE FILE ---------------- */
void delete_file() {
    char fname[20];
    int index = -1;

    printf("Enter file name to delete: ");
    scanf("%s", fname);

    for (int i = 0; i < fcount; i++) {
        if (strcmp(flist[i].name, fname) == 0 &&
            strcmp(flist[i].directory, current_dir) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("File not found in current directory\n\n");
        return;
    }

    if (used_memory >= flist[index].mem_used)
        used_memory -= flist[index].mem_used;

    for (int i = index; i < fcount - 1; i++) {
        flist[i] = flist[i + 1];
    }

    fcount--;
    printf("File deleted from '%s', memory freed\n\n", current_dir);
}

/*reset*/
void reset_files() {
    fcount = 0;
    printf("All files cleared\n");
}
