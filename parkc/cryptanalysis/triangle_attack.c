#include "triangle_attack.h"

static int compare_letter_count(const void *a, const void *b) {
    const LetterFreq *lfa = (LetterFreq*)a;
    const LetterFreq *lfb = (LetterFreq*)b;
    return (lfa->freq < lfb->freq) - (lfa->freq > lfb->freq);
}

static void order_letters(LetterFreq *lc) {
    qsort(lc, ALPHABET_LENGTH, sizeof(LetterFreq), compare_letter_count);
}

LetterFreq *freq_to_map(double *freq) {
    LetterFreq *lc = (LetterFreq*) safe_malloc(sizeof(LetterFreq) * ALPHABET_LENGTH);
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        lc[i].letter = 'a' + i;
        lc[i].freq = freq[i];
    }
    return lc;
}

static LetterFreq *get_letters_occurences(const char *ciphertext) {
    double *occur = ngrams_freq(ciphertext, 1);
    LetterFreq *lc = freq_to_map(occur);
    order_letters(lc);
    free(occur);
    return lc;
}

static int letter_distance(char letter1, char letter2) {
    int distance = abs(letter1 - letter2);
    return distance <= (ALPHABET_LENGTH / 2) ? distance : ALPHABET_LENGTH - distance;
}

static int char_distances(char a, char b, char c) {
    int distance = 0;
    distance += letter_distance(a, b);
    distance += letter_distance(a, c) << 8;
    distance += letter_distance(b, c) << 16;
    return distance;
}

static int lang_distances(LetterFreq *lc) {
    return char_distances(lc[0].letter, lc[1].letter, lc[2].letter);
}

static int next_distance(LetterFreq *lc, int number) {
    static int mask[] = {0, 1, 2};
    int distance = char_distances(lc[mask[0]].letter, lc[mask[1]].letter, lc[mask[2]].letter);
    for (int i = 2; i >= 0; i--) {
        if (i == 2) {
            mask[i] = (mask[i] + 1) % number;
            continue;
        }
        if (mask[i + 1] == 0) {
            mask[i] = (mask[i] + 1) % number;
        } else {
            break;
        }
    }
    return distance;
}

void find_keys(LetterFreq *lfc, LetterFreq *lfl, char *keys, int lang_diff, int bound) {
    char key;
    int index = 0;
    for (int i = 0; i < pow(bound, 3); i++) {
        if (next_distance(lfc, bound) == lang_diff) {
            key = lfc[i / (int)pow(bound, 2)].letter;
            key = key - lfl[0].letter + 'a';
            key = key >= 'a' ? key : key + ALPHABET_LENGTH;
            keys[index++] = key;
        }
    }
}

Keytext *triangle_attack(const char *ciphertext, const LangStats *stats, int bound, int ngrams_count) {
    char *keys = (char*) safe_calloc(ALPHABET_LENGTH + 1, sizeof(char));
    LetterFreq *lf_ciphertext = get_letters_occurences(ciphertext);
    LetterFreq *lf_language = freq_to_map(stats->ngrams[0]);
    order_letters(lf_language);
    int lang_diff = lang_distances(lf_language);
    find_keys(lf_ciphertext, lf_language, keys, lang_diff, bound);
    TextGenerator generator = get_triangle_generator(ciphertext, keys);
    Keytext *keytext = best_match(generator, stats, ngrams_count);
    free(keys);
    free(lf_ciphertext);
    free(lf_language);
    return keytext;
}
