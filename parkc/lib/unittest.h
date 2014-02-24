#ifndef parkc_unittest_h
#define parkc_unittest_h

#include <string.h>

extern int _total_tests;
extern int _total_errors;

#define sassert(test) do {\
    _total_tests++;\
    if (!(test)) {\
        _total_errors++;\
        printf("Test failed: %s\n", #test);\
    }\
} while (0)

#define assert_eq(expected, actual) do {\
    _total_tests++;\
    if ((expected) != (actual)) {\
        _total_errors++;\
        printf("Test failed. %s != %s\n", #expected, #actual);\
    }\
} while(0)

#define assert_str(expected, actual) do {\
    char* _actual = (actual);\
    char* _expected = (expected);\
    _total_tests++;\
    if(strcmp(_expected, _actual) != 0) {\
        _total_errors++;\
        printf("Test failed. Code %s returns %s, expected: %s\n", #actual, _actual, _expected);\
    }\
    free(_actual); /* Not sure about this... */\
} while(0)

#endif
