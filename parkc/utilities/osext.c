#include "osext.h"

void* safe_malloc(size_t size) {
    void* memory = malloc(size);
    if (memory == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    return memory;
}
