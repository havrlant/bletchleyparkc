#include "caesar_brute.h"

Keytext *caesar_crack(const char *ciphertext, LangStats *stats, int ngrams_count) {
    TextGenerator generator = get_caesar_generator(ciphertext);
    Keytext *ctext = best_match(generator, stats, ngrams_count);
    return ctext;
}
