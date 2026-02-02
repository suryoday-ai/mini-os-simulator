#ifndef FILE_H
#define FILE_H

// File structure 
typedef struct {
    char name[20];
    char directory[50];   // directory linking
    int size;             // KB
    int mem_used;         // MB
} File;

/* file functions */
void create_file();
void list_files();
void delete_file();
void reset_files();


#endif
