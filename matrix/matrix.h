#pragma once

typedef struct {
    double ** entries;
    int rows, cols;
} Matrix;


Matrix *matrix_build(int row, int col);
void matrix_delete(Matrix *M);
void matrix_print(Matrix *M);
void matrix_fill(Matrix *M, double value);
void matrix_clear(Matrix *M);
void matrix_set(Matrix *M, Matrix *N);
Matrix *matrix_copy(Matrix *M);
Matrix *matrix_flatten(Matrix *M);
void matrix_scale(Matrix *M, double s);
Matrix *matrix_add(Matrix *M, Matrix* N);
void matrix_add_scalar(Matrix *M, double s);
Matrix *matrix_subtract(Matrix *M, Matrix *N);
Matrix *matrix_multiply(Matrix *M, Matrix *N);
double sigmoid(double x);
void matrix_sigmoid(Matrix *M);
void matrix_randomize(Matrix *M);
