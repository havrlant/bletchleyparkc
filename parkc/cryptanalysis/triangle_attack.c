#include "triangle_attack.h"

static int compare_letter_count(const void *a, const void *b) {
    const LetterFreq *aa = (LetterFreq*)a;
    const LetterFreq *bb = (LetterFreq*)b;
    if (aa->freq > bb->freq)
        return -1;
    else if (aa->freq < bb->freq)
        return 1;
    else
        return 0;
}

static void order_letters(LetterFreq *lc) {
    qsort(lc, ALPHABET_LENGTH, sizeof(LetterFreq), compare_letter_count);
}

LetterFreq* freq_to_map(double* freq) {
    LetterFreq* lc = (LetterFreq*) safe_malloc(sizeof(LetterFreq) * ALPHABET_LENGTH);
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        lc[i].letter = 'a' + i;
        lc[i].freq = freq[i];
    }
    return lc;
}

static LetterFreq *get_letters_occurences(const char* ciphertext) {
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

//static int* lang_differences(LetterFreq *lc_language) {
//    int* diffs = (int*) safe_malloc(sizeof(int) * 3);
//    diffs[0] = letter_distance(lc_language[0].letter, lc_language[1].letter);
//    diffs[1] = letter_distance(lc_language[0].letter, lc_language[2].letter);
//    diffs[2] = letter_distance(lc_language[1].letter, lc_language[2].letter);
//    return  diffs;
//}

static int char_distances(char a, char b, char c) {
    int distance = 0;
    distance += letter_distance(a, b);
    distance += letter_distance(a, c) << 8;
    distance += letter_distance(b, c) << 16;
    return distance;
}

static int lang_distances(LetterFreq *lc) {
//    printf("%c %c %c", lc[0].letter, lc[1].letter, lc[2].letter);
    return char_distances(lc[0].letter, lc[1].letter, lc[2].letter);
}

//static int* combinate_distance(LetterFreq *lc, int number) {
//    int count = number * number * number;
//    int* distances = (int*) safe_malloc(sizeof(int) * count);
//    int counter = 0;
//    for (int i = 0; i < number; i++) {
//        for (int j = 0; j < number; j++) {
//            for (int k = 0; k < number; k++) {
//                distances[counter++] = char_distances(lc[i].letter, lc[j].letter, lc[k].letter);
//            }
//        }
//    }
//    return distances;
//}

static int combinate_distance(LetterFreq *lc, int number) {
    static int mask[] = {0, 0, 0};
    int distance = char_distances(lc[mask[0]].letter, lc[mask[1]].letter, lc[mask[2]].letter);
//    if (lc[mask[0]].letter == 'u' && lc[mask[1]].letter == 'q' && lc[mask[2]].letter == 'e') {
//        printf("Tady: %i, %c\n", distance, lc[mask[1]].letter);
//    }
//    printf("%i %i %i\n", mask[0], mask[1], mask[2]);
    mask[2] = (mask[2] + 1) % number;
    if (mask[2] == 0) {
        mask[1] =(mask[1] + 1) % number;
        if (mask[1] == 0) {
            mask[0] = (mask[0] + 1) % number;
        }
    }
    return distance;
}

Keytext* triangle_attack(const char* ciphertext, LangStats *stats, int bound) {
    char keys[27] = {};
    int index = 0;
    LetterFreq *lc_ciphertext = get_letters_occurences(ciphertext);
    LetterFreq *lc_language = freq_to_map(stats->ngrams[0]);
    order_letters(lc_language);
    int lang_diff = lang_distances(lc_language);
    char c, key;
    for (int i = 0; i < pow(bound, 3); i++) {
        if (combinate_distance(lc_ciphertext, bound) == lang_diff) {
            c = lc_ciphertext[i / (int)pow(bound, 2)].letter;
            key = c - lc_language[0].letter + 'a';
            key = key >= 'a' ? key : key + ALPHABET_LENGTH;
            printf("klic: %c\n", key);
            keys[index++] = key;
        }
    }
    
    TextGenerator generator = get_triangle_generator(ciphertext, keys);
    return best_match(generator, stats, 1);
}
