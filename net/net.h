#pragma once

#include "../matrix/matrix.h"
#include "../matrix/matrix.c"
#include "../file/fileio.h"

typedef struct {
    int input_size, hidden_size, output_size;
    int num_hidden;
    matrix *input, *hidden, *output;
    matrix *weights, *biases;
    void (*activation_func)(matrix *);
} neural_network;

neural_network *network_build(int input_size,
                             int hidden_size,
                             int output_size,
                             int num_hidden,
                             matrix *input,
                             void (*act)(matrix *));
void network_propagate(neural_network *N);
void network_train(example * examples, int num_examples);
void network_print(neural_network *N, int only_nodes);