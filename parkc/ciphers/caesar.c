#include "caesar.h"

static char* make_caesar_table(char key) {
    char* table = (char*) safe_malloc(sizeof(char) * ALPHABET_LENGTH);
    int temp;
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        temp = (int)key + i;
        table[i] = (char)(temp <= (int)'z' ? temp : temp - ALPHABET_LENGTH);
    }
    return table;
}

static char* make_caesar_dec_table(char key) {
    char* table = (char*) safe_malloc(sizeof(char) * ALPHABET_LENGTH);
    int temp;
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        temp = 2 * (int)'a' + i - (int)key;
        table[i] = (char)(temp >= (int)'a' ? temp : temp + ALPHABET_LENGTH);
    }
    return table;
}

void caesar_encrypt_par(const char* opentext, char key, char* ciphertext) {
    char* table = make_caesar_table(key);
    replace_chars_par(opentext, table, ciphertext);
    free(table);
}

void caesar_decrypt_par(const char* ciphertext, char key, char* opentext) {
    char* table = make_caesar_dec_table(key);
    replace_chars_par(ciphertext, table, opentext);
    free(table);
}

char* caesar_encrypt(const char* opentext, char key) {
    char* ciphertext = (char*) safe_malloc(sizeof(char) * (strlen(opentext) + 1));
    caesar_encrypt_par(opentext, key, ciphertext);
    return ciphertext;
}

char* caesar_decrypt(const char* ciphertext, char key) {
    char* opentext = (char*) safe_malloc(sizeof(char) * (strlen(ciphertext) + 1));
    caesar_decrypt_par(ciphertext, key, opentext);
    return opentext;
}
