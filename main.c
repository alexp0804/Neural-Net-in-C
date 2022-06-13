#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "net/net.h"
#include "net/net.c"


int main(void)
{
    int input_len = 5;
    Matrix *input = matrix_build(input_len, 1);
    matrix_randomize(input);
    NeuralNetwork *net = network_build(input_len, 3, 1, 2, input);
    propagate(net);

    printf("Wow! It didn't crash!\n");
    return 0;
}
