#include "vigenere.h"

static char encrypt_char(char letter, char key) {
    int temp = (int)(letter + (key - 'a'));
    return temp <= (int)'z' ? (char)temp : (char)(temp - ALPHABET_LENGTH);
}

static char decrypt_char(char letter, char key) {
    char temp = letter - (key - 'a');
    return temp >= 'a' ? temp : temp + (char)ALPHABET_LENGTH;
}

static char* vigenere(const char* opentext, const char* key, char (*shift)(char, char)) {
    char* ciphertext = empty_string(strlen(opentext));
    size_t keylen = strlen(key);
    int i;
    for (i = 0; opentext[i] != '\0'; i++) {
        ciphertext[i] = shift(opentext[i], key[i % keylen]);
    }
    return ciphertext;
}

char* vigenere_encrypt(const char* opentext, const char* key) {
    return vigenere(opentext, key, encrypt_char);
}

char* vigenere_decrypt(const char* ciphertext, const char* key) {
    return vigenere(ciphertext, key, decrypt_char);
}
