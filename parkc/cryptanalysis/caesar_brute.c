#include "caesar_brute.h"

Ciphertext* caesar_crack(const char *ciphertext, LangStats *stats) {
    TextGenerator generator = get_caesar_generator(ciphertext);
    Ciphertext* ctext = best_match(generator, stats);
    return ctext;
}