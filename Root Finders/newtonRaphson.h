#ifndef C_MATH_NEWTONRAPHSON_H
#define C_MATH_NEWTONRAPHSON_H
#define INPUT_SIZE 16
#define DELTA 1e-6

double newtonRaphson(const char *expression, double x0, double ete, double ere, double tol, int maxiter, int mode,
                     int *state);

#endif //C_MATH_NEWTONRAPHSON_H
