
#include <stdio.h>
#include <stdlib.h>
#include "net.h"


neural_network *network_build(int input_size,
                             int hidden_size,
                             int output_size,
                             int num_hidden,
                             matrix *input,
                             void (*act)(matrix *))
{
    neural_network *net = (neural_network *)  malloc(sizeof(neural_network));

    net->input_size = input_size;
    net->hidden_size = hidden_size;
    net->num_hidden = num_hidden; 
    net->output_size = output_size;

    // Set the input matrix to the param input
    net->input = input;

    // Create the hidden layers
    net->hidden = (matrix *) malloc(sizeof(matrix) * num_hidden);
    for (int i = 0; i < num_hidden; i++)
        net->hidden[i] = *matrix_build(hidden_size, 1); 

    // Create output layer
    net->output = matrix_build(output_size, 1);

    // Weight matrices
    net->weights = (matrix *) malloc(sizeof(matrix) * (num_hidden + 1));
    net->weights[0] = *matrix_build(hidden_size, input_size);
    for (int i = 1; i < num_hidden; i++)
        net->weights[i] = *matrix_build(hidden_size, hidden_size);
    net->weights[num_hidden] = *matrix_build(output_size, hidden_size);

    // Bias matrices
    net->biases = (matrix *) malloc(sizeof(matrix) * (num_hidden + 1));
    for (int i = 0; i < num_hidden; i++)
        net->biases[i] = *matrix_build(hidden_size, 1);
    net->biases[num_hidden] = *matrix_build(output_size, 1);

    // Randomize weights and biases
    for (int i = 0; i < num_hidden + 1; i++)
    {
        matrix_randomize(&net->weights[i]);
        matrix_randomize(&net->biases[i]);
    }

    // Set activation function
    net->activation_func = act;

    return net;
}


void propagate(neural_network *N)
{
    for (int i = 0; i < N->num_hidden + 1; i++)
    {
        // Multiply this nodes values with the weights, add on the biases
        matrix *new = matrix_add(
                        matrix_multiply(
                                &N->weights[i],
                                (i == 0) ? N->input : &N->hidden[i-1]
                        ),
                        &N->biases[i]
                      );

        // Run the result through an activation function, the chosen one if not
        // at the end of the net. If it's the last layer, use softmax.
        if (i != N->num_hidden)
            N->activation_func(new);
        else
            matrix_softmax(new);

        // Replace this layers nodes with result from above
        matrix_set((i != N->num_hidden) ? &N->hidden[i] : N->output, new);
    }
}

void network_print(neural_network *N, int only_nodes)
{
    printf(
        "Network Info:\nInput size: %d\t# hidden layers: %d\tOutput size: %d\n",
        N->input_size,
        N->hidden_size,
        N->output_size
    );

    printf("Input Layer:\n");
    matrix_print(N->input);
    for (int i = 0; i < N->num_hidden; i++)
    {
        if (!only_nodes)
        {
            printf("Weights from Layer %d to Layer %d\n", i, i+1);
            matrix_print(&N->weights[i]);
            printf("Biases for Layer %d\n", i+1);
            matrix_print(&N->biases[i]);
        }
        printf("Nodes for Layer %d\n", i+1);
        matrix_print(&N->hidden[i]);
    }

    if (!only_nodes)
    {
        printf("Weights from Layer %d to Output Layer\n", N->num_hidden);
        matrix_print(&N->weights[N->num_hidden]);
        printf("Biases for Output Layer\n");
        matrix_print(&N->biases[N->num_hidden]);
    }
    printf("Output Layer:\n");
    matrix_print(N->output);
}