#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H
#include <stdlib.h>
#include "../utilities/stringext.h"
#include "../utilities/constants.h"

char* substitution_encrypt(const char*, const char*);
char* substitution_decrypt(const char*, const char*);
#endif
