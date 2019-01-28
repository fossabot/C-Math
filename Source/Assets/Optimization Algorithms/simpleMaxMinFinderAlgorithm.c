#include "simpleMaxMinFinderAlgorithm.h"
#include "../Util/functions.h"

double *simpleMaxMinFinder(const char *expression, double a, double b, unsigned int steps) {

    static double results[2];
    double coefficient = (b - a) / steps;
    double x, y, max = 0, min = 0;

    for (int i = 0; i <= steps; ++i) {
        x = a + coefficient * i;
        y = function_1_arg(expression, x);

        if (y > max) {
            max = y;
        } else if (y < min) {
            min = y;
        }
    }

    results[0] = max;
    results[1] = min;
    return results;
}