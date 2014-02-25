#include "vigenere_brute.h"

static char *every_n_char(const char* ciphertext, int start, int skip, char* output) {
    size_t length = strlen(ciphertext);
    int index = 0;
    for (int i = start; i < length; i += skip) {
        output[index++] = ciphertext[i];
    }
    output[index] = '\0';
//    printf("\n--------------\n%s\n", output);
    return output;
}

char *get_key(const char *ciphertext, const LangStats *stats, int keylen) {
    char *output = empty_string((strlen(ciphertext) / 2) + 1);
    char* key = empty_string(keylen);
    Keytext *current_key;
    for (int i = 0; i < keylen; i++) {
        every_n_char(ciphertext, i, keylen, output);
        current_key = triangle_attack(output, stats, 8, 1);
        key[i] = current_key != NULL ? current_key->key[0] : 'a';
    }
    free(output);
    free(current_key);
    return key;
}

Keytext *vigenere_brute(const char *ciphertext, const LangStats *stats) {
    char *key;
    for (int i = 2; i < 10; i++) {
        key = get_key(ciphertext, stats, i);
        printf("Vysledek: %s\n", key);
    }
    return NULL;
}
