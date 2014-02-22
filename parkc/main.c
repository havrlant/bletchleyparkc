#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ciphers/caesar.h"
#include "utilities/constants.h"
#include "datamining/frequency.h"
#include "datamining/topwords.h"

int main()
{
    double* freq = load_frequencies("cs");
    printf("%g\n", freq[0]);
    return 0;
}
