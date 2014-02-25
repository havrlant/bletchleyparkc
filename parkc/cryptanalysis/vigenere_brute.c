#include "vigenere_brute.h"

static char *every_n_char(const char* ciphertext, int start, int skip, char* output) {
    size_t length = strlen(ciphertext);
    int index = 0;
    for (int i = start; i < length; i += skip) {
        output[index++] = ciphertext[i];
    }
    output[index] = '\0';
    return output;
}

char *get_key(const char *ciphertext, const LangStats *stats, int keylen) {
    char *output = empty_string((strlen(ciphertext) / 2) + 1);
    char* key = empty_string(keylen);
    Keytext *temp;
    for (int i = 0; i < keylen; i++) {
        every_n_char(ciphertext, i, keylen, output);
        temp = triangle_attack(output, stats, 8, 1);
        key[i] = temp->key[0];
    }
    return key;
}

Keytext *vigenere_brute(const char *ciphertext, const LangStats *stats) {
    char *key = get_key(ciphertext, stats, 5);
    printf("Vysledek: %s\n\n", key);
    return NULL;
}
