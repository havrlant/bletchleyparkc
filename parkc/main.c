#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ciphers/caesar.h"
#include "utilities/constants.h"
#include "datamining/frequency.h"
#include "datamining/topwords.h"

int main()
{
    double* freq = ngrams_freq("aaabbbcccd", 1);
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        printf("%g ", freq[i]);
    }
    return 0;
}
