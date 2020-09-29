//#define TEST
#include "problem.h"

int main(void)
{
    double **matrixA = getMatrix(M_SIZE, N_SIZE, 1.1);
    double **matrixB = getMatrix(N_SIZE, P_SIZE, 1.1);
    double **matrixC = getMatrix(M_SIZE, P_SIZE, 0.0);
    const clock_t startTime = clock();
    for (int i = 0; i < M_SIZE; ++i)
        for (int j = 0; j < P_SIZE; ++j)
        {
            double temp = 0.0;
            for (int k = 0; k < N_SIZE; ++k)
                temp += matrixA[i][k] * matrixB[k][j];
            matrixC[i][j] = temp;
        }
#ifndef TEST
    printf("%lf", ((double)(clock() - startTime)) / CLOCKS_PER_SEC);
#else
    printf("%lf", matrixC[M_SIZE - 1][P_SIZE - 1]);
#endif
}
