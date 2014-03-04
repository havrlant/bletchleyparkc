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


char *ciphertext = "razajejwozkpkdkjqpewxuydkivxkvewgperjajwxevahelnkpkvalkgqzjaolhjeialnkzafvxkvevwgkn";

char *opentext = "jasynpoklopurozzurendosilenstvivodarnusrovnamsezemijmenemmistrukanvodstvijamatkuvlastnivsakkdovizdaprokouknutoumelnikolivjakpribuznismrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnytedvidisotcecozzenstinytveuzralouzjetotadybratretyslezlzradcumdozadkujensedobrepodivejcostvojijimkouprovedlimusimedrzetpospoluatuznenimarnesnazenivejmenusatanarozpoutejmepeklouzsevmychpredstavachrodisedevyjevykrasnemodrenadrzecimtakrychlecernajinenitonahodouodpadnivodamrtverybynahazimedovodarenskychobjektuuznehodlamdalnaslouchattemvodarenskymblabolumsedekrysysezerouzbytkyvodarenskychkonstrukcipredpovidamvecnouskazuvodarenskemafiitakjakodavnopredcasemjsmesvatouchatrutopilystejnykonecpripravimepodvodnikumzvodarnynelzeveritnikomukdomatlamuplnoucistotyvsechnytyhlebestiecekavodazestokysmrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnyzevsechstrannavodarnusilaspinyutocizhorastavbydrtizeleznemepoklopydokristalovevodytecoucistirenskesplaskysabotaztospachanavejmenusedepravdy";

char *spravne = "zoeehpuebiytdhdiuzdcjaliycabjlaepfaajcdelaypijtptdcysyqozilyhpihjlyjspidlpbpjqrjjbbqketzieutuelycketcytueeqpdquqduuiqhfjcueicxujqhytolhdeutucasuhzujqteqythurqpulqdoeukdeqqqexjlqdobecthoperaehisejaftlqueaktuaqyaaqeuqcclexhebjdesyqceeycehdpujakejcbkijixjbuyulqiacbulqohlxptdubkiksjduuiqqtdyidjyeiltybduafeyqlejeyydubaqjjfxqzdufl";

char *spatne = "tiyybjoyvcsnxbxcotxwdufcswuvdfuyjzuudwxyfusjcdnjnxwsmskitcfsbjcbdfsdmjcxfjvjdklddvvkeyntcyonoyfsweynwsnoyykjxkokxoockbzdwoycwrodkbsnifbxyonowumobtodknyksnbolkjofkxiyoexykkkyrdfkxivywnbijyluybcmyduznfkoyuenouksuukyokwwfyrbyvdxymskwyyswybxjodueydwvecdcrdvosofkcuwvofkibfrjnxovecemdxoockknxscxdsycfnsvxouzyskfydyssxovukddzrktxozf";


int main(int argc, char *argv[]) {
    int runtest = 0;
    int optarg;
    
    opterr = 0;
    
    while ((optarg = getopt(argc, argv, "u")) != -1) {
        switch(optarg) {
            case 'u':
                runtest = 1;
                break;
            default:
                printf("Unknow argument -%c.", optarg);
                abort();
        }
    }
    
    if (runtest) {
        run_all_tests();
    } else {
        int test = 0, shift = 0;
        printf("Test: %i\n", test);
        for (int i = 0; i < 100; i++) {
            test += 10 << shift;
            shift += 5;
            printf("Test: %i\n", 10 << shift);
        }
    }
    return 0;
}
