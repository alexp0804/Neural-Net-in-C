#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "net/net.h"
#include "net/net.c"


int main(void)
{
    int input_size = 3, hidden_size = 2, output_size = 1, num_hidden = 1;
    int only_nodes = 1;

    Matrix *input = matrix_build(input_size, 1);
    matrix_randomize(input);

    NeuralNetwork *net = network_build(input_size, hidden_size, output_size, num_hidden, input);
    network_print(net, only_nodes);
    propagate(net);

    printf("\nWow! It didn't crash!\n");
    network_print(net, only_nodes);
    return 0;
}
