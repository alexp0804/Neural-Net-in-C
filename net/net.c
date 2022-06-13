
#include <stdio.h>
#include <stdlib.h>
#include "net.h"

NeuralNetwork *network_build(int inp, int hid, int out, Matrix *input)
{
    NeuralNetwork *net = (NeuralNetwork *) malloc(sizeof(NeuralNetwork));

    net->input_size = inp;
    // TODO: I think theres a problem with the way I'm specifying the number of layers and the size of each layer.
    // Currently, those numbers are all the same which is obviously an issue. Need to add a new param for layer size and distinguish that
    // num layers. Be sure to check following code for any modifications.
    net->hidden_size = hid;
    net->output_size = out;

    // Also, I need to clear up if the values themselves within the hidden layers are already implicitly stored,
    // or if a new array of matrices is needed. Values contained in the node are not the weights associated with that
    // node, so I think there's currently an issue.

    net->input = input;
    net->hidden = (Matrix *) malloc(sizeof(Matrix) * (hid + 1));
    net->bias = (Matrix *) malloc(sizeof(Matrix) * (hid + 1));
    net->output = (Matrix *) malloc(sizeof(Matrix));

    // Allocate weights connecting the hidden layers
    net->hidden[0] = *matrix_build(hid, inp);
    for (int i = 1; i < hid; i++)
        net->hidden[i] = *matrix_build(hid, hid);
    net->hidden[hid] = *matrix_build(out, hid);

    // Allocate the bias matrices
    for (int i = 0; i < hid; i++)
        net->bias[i] = *matrix_build(hid, 1);
    net->bias[hid] = *matrix_build(out, 1);

    // Allocate the output matrix
    net->output = matrix_build(out, 1);

    // Randomize all weights/biases
    for (int i = 0; i < hid + 1; i++)
    {
        matrix_randomize(&net->hidden[i]);
        matrix_randomize(&net->bias[i]);
    }

    return net;
}

void network_print(NeuralNetwork *N)
{
    printf(
        "Network Info:\nInput size: %d\t# hidden layers: %d\tOutput size: %d\n",
        N->input_size,
        N->hidden_size,
        N->output_size
    );

    matrix_print(N->input);
}