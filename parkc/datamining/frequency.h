#ifndef parkc_frequency_h
#define parkc_frequency_h

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../utilities/files.h"
#include "../utilities/osext.h"
#include "../utilities/ospath.h"
#include "../utilities/constants.h"
#include "../utilities/arrayext.h"
#include "../utilities/constants.h"

int* ngrams_ocur(const char*, char);
double* ngrams_freq(const char*, char);
double** load_frequencies(const char*);
int hash_ngram(const char* text, int start, char length);

#endif
