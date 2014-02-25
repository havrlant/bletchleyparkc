#ifndef parkc_vigenere_brute_h
#define parkc_vigenere_brute_h

#include "ciphers_generators.h"
#include "../datamining/statitics.h"
#include "triangle_attack.h"
#include "../ciphers/vigenere.h"

Keytext *vigenere_brute(const char*, const LangStats*);

#endif
