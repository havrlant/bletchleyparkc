#include "substitution.h"

static char* switch_key(const char* key) {
    char* newkey = empty_string(ALPHABET_LENGTH);
    int i;
    for (i = 0; i < ALPHABET_LENGTH; i++) {
        newkey[key[i] - 'a'] = 'a' + i;
    }
    return newkey;
}

char* substitution_encrypt(const char* opentext, const char* key) {
    return replace_chars(opentext, key);
}

char* substitution_decrypt(const char* ciphertext, const char* key) {
    char* switched_key = switch_key(key);
    char* result = replace_chars(ciphertext, switched_key);
    free(switched_key);
    return result;
}
