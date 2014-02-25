#include "ciphers_generators.h"

static char *caesar_text;

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

TextGenerator get_caesar_generator(const char *text) {
    caesar_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(caesar_text, text);
    return caesar_generator;
}

static Keytext *cipher_generator(GeneratorDriver driver) {
    static int i;
    static char *opentext = NULL;
    if (driver == INITIALIZE) {
        free(opentext);
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
