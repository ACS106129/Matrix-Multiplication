//#define TEST
#include "problem.h"

void loopFunc(const int block_i, const int block_j, const int block_k, double ***matrixes)
{
    double **matrixC = matrixes[1];
    double **submatrixA = getSubmatrix(matrixes[0], block_i, block_k, M_SUB_SIZE, N_SUB_SIZE);
    double **subtransposeB = getSubmatrix(matrixes[2], block_j, block_k, P_SUB_SIZE, N_SUB_SIZE);
    for (int i = 0; i < M_SUB_SIZE; ++i)
        for (int j = 0; j < P_SUB_SIZE; ++j)
        {
            const double *colB = subtransposeB[j];
            double temp = 0.0;
            for (int k = 0; k < N_SUB_SIZE; ++k)
                temp += submatrixA[i][k] * colB[k];
            matrixC[block_i + i][block_j + j] += temp;
        }
}

int main(void)
{
    double **matrixA = getMatrix(M_SIZE, N_SIZE, 1.1);
    double **matrixB = getMatrix(N_SIZE, P_SIZE, 1.1);
    double **matrixC = getMatrix(M_SIZE, P_SIZE, 0.0);
    const clock_t startTime = clock();
    double **transposeB = getReflectedMatrix(matrixB, N_SIZE, P_SIZE);
    blocksLoop(loopFunc, 3, matrixA, matrixC, transposeB);
#ifndef TEST
    printf("%lf", ((double)(clock() - startTime)) / CLOCKS_PER_SEC);
#else
    printf("%lf", matrixC[M_SIZE - 1][P_SIZE - 1]);
#endif
}