#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

// Helper functions for bad requests
void bad_ref(char *where)
{
    fprintf(stderr, "Invalid matrix reference in matrix_%s()\n", where);
    exit(1);
}
void bad_dims(char *where)
{
    fprintf(stderr, "Invalid matrix dimensions in matrix_%s()\n", where);
    exit(1);
}
void bad_mem(char *where)
{
    fprintf(stderr, "Memory allocation failure in matrix_%s()\n", where);
    exit(1);
}

matrix *matrix_build(int row, int col)
{
    matrix * M = (matrix *) malloc(sizeof(matrix));
    M->rows = row, M->cols = col;

    M->entries = (double **) malloc(sizeof(double *) * row);
    for (int i = 0; i < row; i++)
        M->entries[i] = (double *) calloc(col, sizeof(double));

    return M;
}

void matrix_delete(matrix *M)
{
    if (!M)
        bad_ref("delete");

    for (int i = 0; i < M->rows; i++)
        free(M->entries[i]);

    free(M->entries);
    free(M);
}

void matrix_print(matrix *M)
{
    if (!M)
        bad_ref("print");

    printf("Rows: %d\tCols: %d\n", M->rows, M->cols);
    for (int i = 0; i < M->rows; i++)
    {
        for (int j = 0; j < M->cols; j++)
        {
            printf("%3.4f ", M->entries[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_fill(matrix *M, double value)
{
    if (!M)
        bad_ref("fill"); 

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] = value;
}

void matrix_clear(matrix *M)
{
    if (!M)
        bad_ref("clear");

    matrix_fill(M, 0);
}

// After using this function the N matrix is no longer safe to use.
void matrix_set(matrix *M, matrix *N)
{
    if (!M || !N)
        bad_ref("set");

    if (M->rows != N->rows || M->cols != N->cols)
        bad_dims("set");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] = N->entries[i][j];

    matrix_delete(N);
}

matrix *matrix_copy(matrix *M)
{
    if (!M)
        bad_ref("copy");

    matrix *copy = matrix_build(M->rows, M->cols);
    if (!copy)
        bad_mem("copy");
    
    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            copy->entries[i][j] = M->entries[i][j];

    return copy;
}

matrix *matrix_flatten(matrix *M)
{
    if (!M)
        bad_ref("flatten");
    
    matrix *new = matrix_build(M->rows * M->cols, 1);
    if (!new)
        bad_mem("flatten");
    
    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            new->entries[i * M->cols + j][0] = M->entries[i][j];

    return new;
}

void matrix_scale(matrix *M, double s)
{
    if (!M)
        bad_ref("scale");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] *= s;
}

matrix *matrix_add(matrix *M, matrix* N)
{
    if (!M || !N)
        bad_ref("add");

    if (M->rows != N->rows || M->cols != N->cols)
        bad_dims("add");

    matrix *new = matrix_build(M->rows, M->cols);
    if (!new)
        bad_mem("add");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            new->entries[i][j] = M->entries[i][j] + N->entries[i][j];

    return new;
}

void matrix_add_scalar(matrix *M, double s)
{
    if (!M)
        bad_ref("add_scalar");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] += s;
}

// M - N
matrix *matrix_subtract(matrix *M, matrix *N)
{
    if (!M || !N)
        bad_ref("subtract");

    if (M->rows != N->rows || M->cols != N->cols)
        bad_dims("subtract");

    matrix *new = matrix_build(M->cols, M->rows);
    if (!new)
        bad_mem("subtract");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            new->entries[i][j] = M->entries[i][j] - N->entries[i][j];

    return new;
}

matrix *matrix_multiply(matrix *M, matrix* N)
{
    if (!M || !N)
        bad_ref("multiply");

    if (M->cols != N->rows)
        bad_dims("multiply");

    matrix *new = matrix_build(M->rows, N->cols);
    if (!new)
        bad_mem("multiply");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < N->cols; j++)
            for (int k = 0; k < M->cols; k++) 
                new->entries[i][j] += M->entries[i][k] * N->entries[k][j];

    return new;
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

void matrix_sigmoid(matrix *M)
{
    if (!M)
        bad_ref("sigmoid");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] = sigmoid(M->entries[i][j]);
}

void matrix_softmax(matrix *M)
{
    double norm_term = 0;

    // M must be a column matrix
    if (M->cols != 1) return;

    for (int i = 0; i < M->rows; i++)
        norm_term += exp(M->entries[i][0]);
    
    printf("%f\n", norm_term);

    for (int i = 0; i < M->rows; i++)
        M->entries[i][0] = exp(M->entries[i][0]) / norm_term;
}

// Returns a random floating point value from [0, x]
float rand_float(int x)
{
    // You shouldn't have called this function!
    if (x <= 0) return 0;

    return (float) rand() / (float) (RAND_MAX / x);
}
// [-1, 1]
void matrix_randomize(matrix *M)
{
    if (!M)
        bad_ref("randomize");

    srand(time(NULL));

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] = rand_float(2) - 1;
}

