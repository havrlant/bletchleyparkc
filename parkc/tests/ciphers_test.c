#include "ciphers_test.h"

static void test_caesar_encrypt() {
    str_assert("bipk", caesar_encrypt("ahoj", 'b'));
    str_assert("wxyzabcdefghijklmnopqrstuv", caesar_encrypt("abcdefghijklmnopqrstuvwxyz", 'w'));
}

static void test_caesar_decrypt() {
    str_assert("ahoj", caesar_decrypt("bipk", 'b'));
    str_assert("abcdefghijklmnopqrstuvwxyz", caesar_decrypt("wxyzabcdefghijklmnopqrstuv", 'w'));
}

static void test_vigenere_encrypt() {
    str_assert("acce", vigenere_encrypt("abcd", "ab"));
    str_assert("fdcfoowdbllqwlvgtwmro", vigenere_encrypt("vsudedobradomanejlepe", "klic"));
}

static void test_vigenere_decrypt() {
    str_assert("abcd", vigenere_decrypt("acce", "ab"));
    str_assert("vsudedobradomanejlepe", vigenere_decrypt("fdcfoowdbllqwlvgtwmro", "klic"));
}

static void test_substitution_encrypt() {
    str_assert("blsntnxadcnxocftpytkt", substitution_encrypt("vsudedobradomanejlepe", "camntwqzipryofxkhdlusbevjg"));
}

static void test_substitution_decrypt() {
    str_assert("vsudedobradomanejlepe", substitution_decrypt("blsntnxadcnxocftpytkt", "camntwqzipryofxkhdlusbevjg"));
}

char *all_caesar_tests() {
    test_caesar_encrypt();
    test_caesar_decrypt();
    test_vigenere_encrypt();
    test_vigenere_decrypt();
    test_substitution_encrypt();
    test_substitution_decrypt();
    return NULL;
}
