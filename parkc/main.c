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
#include "tests/run_tests.h"
#include "cryptanalysis/triangle_attack.h"


char* ciphertext = "razajejwozkpkdkjqpewxuydkivxkvewgperjajwxevahelnkpkvalkgqzjaolhjeialnkzafvxkvevwgkn";

char* opentext = "stojimvestinusedestenynazvradlechpovestnychsmrtizradcutadytedkonciposlednikrokydospinystopenychjehovistuzevsechstranvalisemasyvodydostreducernesvatynepanazeleznepekloplamenu";

static int run_test(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp("--test", argv[1]) == 0) {
            run_all_tests();
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (!run_test(argc, argv)) {
        LangStats* stats = default_stats("cs");
//        LetterFreq* lf = freq_to_map(ngrams_freq(opentext, 1));
//        LetterFreq* lf = freq_to_map(stats->ngrams[0]);
//        for (int i = 0; i < ALPHABET_LENGTH; i++) {
//            printf("%c: %g\n", lf[i].letter, lf[i].freq);
//        }
//        printf("%s", caesar_decrypt(ciphertext, 'q'));
        Keytext* ktext = triangle_attack(ciphertext, stats, 6);
        printf("Uhodnuty klic: %s\n", ktext->key);
    }
    
    printf("Done.\n");
    return 0;
}
