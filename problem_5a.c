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
            for (int block_k = 0; block_k < N_SIZE; block_k += N_SUB_SIZE){
                double **submatrixA = getSubmatrix(matrixA, block_i, block_k, M_SUB_SIZE, N_SUB_SIZE);
                double **subtransposeB = getSubmatrix(transposeB, block_j, block_k, P_SUB_SIZE, N_SUB_SIZE);
                for (int i = 0; i < M_SUB_SIZE; ++i)
                    for (int j = 0; j < P_SUB_SIZE; ++j)
                    {
                        const double *subcolB = subtransposeB[j];
                        double temp = 0.0;
                        for (int k = 0; k < N_SUB_SIZE; ++k)
                            temp += submatrixA[i][k] * subcolB[k];
                        matrixC[block_i + i][block_j + j] += temp;
                    }
            }
#ifndef TEST
    printf("%lf", ((double)(clock() - startTime)) / CLOCKS_PER_SEC);
#else
    printf("%lf", matrixC[M_SIZE - 1][P_SIZE - 1]);
#endif
}