#ifndef C_MATH_FIXEDPOINT_H
#define C_MATH_FIXEDPOINT_H
#define INPUT_SIZE 16

double fixedPoint(const char *expression, double x0, double ete, double ere, double tol, int maxiter, int mode,
                  int *state);


#endif //C_MATH_FIXEDPOINT_H
