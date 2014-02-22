#ifndef TOPWORDS_H
#define TOPWORDS_H
#include <string.h>
#include "stdlib.h"
#include "../utilities/stringext.h"
#include "../files.h"
#include "../utilities/ospath.h"
#include "../utilities/osext.h"

StringArray* load_topwords(const char*);
int words_occurences(StringArray*, char*);
#endif
