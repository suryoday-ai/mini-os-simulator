#include <stdio.h>
#include <stdlib.h>

void shell();


int main() {
printf("MiniOS v1.0\n");
printf("Booting system...\n");
printf("Loading modules...\n");
printf("  Shell...........[OK]\n");
printf("  Process.........[OK]\n");
printf("  Scheduler.......[OK]\n");
printf("  Memory..........[OK]\n");
printf("  Filesystem......[OK]\n");
printf("System Ready.\n\n");

    shell();
    return 0;
}




