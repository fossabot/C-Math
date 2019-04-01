#include "fibonacciAlgorithm.h"
#include "../Util/configurations/asl_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fibonacci(unsigned int n) {
    /*
     * In mathematics, the Fibonacci numbers, commonly denoted Fn form a sequence, called the Fibonacci sequence,
     * such that each number is the sum of the two preceding ones, starting from 0 and 1.
     * Fibonacci numbers are strongly related to the golden ratio: Binet's formula expresses the nth Fibonacci number
     * in terms of n and the golden ratio, and implies that the ratio of two consecutive Fibonacci numbers tends to
     * the golden ratio as n increases.
     * Fibonacci numbers are named after Italian mathematician Leonardo of Pisa, later known as Fibonacci.
     * They appear to have first arisen as early as 200 BC in work by Pingala on enumerating possible patterns
     * of poetry formed from syllables of two lengths. In his 1202 book Liber Abaci, Fibonacci introduced the sequence
     * to Western European mathematics, although the sequence had been described earlier in Indian mathematics.
     *
     * ARGUMENTS:
     * n        nth fibonacci number
     *
     */


    return (int) round((pow(ASL_PHI, n) - (pow(-1 / ASL_PHI, n))) / ASL_SQRT5);
}