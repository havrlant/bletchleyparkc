#include "ospath.h"

char *topwords_file(const char *lang) {
    char *temp = concat(APP_FOLDER, lang);
    char *result = concat(temp, "/topwords.txt");
    free(temp);
    return result;
}

char *frequencies_file(const char *lang) {
    char *temp = concat(APP_FOLDER, lang);
    char *result = concat(temp, "/frequencies.txt");
    free(temp);
    return result;
}
