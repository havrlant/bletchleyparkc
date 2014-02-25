#include "frequency.h"

static int hash_ngram(const char *text, int start, char length) {
    double hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += pow(ALPHABET_LENGTH, length - i - 1) * (text[start + i] - 'a');
    }
    return (int)hash_value;
}

static int *_ngrams_freq(const char *text, char n) {
    int *freq = zero_array(int, pow(ALPHABET_LENGTH, n));
    for (int i = 0; text[i] != '\0'; i++) {
        freq[hash_ngram(text, i, n)]++;
    }
    return freq;
}

static int *letters_freq(const char *text) {
    int *freq = zero_array(int, ALPHABET_LENGTH);
    for (int i = 0; text[i] != '\0'; i++) {
        freq[(int)(text[i] - 'a')]++;
    }
    return freq;
}

static double *parse_line(char *line, int length) {
    int arlength = (int)pow(ALPHABET_LENGTH, length);
    double *freq = array(double, arlength);
    char *pch;
    int i = 0;
    for (pch = strtok(line, " "); pch != NULL; pch = strtok (NULL, " ")) {
        freq[i++] = atof(pch);
    }
    return freq;
}

int *ngrams_occur(const char *text, char n) {
    int max_n = 3;
    if (n == 1) {
        return letters_freq(text);
    } else if (n >= 1 && n <= max_n) {
        return _ngrams_freq(text, n);
    } 
    fprintf(stderr, "Illegal argument value. n = %i, should be 1 <= n <= %i", n, max_n);
    exit(EXIT_FAILURE);    
}

double *ngrams_freq(const char *text, char n) {
    double text_length = (double)strlen(text);
    int *ocurences = ngrams_occur(text, n);
    int ngrams_count = (int)pow(ALPHABET_LENGTH, n);
    double *freq = zero_array(double, ngrams_count);
    for (int i = 0; i < ngrams_count; i++) {
        freq[i] = (ocurences[i] / (text_length - n + 1)) * 100;
    }
    free(ocurences);
    return freq;
}

double** load_frequencies(const char *lang) {
    char *path = frequencies_file(lang);
    char *content = read_file(path);
    double** result = array(double*, 2);
    char *temp[2];
    temp[0] = strtok(content, "\n");
    temp[1] = strtok(NULL, "\n");
    for (int i = 0; i < 2; i++) {
        result[i] = parse_line(temp[i], i + 1);
    }
    free(path);
    free(content);
    return result;
}
