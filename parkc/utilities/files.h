#ifndef parkc_files_h
#define parkc_files_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef enum {ROOT, SRC, DATA} Dir_types;
size_t get_file_size(const char*);
char* read_file(const char*);
char* get_path(Dir_types);

#endif
