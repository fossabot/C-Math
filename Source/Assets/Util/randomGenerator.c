#include "randomGenerator.h"

#include <stdlib.h>
#include <time.h>

double zeroToOneUniformRandom(void) {
    /*
     * Generate a random number between 0 and 1
     */

    // set seed
    seed();

    // generate
    return rand() / (double) RAND_MAX;
} // end of zeroToOneUniformRandom

double floatUniformRandom(double a, double b) {
    /*
     * Generate a random number between a and b
     * in real interval
     */

    // generate
    return (b - a) * zeroToOneUniformRandom() + a;
} // end of floatUniformRandom

long int integerUniformRandom(long int n) {
    /*
     * Generate a random integer between 1 and given value n
     */

    // check n
    if (n < 0) {
        n = -n;
    } else if (n == 0) {
        return 0;
    }

    // generate
    long int guard = (long) (zeroToOneUniformRandom() * n) + 1;
    return (guard > n) ? n : guard;
} // end of integerUniformRandom

void seed(void) {
    /*
     * Reset the random number generator with the system clock
     */

    time_t t;
    srand((unsigned) time(&t));
} // end of seed