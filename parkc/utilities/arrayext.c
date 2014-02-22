#include "arrayext.h"

int* zero_array(size_t length) {
    int* array = (int*) safe_malloc(length);
    unsigned int i;
    for (i = 0; i < length; i++) {
        array[i] = 0;
    }
    return array;
}
