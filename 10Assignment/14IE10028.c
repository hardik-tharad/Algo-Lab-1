#include <stdio.h>
#include <math.h>
#define N 3
#define INF 10000
//int tread[N][N] = {{100, 199, 0}, {45, 100, 45}, {200, 0, 100}};
int tread[N][N] = {{100, 200, 400}, {50, 100, 220}, {25, 45, 100}};
double tconv[N][N];
void read()
{
    int i,j;
    /*
    for(i=0; i<N; ++i)
    {
        for(j=0; j<N; ++j)
            scanf("%d", &tread[i][j]);
    }
    putchar('\n'); */
    for(i=0; i<N; ++i)
    {
        for(j=0; j<N; ++j)
        {
            if (tread[i][i] == 0)
                tconv[i][j] = -INF;
            else if (tread[i][j] == 0)
                tconv[i][j] = +INF;
            else
                tconv[i][j] = -log10(tread[i][j]/ (double)tread[i][i]);
            if(tconv[i][j]>-1e-8 && tconv[i][j]<1e-8)
                tconv[i][j]=0.0;
        }
    }
}
void printMatrixInt(int a[][N])
{
    int i,j;
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        printf("%d\t", a[i][j]);
        printf("\n");
    }
    printf("\n");
}
void printMatrixDouble(double a[][N])
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
int find_path()
{
    double dp[N][N];
    int next[N][N];
    int i,j,k;
    for(i=0; i<N; ++i)
    {
        for(j=0; j<N; ++j)
        {
            dp[i][j] = tconv[i][j];
            next[i][j]=j;
        }
    }
    for(k=0; k<N; ++k)
    {
        for(i=0; i<N; ++i)
        {
            for(j=0; j<N; ++j)
            {
                if(dp[i][k]+dp[k][j]< dp[i][j])
                {
                    dp[i][j]= dp[i][k]+dp[k][j];
                    next[i][j]=next[i][k];
                }
            }
        }
    }
    for(i=0; i<N; ++i)
    {
        if(dp[i][i] < 0.0)
        {
            int run = i;
            int cnt = 0;
            do
            {
                printf("%d ", run+1);
                run = next[run][i];
                cnt++;
                if (cnt >= N)
                    break;
            }
            while(run != i);
            putchar('\n');
            return 1;
        }
    }
    return 0;
}
int main()
{
    read();
    printf("Convertion Matrix:\n");
    printMatrixInt(tread);
    printf("Path:\n");
    if(find_path() == 0)
        printf("Not possible\n");
    return 0;
}