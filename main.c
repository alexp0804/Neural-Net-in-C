#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "net/net.h"
#include "net/net.c"

#include "data/fileio.c"

int main(void)
{
    int input_size = 728, hidden_size = 32, output_size = 10, num_hidden = 3;
    int only_nodes = 1;

    // Matrix *input = matrix_build(input_size, 1);
    // matrix_randomize(input);

    // NeuralNetwork *net = network_build(input_size, hidden_size, output_size, num_hidden, input);

    Example * ex = training_data_read();

    for (int i = 0; i < 150; i++)
    {
        printf("Label: %d\n", ex[i].label);
        matrix_print(ex[i].image);
    }
    

    printf("\nWow! It didn't crash!\n");

    return 0;
}
