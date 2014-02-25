#ifndef parkc_osext_h
#define parkc_osext_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
void *safe_malloc(size_t);
void *safe_calloc(size_t, size_t);

#endif
