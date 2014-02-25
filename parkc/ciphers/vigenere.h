#ifndef parkc_vigenere_h
#define parkc_vigenere_h

#include <stdlib.h>
#include <string.h>
#include "../utilities/stringext.h"
#include "../utilities/constants.h"

char* vigenere_encrypt(const char*, const char*);
char* vigenere_decrypt(const char*, const char*);
char* vigenere_decrypt_par(const char*, const char*, char*);
char* vigenere_encrypt_par(const char*, const char*, char*);

#endif
