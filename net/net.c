
#include <stdio.h>
#include <stdlib.h>
#include "net.h"


NeuralNetwork *network_build(int input_size,
                             int hidden_size,
                             int output_size,
                             int num_hidden,
                             Matrix *input)
{
    NeuralNetwork *net = (NeuralNetwork *)  malloc(sizeof(NeuralNetwork));

    net->input_size = input_size;
    net->hidden_size = hidden_size;
    net->num_hidden = num_hidden; 
    net->output_size = output_size;

    // Set the input matrix to the param input
    net->input = input;

    // Create the hidden layers
    net->hidden = (Matrix *) malloc(sizeof(Matrix) * num_hidden);
    for (int i = 0; i < num_hidden; i++)
        net->hidden[i] = *matrix_build(hidden_size, 1); 

    // Create output layer
    net->output = matrix_build(output_size, 1);


    // Weight matrices
    net->weights = (Matrix *) malloc(sizeof(Matrix) * (num_hidden + 1));
    net->weights[0] = *matrix_build(hidden_size, input_size);
    for (int i = 1; i < num_hidden; i++)
        net->weights[i] = *matrix_build(hidden_size, hidden_size);
    net->weights[num_hidden] = *matrix_build(output_size, hidden_size);

    // Bias matrices
    net->biases = (Matrix *) malloc(sizeof(Matrix) * (num_hidden + 1));
    for (int i = 0; i < num_hidden; i++)
        net->biases[i] = *matrix_build(hidden_size, 1);
    net->biases[num_hidden] = *matrix_build(output_size, 1);


    // Randomize weights and biases
    for (int i = 0; i < num_hidden + 1; i++)
    {
        matrix_randomize(net->weights + i);
        matrix_randomize(net->biases + i);
    }

    return net;
}


void propagate(NeuralNetwork *N)
{
    for (int i = 0; i < N->num_hidden + 1; i++)
    {
        Matrix *prev = (i == 0) ? N->input : &N->hidden[i-1];
        printf("%d\n", i);
        fflush(stdout);

printf("\n\n");
            matrix_print(&N->weights[i]);
            matrix_print(prev);
printf("\n\n");

        Matrix *new = matrix_multiply(&N->weights[i], prev);
        new = matrix_add(new, &N->biases[i]);
        matrix_sigmoid(new);

        Matrix *source = (i != N->num_hidden) ? &N->hidden[i] : N->output;
        matrix_delete(source);
        source = new;

        matrix_print(new);
    }
}

void network_print(NeuralNetwork *N)
{
    printf(
        "Network Info:\nInput size: %d\t# hidden layers: %d\tOutput size: %d\n",
        N->input_size,
        N->hidden_size,
        N->output_size
    );

    // TODO Implement this
    matrix_print(N->input);
}