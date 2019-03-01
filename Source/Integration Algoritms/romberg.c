#include "../Assets/Integration Algorithms/rombergAlgorithm.h"

#include <stdio.h>

int main() {
    char *expression = "x^3-2*x^2+5";
    int a = -1, b = 10;
    unsigned int n = 15;
    int state = 0;
    double result = romberg(expression, a, b, n, 1e-6, 0, &state);
    printf("romberg = %lf\n", result);
}