#include "datamining_tests.h"

static void test_ngrams_ocur() {
    int expected[26] = {3, 2, 1};
    int expected2[26] = {0};
    int expected3[26*26] = {2, 1};
    int expected4[26*26] = {3};
    
    assert_array_eq(expected, ngrams_ocur("aaabbc", 1), ALPHABET_LENGTH, int);
    assert_array_eq(expected2, ngrams_ocur("", 1), ALPHABET_LENGTH, int);
    assert_array_eq(expected3, ngrams_ocur("aaab", 2), ALPHABET_LENGTH * ALPHABET_LENGTH, int);
    assert_array_eq(expected4, ngrams_ocur("aaaa", 2), ALPHABET_LENGTH * ALPHABET_LENGTH, int);
}

static void test_ngrams_freq() {
    double expected[26] = {30, 20, 50};
    double expected2[26] = {0, 100};
    double expected3[26 * 26] = {75, 25};
    
    assert_array_eq(expected, ngrams_freq("aaabbccccc", 1), ALPHABET_LENGTH, double);
    assert_array_eq(expected2, ngrams_freq("bbbbbbbbbb", 1), ALPHABET_LENGTH, double);
    assert_array_eq(expected3, ngrams_freq("aaab", 1), ALPHABET_LENGTH, double);
}

void all_datamining_tests() {
    test_ngrams_ocur();
    test_ngrams_freq();
}
