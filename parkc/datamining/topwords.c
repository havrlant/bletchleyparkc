#include "topwords.h"

StringArray* load_topwords(const char* lang) {
    int i = 0;
    char* path = topwords_file(lang);
    char* content = read_file(path);
    int words_count = char_count(content, ' ') + 1;
    char* pch;
    StringArray* sarray = create_string_array(words_count);
    sarray->items = (char**) safe_malloc(sizeof(char*) * words_count);
    for (pch = strtok(content, " "); pch != NULL; pch = strtok(NULL, " ")) {
        sarray->items[i++] = pch;
    }
    free(path);
    // content cannot be freed, because of strtok
    return sarray;
}

int words_occurences(StringArray* sarray, char* text) {
    int counter = 0;
    for (int i = 0; i < sarray->length; i++) {
        if (strstr(text, sarray->items[i]) != NULL) {
            counter++;
        }
    }
    return counter;
}
