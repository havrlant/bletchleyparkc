#include "statitics.h"

double deviation(double* arr1, double* arr2, size_t length) {
    double deviation = 0;
    for (size_t i = 0; i < length; i++) {
        deviation += pow(arr1[i] - arr2[i], 2);
    }
    return deviation;
}

double similarity(char* text, LangStats* stats) {
    double sim = 0;
    double dev;
    double *freq;
    for (int i = 0; i < NGRAMS_COUNT; i++) {
        freq = ngrams_freq(text, i + 1);
        dev = deviation(freq, stats->ngrams[i], pow(ALPHABET_LENGTH, i + 1));
        sim += (dev / (i + 1));
    }
    free(freq);
    return sim;
}

LangStats *create_stats(double** ngrams, StringArray *topwords) {
    LangStats *stats = (LangStats*)malloc(sizeof(LangStats));
    stats->ngrams = ngrams;
    stats->topwords = topwords;
    return stats;
}

Ciphertext *best_match(Ciphertext* (*generator)(), LangStats *stats) {
    Ciphertext *temp, *result = NULL;
    double sim = -1, tempsim;
    for (temp = generator(); temp != NULL; temp = generator()) {
        tempsim = similarity(temp->text, stats);
        if (sim == -1 || tempsim < sim) {
            result = temp;
            sim = tempsim;
        } else {
            free(temp);
        }
    }
    return result;
}
