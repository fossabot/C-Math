#ifndef C_MATH_BISECTION_H
#define C_MATH_BISECTION_H
#define INPUT_SIZE 16

double bisection(const char *expression, double a, double b, double ete, double ere, double tol, int maxiter, int mode,
                 int *state);

#endif //C_MATH_BISECTION_H
