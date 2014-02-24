#include "cryptanalysis.h"

static void test_caesar_brute() {
    StringArray* sarray = create_string_array(1);
    sarray->items = (char*[]){"stok"};
    LangStats *stats = create_stats((double**)TEST_NGRAMS, sarray);
    char* ciphertext = "ijezycluijydkiutuijudodqplhqtbusxfeluijdosxichjyphqtskjqtojutaedsyfeibutdyaheaoteifydoijefudosxzuxelyijkpuliusxijhqdlqbyiucqioletoteijhutksuhduilqjodufqdqpubupdufuabefbqcudk";
    Keytext* ktext = caesar_crack(ciphertext, stats, 1);
    assert_str("q", ktext->key);
}

void all_cryptanalysis_tests() {
    test_caesar_brute();
}
