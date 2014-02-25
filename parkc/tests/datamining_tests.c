#include "datamining_tests.h"

static void test_ngrams_ocur() {
    int length = ALPHABET_LENGTH;
    assert_array_eq(((int[26]){3, 2, 1}), ngrams_occur("aaabbc", 1), length, int);
    assert_array_eq(((int[26]){0}), ngrams_occur("", 1), length, int);
    assert_array_eq(((int[26*26]){2, 1}), ngrams_occur("aaab", 2), length * length, int);
    assert_array_eq(((int[26*26]){3}), ngrams_occur("aaaa", 2), length * length, int);
}

static void test_ngrams_freq() {
    int length = ALPHABET_LENGTH;
    assert_array_eq(((double[26]){30, 20, 50}), ngrams_freq("aaabbccccc", 1), length, double);
    assert_array_eq(((double[26]){0, 100}), ngrams_freq("bbbbbbbbbb", 1), length, double);
    assert_array_eq(((double[26 * 26]){75, 25}), ngrams_freq("aaaab", 2), length * length, double);
    assert_array_eq(((double[26 * 26 * 26]){75, 25}), ngrams_freq("aaaaab", 3), length * length * length, double);
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

static void test_similarity() {
    double *ngrams[] = {((double[26]){50, 30, 20})};
    StringArray* sarray = create_string_array(2);
    sarray->items = (char*[]){"Python", "Ruby"};
    LangStats *stats = create_stats(ngrams, sarray);
    assert_eq(807, round(similarity("aaababsjnkbasbbccccasdad", stats, 1)));
    assert_eq(4894, round(similarity("qwjkeoijgnomkmvo", stats, 1)));
}

void all_datamining_tests() {
    test_ngrams_ocur();
    test_ngrams_freq();
    test_word_ocurences();
    test_deviation();
    test_similarity();
}
