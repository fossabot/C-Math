#ifndef C_MATH_GRADIENTDESCENT_H
#define C_MATH_GRADIENTDESCENT_H
#define INPUT_SIZE 32
#define DX 1e-6

double gradientDescent(const char *expression, double x0, double ete, double ere, double gamma, int maxiter, int mode,
                       int *state);

#endif //C_MATH_GRADIENTDESCENT_H
