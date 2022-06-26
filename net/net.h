#pragma once

#include "../matrix/matrix.h"
#include "../matrix/matrix.c"

typedef struct {
    int input_size, hidden_size, output_size;
    int num_hidden;
    matrix *input, *hidden, *output;
    matrix *weights, *biases;
    void (*activation_func)(matrix *);
} neural_network;

neural_network *build(int inp, int hid, int out, matrix *input, void (*act)(matrix *));
void propogate(neural_network *N);
void network_print(neural_network *N, int only_nodes);