#include "ciphers_generators.h"

static char *caesar_text;
static char *caesar_keys;
static char *caesar_triangle_text;
static int i_triangle;
static int i_caesar;

static Keytext *caesar_generator() {
    if (i_caesar == ALPHABET_LENGTH) {
        return NULL;
    }
    char *key = empty_string(1);
    key[0] = i_caesar + 'a';
    if (i_caesar > 0) {
        caesar_decrypt_par(caesar_text, 'b', caesar_text);
    }
    Keytext *keytext = (Keytext*) malloc(sizeof(Keytext));
    keytext->text = caesar_text;
    keytext->key = key;
    i_caesar++;
    return keytext;
}

static Keytext *triangle_generator() {
    if (caesar_keys[i_triangle] == '\0') {
        return NULL;
    }
    char *key = empty_string(1);
    key[0] = caesar_keys[i_triangle];
    caesar_decrypt_par(caesar_triangle_text, caesar_keys[i_triangle], caesar_triangle_text);
    Keytext *keytext = (Keytext*) malloc(sizeof(Keytext));
    keytext->text = caesar_triangle_text;
    keytext->key = key;
    i_triangle++;
    return keytext;
}

TextGenerator get_caesar_generator(const char *text) {
    caesar_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(caesar_text, text);
    i_caesar = 0;
    return caesar_generator;
}

TextGenerator get_triangle_generator(const char *text, const char *keys) {
    caesar_triangle_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    caesar_keys = (char*) safe_malloc(sizeof(char) * (strlen(keys) + 1));
    strcpy(caesar_triangle_text, text);
    strcpy(caesar_keys, keys);
    i_triangle = 0;
    return triangle_generator;
}
