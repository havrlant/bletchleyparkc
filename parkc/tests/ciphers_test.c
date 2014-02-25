#include "ciphers_test.h"

static void test_caesar_encrypt() {
    assert_str("bipk", caesar_encrypt("ahoj", "b"));
    assert_str("wxyzabcdefghijklmnopqrstuv", caesar_encrypt("abcdefghijklmnopqrstuvwxyz", "w"));
}

static void test_caesar_decrypt() {
    assert_str("ahoj", caesar_decrypt("bipk", "b"));
    assert_str("abcdefghijklmnopqrstuvwxyz", caesar_decrypt("wxyzabcdefghijklmnopqrstuv", "w"));
}

static void test_vigenere_encrypt() {
    assert_str("acce", vigenere_encrypt("abcd", "ab"));
    assert_str("fdcfoowdbllqwlvgtwmro", vigenere_encrypt("vsudedobradomanejlepe", "klic"));
}

static void test_vigenere_decrypt() {
    assert_str("abcd", vigenere_decrypt("acce", "ab"));
    assert_str("vsudedobradomanejlepe", vigenere_decrypt("fdcfoowdbllqwlvgtwmro", "klic"));
}

static void test_substitution_encrypt() {
    assert_str("blsntnxadcnxocftpytkt", substitution_encrypt("vsudedobradomanejlepe", "camntwqzipryofxkhdlusbevjg"));
}

static void test_substitution_decrypt() {
    assert_str("vsudedobradomanejlepe", substitution_decrypt("blsntnxadcnxocftpytkt", "camntwqzipryofxkhdlusbevjg"));
}

void all_ciphers_tests() {
    test_caesar_encrypt();
    test_caesar_decrypt();
    test_vigenere_encrypt();
    test_vigenere_decrypt();
    test_substitution_encrypt();
    test_substitution_decrypt();
}
