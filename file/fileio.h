#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "../net/net.h"

typedef struct {
    matrix *image;
    matrix *label_vector;
    int label;
} example;

FILE *image_file, *label_file;

void bad_file(char *where);
int reverse_int(int i);
void read_int(FILE *file, int *x);
int open_files(char *image_path, char *label_path);
void close_files();
example *create_example(int rows, int cols);
example *training_data_read();