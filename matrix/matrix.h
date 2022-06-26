#pragma once

typedef struct {
    double **entries;
    int rows, cols;
} matrix;


matrix *matrix_build(int row, int col);
void matrix_delete(matrix *M);
void matrix_print(matrix *M);
void matrix_fill(matrix *M, double value);
void matrix_clear(matrix *M);
void matrix_set(matrix *M, matrix *N);
matrix *matrix_copy(matrix *M);
matrix *matrix_flatten(matrix *M);
void matrix_scale(matrix *M, double s);
matrix *matrix_add(matrix *M, matrix* N);
void matrix_add_scalar(matrix *M, double s);
matrix *matrix_subtract(matrix *M, matrix *N);
matrix *matrix_multiply(matrix *M, matrix *N);
double sigmoid(double x);
void matrix_sigmoid(matrix *M);
void matrix_softmax(matrix *M);
void matrix_randomize(matrix *M);

