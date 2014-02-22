#include "ciphers_generators.h"

char *caesar_text;

static Ciphertext *caesar_generator() {
    static int counter = 0;
    if (counter == ALPHABET_LENGTH) {
        return NULL;
    }
    char *key = empty_string(1);
    key[0] = counter + 'a';
    caesar_decrypt_par(caesar_text, 'b', caesar_text);
    Ciphertext* ctext = (Ciphertext*) malloc(sizeof(Ciphertext));
    ctext->text = caesar_text;
    ctext->key = key;
    counter++;
    return ctext;
}

TextGenerator get_caesar_generator(const char* text) {
    caesar_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(caesar_text, text);
    return caesar_generator;
}
