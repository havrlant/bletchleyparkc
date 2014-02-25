#include "osext.h"

void *error_check(void *memory) {
    if (memory == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    return memory;
}

void *safe_malloc(size_t size) {
    return error_check(malloc(size));
}

void *safe_calloc(size_t num, size_t size) {
    return error_check(calloc(num, size));
}
