//#define TEST
#include "problem.h"

int main(void)
{
    double **matrixA = getMatrix(M_SIZE, N_SIZE, 1.1);
    double **matrixB = getMatrix(N_SIZE, P_SIZE, 1.1);
    double **matrixC = getMatrix(M_SIZE, P_SIZE, 0.0);
    const clock_t startTime = clock();
    for (int i = 0; i < M_SIZE; ++i)
        for (int k = 0; k < N_SIZE; ++k)
        {
            const double temp = matrixA[i][k];
            for (int j = 0; j < P_SIZE; ++j)
                matrixC[i][j] += temp * matrixB[k][j];
        }
#ifndef TEST
    printf("%lf", ((double)(clock() - startTime)) / CLOCKS_PER_SEC);
#else
    printf("%lf", matrixC[M_SIZE - 1][P_SIZE - 1]);
#endif
}
