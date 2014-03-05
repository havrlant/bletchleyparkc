#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
#include "cryptanalysis/vigenere_brute.h"
#include "lib/comb/k-permutation.h"
#include "lib/comb/comb-util.h"
#include "ciphers/ciphers.h"
#include "cryptanalysis/crypt.h"

static void print_newline(int pretty_print) {
    if (pretty_print) {
        printf("\n");
    }
}

cipherfun get_cipher_fun(const char* cipher_names[], const cipherfun cipfuns[], const char *current_cipher, int ciphers_count) {
    for (int i = 0; i < ciphers_count; i++) {
        if (strcmp(current_cipher, cipher_names[i]) == 0) {
            return cipfuns[i];
        }
    }
    printf("Error: Invalid cipher name. Valid names: ");
    for (int i = 0; i < ciphers_count; i++) {
        printf("%s ", cipher_names[i]);
    }
    printf("\n");
    exit(EXIT_FAILURE);
}

crack_cipher get_crack_fun(const char* cipher_names[], const crack_cipher cipfuns[], const char *current_cipher, int ciphers_count) {
    for (int i = 0; i < ciphers_count; i++) {
        if (strcmp(current_cipher, cipher_names[i]) == 0) {
            return cipfuns[i];
        }
    }
    printf("Error: Invalid cipher name. Valid names: ");
    for (int i = 0; i < ciphers_count; i++) {
        printf("%s ", cipher_names[i]);
    }
    printf("\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int runtest = 0;
    int pretty_print = 0;
    char *encrypt = NULL, *decrypt = NULL, *key = NULL, *text = NULL, *crack = NULL, *lang = "cs";
    const char *output;
    int c;
    const int ciphers_count = 3;
    const cipherfun encfuns[] = {caesar_encrypt, substitution_encrypt, vigenere_encrypt};
    const cipherfun decfuns[] = {caesar_decrypt, substitution_decrypt, vigenere_decrypt};
    const crack_cipher crackfun[] = {caesar_crack, caesar_crack, vigenere_brute};
    const char* cipher_names[] = {"caesar", "subs", "vig"};
    const char* languages[] = {"cs", "en"};
    const int lang_count = 2;
    const LangStats *stats;
    Keytext result;
        
    opterr = 0;
    
    while ((c = getopt(argc, argv, "upe:d:k:c:l:")) != -1) {
        switch(c) {
            case 'u':
                runtest = 1;
                break;
            case 'e':
                encrypt = optarg;
                break;
            case 'd':
                decrypt = optarg;
                break;
            case 'k':
                key = optarg;
                break;
            case 'c':
                crack = optarg;
                break;
            case 'p':
                pretty_print = 1;
                break;
            case 'l':
                for (int i = 0; i < lang_count; i++) {
                    if (strcmp(optarg, languages[i]) == 0) {
                        lang = optarg;
                        break;
                    }
                }
                break;
            default:
                fprintf(stderr, "Unknow argument -%c.", c);
                exit(EXIT_FAILURE);
        }
    }
    
    if (encrypt != NULL || decrypt != NULL || crack != NULL) {
        if (encrypt != NULL || decrypt != NULL) {
            if (key == NULL) {
                fprintf(stderr, "Error: Key is missing\n");
                exit(EXIT_FAILURE);
            }
        }
        
        if (argc <= optind) {
            fprintf(stderr, "Error: Input text missing.\n");
            exit(EXIT_FAILURE);
        } else {
            text = argv[optind];
        }
        
        if (encrypt != NULL) {
            output = get_cipher_fun(cipher_names, encfuns, encrypt, ciphers_count)(text, key);
        }
        
        if (decrypt != NULL) {
            output = get_cipher_fun(cipher_names, decfuns, decrypt, ciphers_count)(text, key);
        }
        
        if (crack != NULL) {
            stats = default_stats(lang);
            result = get_crack_fun(cipher_names, crackfun, crack, ciphers_count)(text, stats);
            if (result.key[0] != '?') {
                output = result.key;
            } else {
                output = "Cracking was not successful.";
            }
        }
        
        printf("%s", output);
        print_newline(pretty_print);
    }
    
    if (runtest) {
        run_all_tests();
    }
    return 0;
}
