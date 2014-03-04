#ifndef parkc_triangle_attack_h
#define parkc_triangle_attack_h

#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "ciphers_generators.h"
#include "../datamining/frequency.h"
#include "../datamining/statitics.h"
#include "../utilities/constants.h"
#include "../utilities/osext.h"
#include "../ciphers/caesar.h"
#include "../lib/comb/k-permutation.h"
#include "../lib/comb/combination.h"

typedef struct{
    char letter;
    double freq;
} LetterFreq;

Keytext triangle_attack(const char*, const LangStats*, int, int);
LetterFreq *freq_to_map(double*);

#endif
