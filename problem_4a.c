//#define TEST
#include "problem.h"

int main(void)
{
    double **matrixA = getMatrix(M_SIZE, N_SIZE, 1.1);
    double **matrixB = getMatrix(N_SIZE, P_SIZE, 1.1);
    double **matrixC = getMatrix(M_SIZE, P_SIZE, 0.0);
    const clock_t startTime = clock();
    double **transposeB = getReflectedMatrix(matrixB, N_SIZE, P_SIZE);
    for (int block_i = 0; block_i < M_SIZE; block_i += M_SUB_SIZE)
        for (int block_j = 0; block_j < P_SIZE; block_j += P_SUB_SIZE)
            for (int block_k = 0; block_k < N_SIZE; block_k += N_SUB_SIZE)
                for (int i = 0; i < M_SUB_SIZE; ++i)
                    for (int j = 0; j < P_SUB_SIZE; ++j)
                    {
                        const double *colB = transposeB[block_j + j];
                        double temp = 0.0;
                        for (int k = 0; k < N_SUB_SIZE; ++k)
                            temp += matrixA[block_i + i][block_k + k] * colB[block_k + k];
                        matrixC[block_i + i][block_j + j] += temp;
                    }
#ifndef TEST
    printf("%lf", ((double)(clock() - startTime)) / CLOCKS_PER_SEC);
#else
    printf("%lf", matrixC[M_SIZE - 1][P_SIZE - 1]);
#endif
}