#include "cryptanalysis.h"

static void test_caesar_brute() {
    StringArray* sarray = create_string_array(1);
    sarray->items = (char*[]){"stok"};
    LangStats *stats = create_stats((double**)TEST_NGRAMS, sarray);
    char* ciphertext = "ijezycluijydkiutuijudodqplhqtbusxfeluijdosxichjyphqtskjqtojutaedsyfeibutdyaheaoteifydoijefudosxzuxelyijkpuliusxijhqdlqbyiucqioletoteijhutksuhduilqjodufqdqpubupdufuabefbqcudk";
    Keytext* ktext = caesar_crack(ciphertext, stats, 1);
    assert_str("q", ktext->key);
}

static void test_triangle_attack() {
    LangStats* stats = default_langstats();
    char *opentext = "vedeninasdotohonutiabychomzboziaktivnena";
    char *ciphertext = empty_string(strlen(opentext));
    Keytext *keytext;
    char key[2] = {};
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        key[0] = 'a' + i;
        caesar_encrypt_par(opentext, key[0], ciphertext);
        keytext = triangle_attack(ciphertext, stats, 6, 1);
        assert_str(key, keytext->key);
    }
}

void all_cryptanalysis_tests() {
    test_caesar_brute();
    test_triangle_attack();
}
