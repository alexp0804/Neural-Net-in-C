#pragma once
#include "../matrix/matrix.h"
#include "../matrix/matrix.c"

typedef struct {
    int input_size, hidden_size, output_size;
    int num_hidden;
    Matrix *input, *hidden, *output;
    Matrix *weights, *biases;
} NeuralNetwork;

NeuralNetwork *build(int inp, int hid, int out, Matrix *input);
void propogate(NeuralNetwork *N);
void network_print(NeuralNetwork *N, int only_nodes);