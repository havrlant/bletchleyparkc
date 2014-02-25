#include "statitics.h"

double deviation(double *arr1, double *arr2, size_t length) {
    double deviation = 0;
    for (size_t i = 0; i < length; i++) {
        deviation += pow(arr1[i] - arr2[i], 2);
    }
    return deviation;
}

double similarity(char *text, const LangStats *stats, int ngrams_count) {
    double sim = 0;
    double dev;
    double *freq;
    for (int i = 0; i < ngrams_count; i++) {
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

LangStats *default_stats(const char *lang) {
    double** ngrams = load_frequencies(lang);
    StringArray *topwords = load_topwords(lang);
    return create_stats(ngrams, topwords);
    
}

Keytext *best_match(TextGenerator generate, const LangStats *stats, int ngrams_count) {
    Keytext *temp, *result = NULL;
    double sim = -1, tempsim;
    for (temp = generate(); temp != NULL; temp = generate()) {
        tempsim = similarity(temp->text, stats, ngrams_count);
        if (sim == -1 || tempsim < sim) {
            if (result != NULL) {
                free(result->key);
            }
            free(result);
            result = temp;
            sim = tempsim;
        } else {
            free(temp->key);
            free(temp);
        }
    }
    return result;
}
