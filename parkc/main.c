#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ciphers/caesar.h"
#include "utilities/constants.h"
#include "datamining/frequency.h"
#include "datamining/topwords.h"

int main()
{
    StringArray* words = load_topwords("cs");
    for (int i = 0; i < words->length; i++) {
        printf("%s ", words->items[i]);
    }
    return 0;
}
