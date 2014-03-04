#include "cryptanalysis.h"

static void test_caesar_brute() {
    StringArray *sarray = create_string_array(1);
    sarray->items = (char*[]){"stok"};
    LangStats *stats = create_stats((double**)TEST_NGRAMS, sarray);
    char *ciphertext = "ijezycluijydkiutuijudodqplhqtbusxfeluijdosxichjyphqtskjqtojutaedsyfeibutdyaheaoteifydoijefudosxzuxelyijkpuliusxijhqdlqbyiucqioletoteijhutksuhduilqjodufqdqpubupdufuabefbqcudk";
    Keytext ktext = caesar_crack(ciphertext, stats, 1);
    assert_str("q", ktext.key);
}

static void test_triangle_attack() {
    LangStats *stats = default_langstats();
    char *opentext = "vedeninasdotohonutiabychomzboziaktivnenabizeliprotozepokudnesplnimeprodejzbozizakorunmesicnekratisenampenizereklamfdnesprazskapostovnidorucovatelkakteranechcezverejnitsvejmenoceskapostanatomnicspatnehonevidihledamekazdoukorunuzalezinamnatomjaksenedostatdoztratrikasefodborukomunikaceivomravinaclekarkuevukralikovoukteravedesitporadennaodvykanikourenichovanipostynadzvedloceskopodepsaloumluvuokontroletabakukdesezavazujemeomezitpocetprodejnichmistamyudelamepresnyopaknavicpodhlavickoustatniinstitucetojeabsurdnizlobisebudemeprotestovatunadrizenehoorganupostyinaministerstvuzdravotnictvidodavakralikova";
    char *ciphertext = empty_string(strlen(opentext));
    Keytext keytext;
    char key[2] = {};
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        key[0] = 'a' + i;
        caesar_encrypt_par(opentext, key, ciphertext);
        keytext = triangle_attack(ciphertext, stats, 6, 3);
        assert_str(key, keytext.key);
    }
    
    keytext = triangle_attack("asdfg", stats, 3, 3);
    assert_str("?", keytext.key);
    assert_str("", keytext.text);
}

static void test_vigenere_brute() {
    LangStats *stats = default_langstats();
    char *opentext = "jasynpoklopurozzurendosilenstvivodarnusrovnamsezemijmenemmistrukanvodstvijamatkuvlastnivsakkdovizdaprokouknutoumelnikolivjakpribuznismrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnytedvidisotcecozzenstinytveuzralouzjetotadybratretyslezlzradcumdozadkujensedobrepodivejcostvojijimkouprovedlimusimedrzetpospoluatuznenimarnesnazenivejmenusatanarozpoutejmepeklouzsevmychpredstavachrodisedevyjevykrasnemodrenadrzecimtakrychlecernajinenitonahodouodpadnivodamrtverybynahazimedovodarenskychobjektuuznehodlamdalnaslouchattemvodarenskymblabolumsedekrysysezerouzbytkyvodarenskychkonstrukcipredpovidamvecnouskazuvodarenskemafiitakjakodavnopredcasemjsmesvatouchatrutopilystejnykonecpripravimepodvodnikumzvodarnynelzeveritnikomukdomatlamuplnoucistotyvsechnytyhlebestiecekavodazestokysmrtlidemzvodarnysmrtivrchnizradkynijenslavumistrumzcistirnyzevsechstrannavodarnusilaspinyutocizhorastavbydrtizeleznemepoklopydokristalovevodytecoucistirenskesplaskysabotaztospachanavejmenusedepravdy";
    char *keys[] = {"klic", "qwsa", "as", "strom"};
    Keytext keytext;
    size_t key_count = 4;
    for (size_t i = 0; i < key_count; i++) {
        keytext = vigenere_brute(vigenere_encrypt(opentext, keys[i]), stats);
        assert_str(keys[i], keytext.key);
    }
}

void all_cryptanalysis_tests() {
    test_caesar_brute();
    test_triangle_attack();
    test_vigenere_brute();
}
