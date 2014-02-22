#include "stringext.h"

char* empty_string(size_t length) {
    char* string = (char*) safe_malloc(sizeof(char) * (length + 1));
    string[length] = '\0';
    return string;
}

char* replace_chars(const char* text, const char* table) {
    char* newtext = empty_string(strlen(text));
    for (int i = 0; text[i]; ++i) {
        newtext[i] = table[text[i] - 'a'];
    }
    return newtext;
}

void replace_chars_par(const char* text, const char* table, char* newtext) {
    size_t i;
    for (i = 0; text[i]; ++i) {
        newtext[i] = table[text[i] - 'a'];
    }
    newtext[i] = '\0';
}

char* concat(const char* s1, const char* s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char* result = safe_malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

int char_count(const char* text, char character) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == character) {
            count++;
        }
    }
    return count;
}

StringArray* create_string_array(int length) {
    StringArray* sarray = (StringArray*)safe_malloc(sizeof(StringArray));
    sarray->length = length;
    return sarray;
}

char* normalize(const char* text) {
    char* newtext;
    int counter = 0, j = 0;
    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            counter++;
        }
    }
    newtext = empty_string(counter);
    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalnum(text[i])) {
            newtext[j++] = tolower(text[i]);
        }
    }
    return newtext;
}
