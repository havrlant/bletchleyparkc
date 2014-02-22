#ifndef parkc_stringext_h
#define parkc_stringext_h

#include <stdlib.h>
#include <string.h>
#include "osext.h"

typedef struct {
    char** items;
    int length;
} StringArray;

char* replace_chars(const char*, const char*);
void replace_chars_par(const char*, const char*, char*);
char* empty_string(size_t);
char* concat(const char*, const char*);
int char_count(const char*, char);
StringArray* create_string_array(int);

#endif
