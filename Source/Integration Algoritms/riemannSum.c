#include "../Assets/Integration Algorithms/riemannSumAlgorithm.h"

#include <stdio.h>

void main() {
    char exp[] = "x^2+1";
    int a = 0, b = 1, o = 2, m = 0;
    unsigned int n = 10000;
    double area = riemannSum(exp, a, b, n, o, m);
    printf("Area =  %lf", area);
}

