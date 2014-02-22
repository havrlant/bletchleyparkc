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

int main()
{
//    char *text = normalize("Ja, Syn Poklopu, rozzuren do silenstvi, vodarnu srovnam se zemi, jmenem mistru kanvodstvi. Ja, matku vlastni, vsak kdo vi zda, prokouknutou mel, nikoliv jak pribuzni. ");
//    double** freq = load_frequencies("cs");
//    StringArray *topwords = load_topwords("cs");
//    LangStats *stats = create_stats(freq, topwords);
//    char key;
//    for (size_t i = 0; i < ALPHABET_LENGTH; i++) {
//        key = 'a' + i;
//        printf("%c: %g\n", key, similarity(caesar_encrypt(text, key), stats));
//    }
    char* text = "abcdef";
    TextGenerator generator = get_caesar_generator(text);
    Ciphertext* ctext = generator();
    while (ctext != NULL) {
        printf("%s\n", ctext->text);
        ctext = generator();
    }
    return 0;
}
