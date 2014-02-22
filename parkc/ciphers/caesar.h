#ifndef CAESAR_H
#define CAESAR_H

#include <stdlib.h>
#include <string.h>
#include "../utilities/stringext.h"
#include "../utilities/constants.h"
#include "../utilities/osext.h"

char* caesar_encrypt(const char*, char);
char* caesar_decrypt(const char*, char);
#endif
