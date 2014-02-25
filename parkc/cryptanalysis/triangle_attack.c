#include "triangle_attack.h"

static int cmp_lett_desc(const void *a, const void *b) {
    const LetterFreq *lfa = (LetterFreq*)a;
    const LetterFreq *lfb = (LetterFreq*)b;
    return (lfa->freq < lfb->freq) - (lfa->freq > lfb->freq);
}

static int cmp_lett(const void *a, const void *b) {
    const LetterFreq *lfa = (LetterFreq*)a;
    const LetterFreq *lfb = (LetterFreq*)b;
    return (lfa->freq > lfb->freq) - (lfa->freq < lfb->freq);
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

static int next_distance(LetterFreq *lc, int number, char *key) {
    static int mask[] = {0, 1, 2};
    int distance = char_distances(lc[mask[0]].letter, lc[mask[1]].letter, lc[mask[2]].letter);
    *key = lc[mask[0]].letter;
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

static void find_keys(LetterFreq *lfc, LetterFreq *lfl, char *keys, int lang_dist, int bound) {
    char key;
    int index = 0;
    for (int i = 0; i < pow(bound, 3); i++) {
        if (next_distance(lfc, bound, &key) == lang_dist) {
            key = key - lfl[0].letter + 'a';
            key = key >= 'a' ? key : key + ALPHABET_LENGTH;
            keys[index++] = key;
        }
    }
    if (keys[0] == '\0') {
        keys[0] = '?';
    }
}

static char *get_side_keys(LetterFreq *lfc, LetterFreq *lfl, const char *ciphertext, int bound, int ngrams_count, int (*compar)(const void*, const void*)) {
    char *keys = (char*) safe_calloc(ALPHABET_LENGTH + 1, sizeof(char));
    qsort(lfc, ALPHABET_LENGTH, sizeof(LetterFreq), compar);
    qsort(lfl, ALPHABET_LENGTH, sizeof(LetterFreq), compar);
    int lang_diff = lang_distances(lfl);
    find_keys(lfc, lfl, keys, lang_diff, bound);
    return keys;
}

static char *strintersection(char *str1, char *str2) {
    char *intersect = (char*) safe_calloc(strlen(str1) + 1, sizeof(char));
    int found = 0;
    for (int i = 0; str1[i] != '\0'; i++) {
        for (int j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                intersect[found++] = str1[i];
                break;
            }
        }
    }
    return intersect;
}

static char *strunion(char *str1, char *str2) {
    char *sunion = (char*) safe_malloc(strlen(str1) + strlen(str2) + 1);
    size_t length = strlen(str1);
    size_t found = length;
    strcpy(sunion, str1);
    int j;
    for (int i = 0; str2[i] != '\0'; i++) {
        for (j = 0; j < length; j++) {
            if (sunion[j] == str2[i]) {
                break;
            }
        }
        if (j == length) {
            sunion[found++] = str2[i];
        }
    }
    return sunion;
}

char* get_possible_keys(const char *ciphertext, const LangStats *stats, int bound, int ngrams_count) {
    char *top_keys, *bottom_keys;
    LetterFreq *lfc = get_letters_occurences(ciphertext);
    LetterFreq *lfl = freq_to_map(stats->ngrams[0]);
    top_keys = get_side_keys(lfc, lfl, ciphertext, bound, ngrams_count, cmp_lett);
    bottom_keys = get_side_keys(lfc, lfl, ciphertext, bound, ngrams_count, cmp_lett_desc);
    char *keys = strintersection(top_keys, bottom_keys);
    size_t inter_count = strlen(keys);
    if (inter_count == 0) {
        keys = strunion(top_keys, bottom_keys);
    }
    free(top_keys);
    free(bottom_keys);
    free(lfc);
    free(lfl);
    return keys;
}

char** convert_to_classical_keys(const char *keys) {
    char **new_keys = (char**) safe_malloc(sizeof(char*) * (strlen(keys)));
    int i;
    for (i = 0; keys[i] != '\0'; i++) {
        new_keys[i] = safe_malloc(2);
        new_keys[i][0] = keys[i];
        new_keys[i][1] = '\0';
    }
    return new_keys;
}

Keytext *triangle_attack(const char *ciphertext, const LangStats *stats, int bound, int ngrams_count) {
    Keytext *keytext;
    const char *keys = get_possible_keys(ciphertext, stats, bound, ngrams_count);
    char **classical_keys = convert_to_classical_keys(keys);
    TextGenerator generator = get_generator(ciphertext, classical_keys, strlen(keys), caesar_decrypt_par);
//    TextGenerator generator = get_triangle_generator(ciphertext, keys);
    keytext = best_match(generator, stats, ngrams_count);
    return keytext;
}
