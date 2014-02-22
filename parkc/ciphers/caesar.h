#ifndef parkc_caesar_h
#define parkc_caesar_h

#include <stdlib.h>
#include <string.h>
#include "../utilities/stringext.h"
#include "../utilities/constants.h"
#include "../utilities/osext.h"

void caesar_encrypt_par(const char*, char, char*);
void caesar_decrypt_par(const char*, char, char*);
char* caesar_encrypt(const char*, char);
char* caesar_decrypt(const char*, char);

#endif
