#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 30
#define __max(x, y) (x)<(y)?(x):(y)
#define INF (1<<25)
const int temp = 2;
typedef struct
{
    int ar[100][100];
}G;
G gph;
int vis[100] = { 0 };
int valid[100] = { 0 };
int num =0;
int postnumb[100] = {0};
int postnumbed[100] = {0};
int nnn=0;
void init()
{
    memset(&gph, 0, sizeof(gph));
}
void addEdge(int a, int b)
{
    gph.ar[a][b] = 1;
}
void _visit(int i)
{
    if (vis[i] == temp)
        return;
    if (vis[i] == 1)
        return;
    vis[i] = temp;
    ++num;
    int j;
    for(j=0; j<100; ++j)
    {
        if (gph.ar[i][j] == 1)
            _visit(j);
    }
    postnumb[i] = num;
    postnumbed[nnn++] = i;
    printf("%d ", i);
    vis[i] = 1;
}
void topsort()
{
    int i;
    for(i=0; i<100; ++i)
    {
        if (valid[i])
        _visit(i);
    }
}
int is_unique(int ar[], const int n)
{
    int i, j;
    for(i=0; i<n; ++i)
    {
        for (j = i + 1; j<n; ++j)
        {
            if (ar[i] == ar[j])
                return ar[i];
        }
    }
    return -INF;
}
int srt(int ar[], const int n)
{
    int i, j;
    int ret = -INF;
    for(i=0; i<n; ++i)
    {
        for (j = i + 1; j<n; ++j)
        {
            if (ar[i] == ar[j])
                ret = ar[i];
            if (ar[i] > ar[j])
                addEdge(ar[i], ar[j]);
            else
                addEdge(ar[j], ar[i]);
        }
        valid[ar[i]] = 1;
    }
    return ret;
}
void gen(int arr[], const int n)
{
    int is[100] = { 0 };
    int i;
    for(i=0; i<n; ++i)
    {
        do
        {
            arr[i] = rand() % 50;
        } while (is[arr[i]] == 1);
        is[arr[i]] = 1;
        printf("%d ", arr[i]);
    }
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int arr[100] = { 3, 1, 4, 7, 10, 11 };
    int n = 6;
    if (argc == 1)
    {
        printf("Invalid num args\nCommand line input was expected\nRunning with default number\n");
        putchar('\n');
        int i;
        for(i=0; i<n; ++i)
            printf("%d ", arr[i]);
        putchar('\n');
    }
    else if (argc == 2)
    {
        n = atoi(argv[1]);
        printf("In : ");
        gen(arr, n);
        putchar('\n');;
    }
    else
    {
        n = atoi(argv[1]);
        int i;
        printf("In : ");
        for(i=0; i<n; ++i)
            printf("%d ", arr[i] = atoi(argv[i + 2]));
        putchar('\n');;
    }
    init();
    int x = srt(arr, n);
    if (x == -INF)
    {
        printf("No repetitions\n");
    }
    else
    {
        printf("Repition :");
        printf("%d ", x);
        putchar('\n');
    }
    printf("Topsort: ");
    topsort();
    putchar('\n');
    return 0;
}