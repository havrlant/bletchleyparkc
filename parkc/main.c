#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ciphers/caesar.h"
#include "utilities/constants.h"
#include "utilities/stringext.h"
#include "datamining/frequency.h"
#include "datamining/topwords.h"
#include "datamining/statitics.h"
#include "cryptanalysis/ciphers_generators.h"
#include "cryptanalysis/caesar_brute.h"

int main()
{
    char *text = normalize("Ja, Syn Poklopu, rozzuren do silenstvi, vodarnu srovnam se zemi, jmenem mistru kanvodstvi. Ja, matku vlastni, vsak kdo vi zda, prokouknutou mel, nikoliv jak pribuzni. ");
    double** freq = load_frequencies("cs");
    StringArray *topwords = load_topwords("cs");
    LangStats *stats = create_stats(freq, topwords);
    
    Keytext* ctext = caesar_crack(caesar_encrypt(text, 'a'), stats);
    printf("Pouzity klic: %s\n", ctext->key);
    
    return 0;
}
