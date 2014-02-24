#include "datamining_tests.h"

static void test_ngrams_ocur() {
    int length = ALPHABET_LENGTH;
    assert_array_eq(((int[]){3, 2, 1}), ngrams_ocur("aaabbc", 1), length, int);
    assert_array_eq(((int[]){0}), ngrams_ocur("", 1), length, int);
    assert_array_eq(((int[]){2, 1}), ngrams_ocur("aaab", 2), length * length, int);
    assert_array_eq(((int[]){3}), ngrams_ocur("aaaa", 2), length * length, int);
}

static void test_ngrams_freq() {
    int length = ALPHABET_LENGTH;
    assert_array_eq(((double[]){30, 20, 50}), ngrams_freq("aaabbccccc", 1), length, double);
    assert_array_eq(((double[]){0, 100}), ngrams_freq("bbbbbbbbbb", 1), length, double);
    assert_array_eq(((double[]){75, 25}), ngrams_freq("aaab", 1), length, double);
}

static void test_word_ocurences() {
    StringArray* sarray = create_string_array(3);
    sarray->items = (char*[]){"ha", "Python", "Ruby"};
    assert_eq(3, words_occurences(sarray, "Python is better than Ruby! Hahaha!"));
    assert_eq(1, words_occurences(sarray, "Python forever."));
    assert_eq(0, words_occurences(sarray, "Scala is also pretty damn good."));
}

static void test_deviation() {
    assert_eq(2, deviation((double[]){1, 2, 3}, (double[]){2, 3, 3}, 3));
    assert_eq(6, deviation((double[]){1, 1, 2, 4}, (double[]){0, 3, 2, 5}, 4));
    assert_eq(0, deviation((double[]){1, 2, 3, 4}, (double[]){1, 2, 3, 4}, 4));
    assert_eq(0.25, deviation((double[]){1, 1.5}, (double[]){1, 1}, 2));
}

void all_datamining_tests() {
    test_ngrams_ocur();
    test_ngrams_freq();
    test_word_ocurences();
    test_deviation();
}
