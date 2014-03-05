#include "caesar_brute.h"

Keytext caesar_ngrams_crack(const char *ciphertext, const LangStats *stats, int ngrams_count) {
    TextGenerator generator = get_caesar_generator(ciphertext);
    return best_match(generator, stats, ngrams_count);
}

Keytext caesar_crack(const char *ciphertext, const LangStats *stats) {
    return caesar_ngrams_crack(ciphertext, stats, 2);
}