#include "ciphers_generators.h"

static char *caesar_text;

static char **_keys;
static const char *_ciphertext;
static Decrypt _decrypt;
static size_t _n;

static Keytext caesar_generator(GeneratorDriver driver, int *inloop) {
    static int i;
    if (driver == INITIALIZE) {
        i = 0;
        *inloop = 1;
    }
    if (i == ALPHABET_LENGTH) {
        *inloop = 0;
        return (Keytext){.text="", .key=""};
    }
    char *key = empty_string(1);
    key[0] = i + 'a';
    if (i > 0) {
        caesar_decrypt_par(caesar_text, "b", caesar_text);
    }
    i++;
//    Keytext ktext;
//    ktext.text = caesar_text;
//    ktext.key = key;
//    return ktext;
    return (Keytext){.text=caesar_text, .key=key};
}

TextGenerator get_caesar_generator(const char *text) {
    caesar_text = (char*) safe_malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(caesar_text, text);
    return caesar_generator;
}

static Keytext cipher_generator(GeneratorDriver driver, int *inloop) {
    static int i;
    static char *opentext = NULL;
    if (driver == INITIALIZE) {
        *inloop = 1;
        free(opentext);
        i = 0;
        opentext = empty_string(strlen(_ciphertext));
    }
    
    if (i == _n) {
        *inloop = 0;
        return (Keytext){.text = "", .key=""};
    }
    
    if (strcmp(_keys[i], "?") == 0) {
        i++;
        return cipher_generator(NEXT, inloop);
    }
    
    _decrypt(_ciphertext, _keys[i], opentext);
    return (Keytext){.text = opentext, .key=_keys[i++]};
}

TextGenerator get_generator(const char *ciphertext, char **keys, size_t n, Decrypt decrypt) {
    _decrypt = decrypt;
    _keys = keys;
    _ciphertext = ciphertext;
    _n = n;
    return cipher_generator;
}
