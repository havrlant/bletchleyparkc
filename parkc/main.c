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


char *ciphertext = "razajejwozkpkdkjqpewxuydkivxkvewgperjajwxevahelnkpkvalkgqzjaolhjeialnkzafvxkvevwgkn";

char *opentext = "jasynpoklopurozzurendosilenstvivodarnusrovnamsezemijmenemmistrukanvodstvijamatkuvlastnivsakkdovizdaprokouknutoumelnikolivjakpribuznismrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnytedvidisotcecozzenstinytveuzralouzjetotadybratretyslezlzradcumdozadkujensedobrepodivejcostvojijimkouprovedlimusimedrzetpospoluatuznenimarnesnazenivejmenusatanarozpoutejmepeklouzsevmychpredstavachrodisedevyjevykrasnemodrenadrzecimtakrychlecernajinenitonahodouodpadnivodamrtverybynahazimedovodarenskychobjektuuznehodlamdalnaslouchattemvodarenskymblabolumsedekrysysezerouzbytkyvodarenskychkonstrukcipredpovidamvecnouskazuvodarenskemafiitakjakodavnopredcasemjsmesvatouchatrutopilystejnykonecpripravimepodvodnikumzvodarnynelzeveritnikomukdomatlamuplnoucistotyvsechnytyhlebestiecekavodazestokysmrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnyzevsechstrannavodarnusilaspinyutocizhorastavbydrtizeleznemepoklopydokristalovevodytecoucistirenskesplaskysabotaztospachanavejmenusedepravdy";

char *spravne = "zoeehpuebiytdhdiuzdcjaliycabjlaepfaajcdelaypijtptdcysyqozilyhpihjlyjspidlpbpjqrjjbbqketzieutuelycketcytueeqpdquqduuiqhfjcueicxujqhytolhdeutucasuhzujqteqythurqpulqdoeukdeqqqexjlqdobecthoperaehisejaftlqueaktuaqyaaqeuqcclexhebjdesyqceeycehdpujakejcbkijixjbuyulqiacbulqohlxptdubkiksjduuiqqtdyidjyeiltybduafeyqlejeyydubaqjjfxqzdufl";

char *spatne = "tiyybjoyvcsnxbxcotxwdufcswuvdfuyjzuudwxyfusjcdnjnxwsmskitcfsbjcbdfsdmjcxfjvjdklddvvkeyntcyonoyfsweynwsnoyykjxkokxoockbzdwoycwrodkbsnifbxyonowumobtodknyksnbolkjofkxiyoexykkkyrdfkxivywnbijyluybcmyduznfkoyuenouksuukyokwwfyrbyvdxymskwyyswybxjodueydwvecdcrdvosofkcuwvofkibfrjnxovecemdxoockknxscxdsycfnsvxouzyskfydyssxovukddzrktxozf";

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
//        triangle_attack(spravne, default_stats("cs"), 8, 1);
//        triangle_attack(spatne, default_stats("cs"), 8, 1);
//        ciphertext = vigenere_encrypt(opentext, "qwp");
        Keytext *ktext = vigenere_brute(vigenere_encrypt(opentext, "klic"), default_stats("cs"));
        printf("%s\n", ktext->key);
//        vigenere_brute(vigenere_encrypt(opentext, "key"), default_stats("cs"));
    }
    
    printf("Done.\n");
    return 0;
}
