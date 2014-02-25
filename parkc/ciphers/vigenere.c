#include "vigenere.h"

static char encrypt_char(char letter, char key) {
    int temp = (int)(letter + (key - 'a'));
    return temp <= (int)'z' ? (char)temp : (char)(temp - ALPHABET_LENGTH);
}

static char decrypt_char(char letter, char key) {
    char temp = letter - (key - 'a');
    return temp >= 'a' ? temp : temp + (char)ALPHABET_LENGTH;
}

static char* vigenere(const char* opentext, const char* key, char (*shift)(char, char), char* text) {
    size_t keylen = strlen(key);
    for (size_t i = 0; opentext[i] != '\0'; i++) {
        text[i] = shift(opentext[i], key[i % keylen]);
    }
    return text;
}

char* vigenere_encrypt_par(const char *opentext, const char *key, char *ciphertext) {
    return vigenere(opentext, key, encrypt_char, ciphertext);
}

char* vigenere_decrypt_par(const char *opentext, const char *key, char *ciphertext) {
    return vigenere(opentext, key, decrypt_char, ciphertext);
}

char* vigenere_encrypt(const char* opentext, const char* key) {
    char* text = empty_string(strlen(opentext));
    return vigenere_encrypt_par(opentext, key, text);
}

char* vigenere_decrypt(const char* opentext, const char* key) {
    char* text = empty_string(strlen(opentext));
    return vigenere_decrypt_par(opentext, key, text);
}
