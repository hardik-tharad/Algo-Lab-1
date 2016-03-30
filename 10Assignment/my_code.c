#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define N 3
//double tread[N][N] = {{100, 199, 0}, {45, 100, 45}, {200, 0, 100}};
double tread[N][N] = {{100, 200, 400}, {50, 100, 220}, {25, 45, 100}};
void printMatrix(double a[][N])
{
    int i,j;
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        printf("%f\t", a[i][j]);
        printf("\n");
    }
    printf("\n");
}
void read()
{
    /* int i,j;
    for(i=0; i<N; ++i)
    {
        for(j=0; j<N; ++j)
            scanf("%d", &tread[i][j]);
    }
    putchar('\n'); */
    printf("Convertion Matrix:\n");
    printMatrix(tread);
}
int find_profit()
{
    double temp[N][N];
    int path[N][N];
    int i,j,k;
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
            temp[i][j]=tread[i][j];
    }
    for(k=0; k<N; ++k)
    {
        for(i=0; i<N; ++i)
        {
            for(j=0; j<N; ++j)
            {
                if(temp[i][k]*temp[k][j]/temp[i][i] > temp[i][j])
                    temp[i][j] = temp[i][k]*temp[k][j]/temp[i][i];
            }
        }
    }
    printf("Max Sum Matrix:\n");
    printMatrix(temp);
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
            temp[i][j]=temp[i][j]-tread[i][j];
    }
    printf("Profit Matrix:\n");
    printMatrix(temp);
    for (i = 0; i < N; ++i)
    {
        if(temp[i][i]>0)
            return 1;
    }
    return 0;
}
int main()
{
    read();
    if(find_profit() == 0)
        printf("Not possible\n");
    else
        printf("Path present\n");
    return 0;
}