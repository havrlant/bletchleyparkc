#include "frequency.h"

static int hash_ngram(const char* text, int start, char length) {
    double hash_value = 0;
    int i;
    for (i = 0; i < length; i++) {
        hash_value += pow(ALPHABET_LENGTH, length - i - 1) * (text[start + i] - 'a');
    }
    return (int)hash_value;
}


static int* _ngrams_freq(const char* text, char n) {
    int* freq = zero_array((size_t)pow(ALPHABET_LENGTH, n)); 
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        freq[hash_ngram(text, i, n)]++;
    }
    return freq;
}

static int* letters_freq(const char* text) {
    int* freq = zero_array(ALPHABET_LENGTH);
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        freq[(int)(text[i] - 'a')]++;
    }
    return freq;
}

int* ngrams_freq(const char* text, char n) {
    int max_n = 4;
    if (n == 1) {
        return letters_freq(text);
    } else if (n >= 1 && n <= max_n) {
        return _ngrams_freq(text, n);
    } 
    fprintf(stderr, "Illegal argument value. n = %i, should be 1 <= n <= %i", n, max_n);
    exit(EXIT_FAILURE);    
}

double* load_frequencies(const char* lang) {
    char* path = frequencies_file(lang);
    double* freq = (double*) safe_malloc(sizeof(double) * ALPHABET_LENGTH);
    char* content = read_file(path);
    char* pch;
    int i = 0;
    for (pch = strtok(content, " "); pch != NULL; pch = strtok (NULL, " ")) {
        freq[i++] = atof(pch);
    }
    free(path);
    free(content);
    return freq;
}
