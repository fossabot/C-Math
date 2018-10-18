#include "tinyexpr.h"

#ifndef C_MATH_BISECTION_H
#define C_MATH_BISECTION_H
#define INPUT_SIZE 16

double function(double value, const char *expression);

double bisection(const char *expression, double a, double b, double ete, double ere, double tol, int maxiter, int mode,
                 int *state);

#endif //C_MATH_BISECTION_H
