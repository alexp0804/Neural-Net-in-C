#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

// Helper functions for bad requests
void bad_ref(char *where)
{
    fprintf(stderr, "Invalid Matrix reference in matrix_%s()\n", where);
    exit(1);
}
void bad_dims(char *where)
{
    fprintf(stderr, "Invalid Matrix dimensions in matrix_%s()\n", where);
    exit(1);
}
void bad_mem(char *where)
{
    fprintf(stderr, "Memory allocation failure in matrix_%s()\n", where);
    exit(1);
}

Matrix *matrix_build(int row, int col)
{
    Matrix * M = (Matrix *) malloc(sizeof(Matrix));
    M->rows = row, M->cols = col;

    M->entries = (double **) malloc(sizeof(double *) * row);
    for (int i = 0; i < row; i++)
        M->entries[i] = (double *) calloc(col, sizeof(double));

    return M;
}

void matrix_delete(Matrix *M)
{
    if (!M)
        bad_ref("delete");

    for (int i = 0; i < M->rows; i++)
        free(M->entries[i]);

    free(M->entries);
    free(M);
}

void matrix_print(Matrix *M)
{
    if (!M)
        bad_ref("print");

    printf("Rows: %d\tCols: %d\n", M->rows, M->cols);
    for (int i = 0; i < M->rows; i++)
    {
        for (int j = 0; j < M->cols; j++)
        {
            printf("%.2f ", M->entries[i][j]);
        }
        printf("\n");
    }
}

void matrix_fill(Matrix *M, double value)
{
    if (!M)
        bad_ref("fill"); 

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] = value;
}

void matrix_clear(Matrix *M)
{
    if (!M)
        bad_ref("clear");

    matrix_fill(M, 0);
}

// After using this function the N matrix is no longer safe to use.
void matrix_set(Matrix *M, Matrix *N)
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

Matrix *matrix_copy(Matrix *M)
{
    if (!M)
        bad_ref("copy");

    Matrix *copy = matrix_build(M->rows, M->cols);
    if (!copy)
        bad_mem("copy");
    
    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            copy->entries[i][j] = M->entries[i][j];

    return copy;
}

Matrix *matrix_flatten(Matrix *M)
{
    if (!M)
        bad_ref("flatten");
    
    Matrix *new = matrix_build(M->rows * M->cols, 1);
    if (!new)
        bad_mem("flatten");
    
    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            new->entries[i * M->cols + j][0] = M->entries[i][j];

    return new;
}

void matrix_scale(Matrix *M, double s)
{
    if (!M)
        bad_ref("scale");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] *= s;
}

Matrix *matrix_add(Matrix *M, Matrix* N)
{
    if (!M || !N)
        bad_ref("add");

    if (M->rows != N->rows || M->cols != N->cols)
        bad_dims("add");

    Matrix *new = matrix_build(M->rows, M->cols);
    if (!new)
        bad_mem("add");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            new->entries[i][j] = M->entries[i][j] + N->entries[i][j];

    return new;
}

void matrix_add_scalar(Matrix *M, double s)
{
    if (!M)
        bad_ref("add_scalar");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] += s;
}

// M - N
Matrix *matrix_subtract(Matrix *M, Matrix *N)
{
    if (!M || !N)
        bad_ref("subtract");

    if (M->rows != N->rows || M->cols != N->cols)
        bad_dims("subtract");

    Matrix *new = matrix_build(M->cols, M->rows);
    if (!new)
        bad_mem("subtract");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            new->entries[i][j] = M->entries[i][j] - N->entries[i][j];

    return new;
}

Matrix *matrix_multiply(Matrix *M, Matrix* N)
{
    if (!M || !N)
        bad_ref("multiply");

    if (M->cols != N->rows)
        bad_dims("multiply");

    Matrix *new = matrix_build(M->rows, N->cols);
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

void matrix_sigmoid(Matrix *M)
{
    if (!M)
        bad_ref("sigmoid");

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] = sigmoid(M->entries[i][j]);
}

// [-1, 1)
void matrix_randomize(Matrix *M)
{
    if (!M)
        bad_ref("randomize");

    srand(time(NULL));

    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->cols; j++)
            M->entries[i][j] = rand() % 2 - 1;
}

