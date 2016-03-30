#include <stdio.h>
#include <math.h>
#define N 3
#define REP(i, n) for(i=0; i<n; ++i)
#define REP2(i, j, n) for(i=0; i<n; ++i) for(j=0; j<n; ++j)
#define pri(n) printf("%d ", n);
#define space putchar(' ');
#define endl putchar('\n');
#define __max(x, y) (x)<(y)?(x):(y)
#define INF (1<<25)
#define prd(n) {if(n>=INF/2.0) printf(" INF    "); else { if(n>=0.0) space; printf("%.4lf ", n);} }
#define NO_WARNINGS
#define DONT_PRINT_INPUT
#define NO_INTERMIDIATES
double maxlf(double a, double b) {
    return __max(a, b);
}
int tread[N][N];
double tconv[N][N];
void read()
{
    int i,j;
    REP(i, N) {
        REP(j, N) {
            scanf("%d", &tread[i][j]);
#ifndef NO_WARNINGS
                printf("Warning: zero detected\n");
#endif
#ifndef DONT_PRINT_INPUT
            pri(tread[i][j]);
#endif
        }
#ifndef DONT_PRINT_INPUT
        endl
#endif
    }

    REP(i, N) {
        REP(j, N) {
            if (tread[i][i] == 0) {
                tconv[i][j] = -INF;
                // printf("Warning: zero detected\n");
            } else if (tread[i][j] == 0) {
                tconv[i][j] = +INF;
                // printf("Warning: zero detected\n");
            } else {
                tconv[i][j] = -log10(tread[i][j]/ (double)tread[i][i]);
            }
            if(tconv[i][j]>-1e-8 && tconv[i][j]<1e-8)
                tconv[i][j]=0.0;
        }
#ifndef NO_INTERMIDIATES
        endl
#endif
    }
}
int find_if()
{
    double dp[N][N];
    int i,j, k, i2, j2;

    REP2(i, j, N) {
        dp[i][j] = tconv[i][j];
    }

    REP(k, N) {
        REP2(i, j, N) {
            dp[i][j] = maxlf(dp[i][k]+dp[k][j], dp[i][j]);
        }
        REP2(i2, j2, N) {
            if (j2 == 0) endl
            prd(dp[i2][j2]);
        }
        endl

    }
    endl
    REP2(i, j, N) {
        if (j == 0) endl
        prd(dp[i][j]);
    }
    endl

    REP(i, N) {
        if(dp[i][i] < 0.0)
            return 1;
    }
    return 0;
}
int find_if_with_path()
{
    double dp[N][N];
    int next[N][N];
    int i,j, k;

    REP2(i, j, N) {
        dp[i][j] = tconv[i][j];
        next[i][j]=j;
    }

    REP(k, N) {
        REP2(i, j, N) {
            if(dp[i][k]+dp[k][j]< dp[i][j]) {
                dp[i][j]= dp[i][k]+dp[k][j];
                next[i][j]=next[i][k];
            }
        }
#ifndef NO_INTERMIDIATES
        int i2, j2;
        REP2(i2, j2, N) {
            if (j2 == 0) endl
            prd(dp[i2][j2]);
        }
        endl
#endif
    }
#ifndef NO_INTERMIDIATES
    endl
    REP2(i, j, N) {
        if (j == 0) endl
        prd(pow(10.0, -dp[i][j]));
    }
    endl
#endif
    REP(i, N) {
        if(dp[i][i] < 0.0) {
            int run = i;
#ifndef NO_INTERMIDIATES
            printf("run = %d\n", i);
#endif
            // system("sleep 1");
            int cnt = 0;
            do {
                pri(run);
                fflush(stdout);
                run = next[run][i];
                cnt++;
                if (cnt > N) break;
                // system("sleep 1");
            }while(run != i);
            endl
            return 1;
        }
    }
    return 0;
}
int main()
{
    read();

    if(find_if_with_path() == 0) {
        printf("Not possible\n");
    } else {
        printf("Yes, path is shown above\n");
    }

    // endl
    return 0;
}
/**
100 199 0
 45  100 45
 200  0 100
Ans : 0 1 2, Yes
 100 199 0
 45  100 45
 100  0 100
Ans : No
**/