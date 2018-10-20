#include "fibonacci.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    unsigned int n = 20;
    int *seq = fibonacci(n);
    for (int i = 0; i < n; i++) {
        printf("%d ", seq[i]);
    }
    free(seq);
    return 0;
}

int *fibonacci(unsigned int n_sequence) {
    int i, j;
    const unsigned int size = n_sequence + 1;
    int *sequence = malloc(size * sizeof(sequence));
    memset(sequence, 0x00, size);
    for (i = 1, j = 1; i < n_sequence; i++) {
        sequence[i] = sequence[i - 1] + j;
        j = sequence[i - 1];
    }
    return sequence;
}