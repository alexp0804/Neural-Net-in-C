#pragma once
#include "../matrix/matrix.h"
#include "../matrix/matrix.c"

typedef struct {
    int input_size, hidden_size, output_size;
    int num_hidden;
    Matrix *input, *hidden, *output, *bias;
} NeuralNetwork;

NeuralNetwork *build(int inp, int hid, int out, Matrix *input);