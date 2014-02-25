#include "ciphers_generators.h"

static char *caesar_text;
static char *caesar_keys;
static char *caesar_triangle_text;

static Keytext *caesar_generator() {
    static int counter = 0;
    if (counter == ALPHABET_LENGTH) {
        return NULL;
    }
    char *key = empty_string(1);
    key[0] = counter + 'a';
    if (counter > 0) {
        caesar_decrypt_par(caesar_text, 'b', caesar_text);
    }
    Keytext* keytext = (Keytext*) malloc(sizeof(Keytext));
    keytext->text = caesar_text;
    keytext->key = key;
    counter++;
    return keytext;
}

static Keytext *triangle_generator() {
    static int i = 0;
    if (caesar_keys[i] == '\0') {
        return NULL;
    }
    char *key = empty_string(1);
    key[0] = caesar_keys[i];
    caesar_decrypt_par(caesar_triangle_text, caesar_keys[i], caesar_triangle_text);
    Keytext* keytext = (Keytext*) malloc(sizeof(Keytext));
    keytext->text = caesar_triangle_text;
    keytext->key = key;
    i++;
    return keytext;
}

TextGenerator get_caesar_generator(const char* text) {
    caesar_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(caesar_text, text);
    return caesar_generator;
}

TextGenerator get_triangle_generator(const char* text, const char *keys) {
    caesar_triangle_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    caesar_keys = (char*) safe_malloc(sizeof(char) * (strlen(keys) + 1));
    strcpy(caesar_triangle_text, text);
    strcpy(caesar_keys, keys);
    return triangle_generator;
}
