#ifndef parkc_statitics_h
#define parkc_statitics_h

#include <stdlib.h>
#include <math.h>
#include "../utilities/constants.h"
#include "frequency.h"
#include "../cryptanalysis/ciphers_generators.h"

typedef struct {
    double **ngrams;
    StringArray *topwords;
} LangStats;

double deviation(double*, double*, size_t);
double similarity(char*, LangStats*);
LangStats* create_stats(double**, StringArray*);
Keytext *best_match(Keytext* (*generate)(), LangStats*);
#endif
