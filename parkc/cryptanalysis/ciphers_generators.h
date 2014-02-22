#ifndef parkc_ciphers_generators_h
#define parkc_ciphers_generators_h

#include "../ciphers/caesar.h"
#include "../ciphers/vigenere.h"
#include "../ciphers/substitution.h"
#include "../utilities/osext.h"
#include "../utilities/constants.h"
#include <string.h>

typedef struct {
    char* text;
    char* key;
} Ciphertext;

typedef Ciphertext* (*TextGenerator)();

TextGenerator get_caesar_generator(const char*);

#endif
