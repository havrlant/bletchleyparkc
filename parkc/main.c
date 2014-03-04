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


char *ciphertext = "razajejwozkpkdkjqpewxuydkivxkvewgperjajwxevahelnkpkvalkgqzjaolhjeialnkzafvxkvevwgkn";

char *opentext = "jasynpoklopurozzurendosilenstvivodarnusrovnamsezemijmenemmistrukanvodstvijamatkuvlastnivsakkdovizdaprokouknutoumelnikolivjakpribuznismrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnytedvidisotcecozzenstinytveuzralouzjetotadybratretyslezlzradcumdozadkujensedobrepodivejcostvojijimkouprovedlimusimedrzetpospoluatuznenimarnesnazenivejmenusatanarozpoutejmepeklouzsevmychpredstavachrodisedevyjevykrasnemodrenadrzecimtakrychlecernajinenitonahodouodpadnivodamrtverybynahazimedovodarenskychobjektuuznehodlamdalnaslouchattemvodarenskymblabolumsedekrysysezerouzbytkyvodarenskychkonstrukcipredpovidamvecnouskazuvodarenskemafiitakjakodavnopredcasemjsmesvatouchatrutopilystejnykonecpripravimepodvodnikumzvodarnynelzeveritnikomukdomatlamuplnoucistotyvsechnytyhlebestiecekavodazestokysmrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnyzevsechstrannavodarnusilaspinyutocizhorastavbydrtizeleznemepoklopydokristalovevodytecoucistirenskesplaskysabotaztospachanavejmenusedepravdy";

char *spravne = "zoeehpuebiytdhdiuzdcjaliycabjlaepfaajcdelaypijtptdcysyqozilyhpihjlyjspidlpbpjqrjjbbqketzieutuelycketcytueeqpdquqduuiqhfjcueicxujqhytolhdeutucasuhzujqteqythurqpulqdoeukdeqqqexjlqdobecthoperaehisejaftlqueaktuaqyaaqeuqcclexhebjdesyqceeycehdpujakejcbkijixjbuyulqiacbulqohlxptdubkiksjduuiqqtdyidjyeiltybduafeyqlejeyydubaqjjfxqzdufl";

char *spatne = "tiyybjoyvcsnxbxcotxwdufcswuvdfuyjzuudwxyfusjcdnjnxwsmskitcfsbjcbdfsdmjcxfjvjdklddvvkeyntcyonoyfsweynwsnoyykjxkokxoockbzdwoycwrodkbsnifbxyonowumobtodknyksnbolkjofkxiyoexykkkyrdfkxivywnbijyluybcmyduznfkoyuenouksuukyokwwfyrbyvdxymskwyyswybxjodueydwvecdcrdvosofkcuwvofkibfrjnxovecemdxoockknxscxdsycfnsvxouzyskfydyssxovukddzrktxozf";

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
    return NULL;
}

int main(int argc, char *argv[]) {
    int runtest = 0;
    int pretty_print = 0;
    char *encrypt = NULL, *decrypt = NULL, *key = NULL, *text = NULL;
    char *output;
    int c;
    const int ciphers_count = 3;
    const cipherfun encfuns[] = {caesar_encrypt, substitution_encrypt, vigenere_encrypt};
    const cipherfun decfuns[] = {caesar_decrypt, substitution_decrypt, vigenere_decrypt};
    const char* cipher_names[] = {"caesar", "subs", "vig"};
        
    opterr = 0;
    
    while ((c = getopt(argc, argv, "upe:d:k:")) != -1) {
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
            case 'p':
                pretty_print = 1;
                break;
            default:
                printf("Unknow argument -%c.", c);
                abort();
        }
    }
    
    if (encrypt != NULL || decrypt != NULL) {
        if (key == NULL) {
            printf("Error: Key is missing");
            abort();
        }
        if (argc <= optind) {
            printf("Error: Input text missing.\n");
            abort();
        } else {
            text = argv[optind];
        }
        
        if (encrypt != NULL) {
            output = get_cipher_fun(cipher_names, encfuns, encrypt, ciphers_count)(text, key);
        }
        
        if (decrypt != NULL) {
            output = get_cipher_fun(cipher_names, decfuns, decrypt, ciphers_count)(text, key);
        }
        
        printf("%s", output);
        print_newline(pretty_print);
    }
    
    if (runtest) {
        run_all_tests();
    }
    return 0;
}
