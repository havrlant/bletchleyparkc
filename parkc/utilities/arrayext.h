#ifndef parkc_arrayext_h
#define parkc_arrayext_h

#include <stdlib.h>
#include "osext.h"
#define zero_array(type, length) (type*)safe_calloc((size_t)(length), sizeof(type));

#endif
