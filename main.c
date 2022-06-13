#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "net/net.h"
#include "net/net.c"

// Matrix *matrix_multiply(Matrix *M, Matrix* N);

int main(void)
{
    Matrix *input = matrix_build(5, 1);
    matrix_randomize(input);
    NeuralNetwork *net = network_build(5, 1, 2, input);
    printf("Somehow didn't crash!\n");
    return 0;
}
