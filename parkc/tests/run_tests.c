#include "run_tests.h"

void run_all_tests() {
    all_ciphers_tests();
    if (_total_errors == 0) {
        printf("ALL %i TESTS PASSED!\n", _total_tests);
    } else {
        printf("%i errors found :-(. Total tests: %i\n", _total_errors, _total_tests);
    }
}