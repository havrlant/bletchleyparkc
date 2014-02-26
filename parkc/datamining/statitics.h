#ifndef parkc_statitics_h
#define parkc_statitics_h

#include <stdlib.h>
#include <math.h>
#include "../utilities/constants.h"
#include "../utilities/osext.h"
#include "frequency.h"
#include "topwords.h"
#include "../cryptanalysis/ciphers_generators.h"

typedef struct {
    double **ngrams;
    StringArray *topwords;
} LangStats;

double deviation(double*, double*, size_t);
double similarity(char*, const LangStats*, int);
LangStats *create_stats(double**, StringArray*);
Keytext best_match(TextGenerator, const LangStats*, int);
LangStats *default_stats(const char*);
#endif
