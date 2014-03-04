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

static void init_perm_array(unsigned int *array, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        array[i] = i;
    }
}

static uint64_t char_distances(LetterFreq *lfc, unsigned int *mask, unsigned int k) {
    unsigned int tempmask[2];
    init_perm_array(tempmask, 2);
    uint64_t cdistance = 0;
    int shift = 0;
    do {
        cdistance += letter_distance(lfc[mask[tempmask[0]]].letter, lfc[mask[tempmask[1]]].letter) << shift;
        shift += 4;
    } while (MBnext_combination(tempmask, k, 2));
    return cdistance;
}

static uint64_t lang_distances(LetterFreq *lc, unsigned int k) {
    unsigned int mask[k];
    init_perm_array(mask, k);
    return char_distances(lc, mask, k);
}

static void find_keys(LetterFreq *lfc, LetterFreq *lfl, char *keys, uint64_t lang_dist, unsigned int n, unsigned int k) {
    unsigned int mask[k];
    init_perm_array(mask, k);
    char key;
    int index = 0;
    uint64_t distance;
    do {
        distance = char_distances(lfc, mask, k);
        key = lfc[mask[0]].letter;
        if (distance == lang_dist) {
            key = key - lfl[0].letter + 'a';
            key = key >= 'a' ? key : key + ALPHABET_LENGTH;
            keys[index++] = key;
        }
    } while (MBnext_k_permutation(mask, n, k));
    
    if (keys[0] == '\0') {
        keys[0] = '?';
    }
}

static char *get_side_keys(LetterFreq *lfc, LetterFreq *lfl, const char *ciphertext, unsigned int n, unsigned int k, int (*compar)(const void*, const void*)) {
    char *keys = (char*) safe_calloc(ALPHABET_LENGTH + 1, sizeof(char));
    qsort(lfc, ALPHABET_LENGTH, sizeof(LetterFreq), compar);
    qsort(lfl, ALPHABET_LENGTH, sizeof(LetterFreq), compar);
    uint64_t lang_diff = lang_distances(lfl, k);
    find_keys(lfc, lfl, keys, lang_diff, n, k);
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

static char* get_possible_keys(const char *ciphertext, const LangStats *stats, unsigned int n, unsigned int k) {
    char *top_keys, *bottom_keys;
    LetterFreq *lfc = get_letters_occurences(ciphertext);
    LetterFreq *lfl = freq_to_map(stats->ngrams[0]);
    top_keys = get_side_keys(lfc, lfl, ciphertext, n, k, cmp_lett);
    bottom_keys = get_side_keys(lfc, lfl, ciphertext, n, k, cmp_lett_desc);
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

static char** convert_to_classical_keys(const char *keys) {
    char **new_keys = (char**) safe_malloc(sizeof(char*) * (strlen(keys)));
    for (int i = 0; keys[i] != '\0'; i++) {
        new_keys[i] = safe_malloc(2);
        new_keys[i][0] = keys[i];
        new_keys[i][1] = '\0';
    }
    return new_keys;
}

Keytext triangle_attack(const char *ciphertext, const LangStats *stats, unsigned int n, unsigned int k) {
    const char *keys = get_possible_keys(ciphertext, stats, n, k);
    char **classical_keys = convert_to_classical_keys(keys);
    TextGenerator generator = get_generator(ciphertext, classical_keys, strlen(keys), caesar_decrypt_par);
    return best_match(generator, stats, 2);
}
