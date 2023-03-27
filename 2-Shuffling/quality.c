#include <stdlib.h>
#include <time.h>

#include "riffle.h"

int main() {
    srand(time(NULL));
    int i;
    for (i = 1; i <= 15; i++) {
        average_quality(50, i, 30);
    }
    return 0;
}
