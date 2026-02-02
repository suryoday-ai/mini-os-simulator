#include <stdio.h>
#include "include/memory.h"

#define TOTAL_MEMORY 1024   // MB

int used_memory = 0;

// Show memory status
void show_memory() {
    printf("\nTotal Memory : %d MB\n", TOTAL_MEMORY);
    printf("Used Memory  : %d MB\n", used_memory);
    printf("Free Memory  : %d MB\n\n", TOTAL_MEMORY - used_memory);
}

// Allocate memory
void alloc_memory() {
    int size;
    printf("Enter memory to allocate (MB): ");
    scanf("%d", &size);

    if (used_memory + size > TOTAL_MEMORY) {
        printf("Not enough memory available\n\n");
        return;
    }

    used_memory += size;
    printf("%d MB memory allocated successfully\n\n", size);
}

// Free memory
void free_memory() {
    int size;
    printf("Enter memory to free (MB): ");
    scanf("%d", &size);

    if (size > used_memory) {
        printf("Invalid free request\n\n");
        return;
    }

    used_memory -= size;
    printf("%d MB memory freed successfully\n\n", size);
}
//reset memory
void reset_memory() {
    used_memory = 0;
    printf("Memory reset successful\n");
}
