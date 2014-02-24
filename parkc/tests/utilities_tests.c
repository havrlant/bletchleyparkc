#include "utilities_tests.h"

static void test_normalize() {
    assert_str("abcdefgh", normalize("Ab!!,,  cdef gH§?!!"));
    assert_str("helloworld", normalize("Hello World!"));
    assert_str("helloworld", normalize("helloworld"));
    assert_str("", normalize(""));
}

static void test_char_count() {
    assert_eq(4, char_count("aaaabb", 'a'));
    assert_eq(0, char_count("aaaabb", 'c'));
}

static void test_concat() {
    assert_str("abcd", concat("ab", "cd"));
    assert_str("abcd", concat("abcd", ""));
    assert_str("abcd", concat("", "abcd"));
    assert_str("", concat("", ""));
}

void all_utilities_tests() {
    test_normalize();
    test_char_count();
    test_concat();
}