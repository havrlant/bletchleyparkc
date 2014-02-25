#include "utils.h"

LangStats *default_langstats() {
    StringArray *sarray = create_string_array(0);
    LangStats *stats = create_stats((double**)TEST_NGRAMS, sarray);
    return stats;
}
