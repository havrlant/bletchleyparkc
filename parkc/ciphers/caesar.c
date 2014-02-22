#include "caesar.h"

static char* make_caesar_table(char key) {
    char* table = (char*) safe_malloc(sizeof(char) * ALPHABET_LENGTH);
    int temp;
    int i;
    for (i = 0; i < ALPHABET_LENGTH; ++i) {
        temp = (int)key + i;
        table[i] = (char)(temp <= (int)'z' ? temp : temp - ALPHABET_LENGTH);
    }
    return table;
}

static char* make_caesar_dec_table(char key) {
    char* table = (char*) safe_malloc(sizeof(char) * ALPHABET_LENGTH);
    int temp;
    int i;
    for (i = 0; i < ALPHABET_LENGTH; ++i) {
        temp = 2 * (int)'a' + i - (int)key;
        table[i] = (char)(temp >= (int)'a' ? temp : temp + ALPHABET_LENGTH);
    }
    return table;
}

char* caesar_encrypt(const char* opentext, char key) {
    char* table = make_caesar_table(key);
    char* result = replace_chars(opentext, table);
    free(table);
    return result;
} 

char* caesar_decrypt(const char* opentext, char key) {
    char* table = make_caesar_dec_table(key);
    char* result = replace_chars(opentext, table);
    free(table);
    return result;
}
