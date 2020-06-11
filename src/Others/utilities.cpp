#include <cstdio>
#include <cstdlib>
#include "utilities.h"

void exitWithError(const char *errorText) {
    perror(errorText);
    exit(1);
}
