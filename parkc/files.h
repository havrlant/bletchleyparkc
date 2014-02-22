//
//  files.h
//  parkc
//
//  Created by Lukáš Havrlant on 22.2.14.
//  Copyright (c) 2014 Lukáš Havrlant. All rights reserved.
//

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
