#include "ciphers_generators.h"

static char *caesar_text;
static char **caesar_keys;
static char *caesar_triangle_text;

static char **_keys;
static const char *_ciphertext;
static Decrypt _decrypt;
static size_t _n;

static Keytext *caesar_generator(GeneratorDriver driver) {
    static int i;
    if (driver == INITIALIZE) {
        i = 0;
    }
    if (i == ALPHABET_LENGTH) {
        return NULL;
    }
    char *key = empty_string(1);
    key[0] = i + 'a';
    if (i > 0) {
        caesar_decrypt_par(caesar_text, "b", caesar_text);
    }
    Keytext *keytext = (Keytext*) malloc(sizeof(Keytext));
    keytext->text = caesar_text;
    keytext->key = key;
    i++;
    return keytext;
}

static Keytext *triangle_generator(GeneratorDriver driver) {
    static int i;
    if (driver == INITIALIZE) {
        i = 0;
    }
    if (caesar_keys[i] == NULL || caesar_keys[i][0] == '?') {
        return NULL;
    }
    char *key = empty_string(1);
    key[0] = caesar_keys[i][0];
//    caesar_decrypt_par(caesar_triangle_text, caesar_keys[i], caesar_triangle_text);
    Keytext *keytext = (Keytext*) malloc(sizeof(Keytext));
    keytext->text = caesar_encrypt(caesar_triangle_text, caesar_keys[i]);
    keytext->key = key;
    i++;
    return keytext;
}

TextGenerator get_caesar_generator(const char *text) {
    caesar_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(caesar_text, text);
    return caesar_generator;
}

TextGenerator get_triangle_generator(const char *text, const char *keys) {
    caesar_triangle_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    caesar_keys = (char**) safe_malloc(sizeof(char*) * (strlen(keys) + 1));
    int i;
    for (i = 0; keys[i] != '\0'; i++) {
        caesar_keys[i] = empty_string(1);
        caesar_keys[i][0] = keys[i];
        caesar_keys[i][1] = '\0';
    }
    caesar_keys[i] = NULL;
    strcpy(caesar_triangle_text, text);
    return triangle_generator;
}

static Keytext *cipher_generator(GeneratorDriver driver) {
    static int i;
    static char *opentext;
    if (driver == INITIALIZE) {
        i = 0;
        opentext = empty_string(strlen(_ciphertext));
    }
    
    if (i == _n) {
        return NULL;
    }
    
    _decrypt(_ciphertext, _keys[i], opentext);
    Keytext *keytext = (Keytext*) malloc(sizeof(Keytext));
    keytext->text = opentext;
    keytext->key = _keys[i];
    i++;
    return keytext;
}

TextGenerator get_generator(const char *ciphertext, char **keys, size_t n, Decrypt decrypt) {
    _decrypt = decrypt;
    _keys = keys;
    _ciphertext = ciphertext;
    _n = n;
    return cipher_generator;
}
