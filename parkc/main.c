#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ciphers/caesar.h"
#include "utilities/constants.h"
#include "datamining/frequency.h"
#include "datamining/topwords.h"

int main()
{
//    double** freq = load_frequencies("cs");
//    for (int i = 0; i < pow(ALPHABET_LENGTH, 2); i++) {
//        printf("%g ", freq[1][i]);
//    }
    printf("%s\n", caesar_encrypt("ahoj", 'b'));
    printf("%s\n", caesar_decrypt("bipk", 'b'));
    return 0;
}
