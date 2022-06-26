#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "net/net.h"
#include "net/net.c"

#include "file/fileio.h"
#include "file/fileio.c"

int main(void)
{
    int input_size = 728, hidden_size = 32, output_size = 10, num_hidden = 3;

    // int input_size = 1, hidden_size = 1, output_size = 2, num_hidden = 1;

    // matrix *input = matrix_build(input_size, 1);
    // matrix_randomize(input);



    // neural_network *net = network_build(
    //                           input_size,
    //                           hidden_size,
    //                           output_size,
    //                           num_hidden,
    //                           input,
    //                           &matrix_sigmoid
    //                       );

    // printf("Before propagating\n");
    // network_print(net, 0);
    // propagate(net);

    // printf("After propagating\n");
    // network_print(net, 1);

    // Example * ex = training_data_read();

    // for (int i = 0; i < 150; i++)
    // {
    //     printf("Label: %d\n", ex[i].label);
    //     matrix_print(ex[i].image);
    // }

    printf("\nWow, it didn't crash.\n");

    return 0;
}
