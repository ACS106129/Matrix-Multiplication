#pragma once
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef TEST
#define M_SIZE 2500u
#define N_SIZE 2500u
#define P_SIZE 2500u
#define BLOCK_RATE 5u
#else
#define M_SIZE 10u
#define N_SIZE 10u
#define P_SIZE 10u
#define BLOCK_RATE 2u
#endif
#define M_SUB_SIZE (M_SIZE / BLOCK_RATE)
#define N_SUB_SIZE (N_SIZE / BLOCK_RATE)
#define P_SUB_SIZE (P_SIZE / BLOCK_RATE)

/** 
 * Get the dynamical matrix
 * @param row row size
 * @param col col size
 * @param val initial value
 * @return new dynamical matrix
 */
static double **getMatrix(const int row, const int col, const double val)
{
    double **matrix = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; ++i)
    {
        matrix[i] = (double *)malloc(col * sizeof(double *));
        for (int j = 0; j < col; ++j)
            matrix[i][j] = val;
    }
    return matrix;
}

/**
 * Get reflected matrix from origin one
 * @param matrix dynamical matrix
 * @param row    matrix row size
 * @param col    matrix col size
 * @return reflected matrix
 */
static double **getReflectedMatrix(double **matrix, const int row, const int col)
{
    double **reflect = getMatrix(row, col, 0.0);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            reflect[j][i] = matrix[i][j];
    return reflect;
}

/**
 * Get the submatrix from origin matrix
 * @param matrix   origin matrix
 * @param startRow start row index of matrix
 * @param startCol start column index of matrix
 * @param rowSize  row size of submatrix
 * @param colSize  column size of submatrix
 * @return submatrix
 */
static double **getSubmatrix(double **matrix, const int startRow, const int startCol, const int rowSize, const int colSize)
{
    double **submatrix = getMatrix(rowSize, colSize, 0.0);
    for (int i = 0; i < rowSize; ++i)
        for (int j = 0; j < colSize; ++j)
            submatrix[i][j] = matrix[i + startRow][j + startCol];
    return submatrix;
}

/**
 * Loop against the block function
 * @param loopFunc function of looping block size of param i, j, k and matrixes
 * @param matrixSize numbers of splatting matrixes
 */
static void blocksLoop(void (*loopFunc)(const int block_i, const int block_j, const int block_k, double ***matrixes), const int matrixSize, ...)
{
    va_list args;
    va_start(args, matrixSize);
    double ***mats = malloc(sizeof(double **) * matrixSize);
    for (int i = 0; i < matrixSize; ++i)
        mats[i] = va_arg(args, double **);
    for (int bi = 0; bi < M_SIZE; bi += M_SUB_SIZE)
        for (int bj = 0; bj < P_SIZE; bj += P_SUB_SIZE)
            for (int bk = 0; bk < N_SIZE; bk += N_SUB_SIZE)
                (*loopFunc)(bi, bj, bk, mats);
    va_end(args);
}
