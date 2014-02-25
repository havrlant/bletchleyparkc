#ifndef parkc_ciphers_generators_h
#define parkc_ciphers_generators_h

#include "../ciphers/caesar.h"
#include "../ciphers/vigenere.h"
#include "../ciphers/substitution.h"
#include "../utilities/osext.h"
#include "../utilities/constants.h"
#include <string.h>

typedef enum {NEXT = 0, INITIALIZE = 1} GeneratorDriver;

typedef struct {
    char *text;
    const char *key;
} Keytext;

typedef Keytext *(*TextGenerator)();
typedef void (*Decrypt)(const char*, const char*, char*);

TextGenerator get_caesar_generator(const char*);
TextGenerator get_generator(const char *ciphertext, char**, size_t, Decrypt);

#endif
