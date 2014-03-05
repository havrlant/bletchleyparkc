#ifndef parkc_caesar_brute_h
#define parkc_caesar_brute_h

#include "ciphers_generators.h"
#include "../datamining/statitics.h"

Keytext caesar_ngrams_crack(const char*, const LangStats*, int);
Keytext caesar_crack(const char*, const LangStats*);

#endif
