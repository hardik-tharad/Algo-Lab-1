#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
// #define N 3
#define MAX 30
#define REP(i, n) for(i=0; i<n; ++i)
#define REP2(i, j, n) for(i=0; i<n; ++i) for(j=0; j<n; ++j)
#define pri(n) printf("%d ", n);
#define print(n) //printf("%d ", n);
#define prs(n) printf("%s", n);
#define space putchar(' ');
#define endl putchar('\n');
#define __max(x, y) (x)<(y)?(x):(y)
#define INF (1<<25)
const int temp = 2;
typedef struct{
    int ar[100][100];
}G;
G gph;
void init() { memset(&gph, 0, sizeof(gph)); }
void addEdge(int a, int b) { gph.ar[a][b] = 1; }

int vis[100] = { 0 };
int valid[100] = { 0 };
void _visit(int i);
int num =0;
int postnumb[100] = {0};
int postnumbed[100] = {0};
int nnn=0;
void topsort()
{
    int i;
    REP(i, 100) {
        if (valid[i])
        _visit(i);
    }
}

void _visit(int i)
{
    if (vis[i] == temp) {
        return; //not DAG
    }
    if (vis[i] == 1)
        return;
    vis[i] = temp;
    ++num;
    // int ok = 0;
    int j;
    REP(j, 100) {
        if (gph.ar[i][j] == 1) {
            // ok = 1;
            _visit(j);
        }
    }
//  if (ok)
    postnumb[i] = num;
    postnumbed[nnn++] = i;
    pri(i);
    vis[i] = 1;
}
void printwithpostnumb()
{
    int i;
    REP(i, nnn)
        print(postnumbed[i]);
}
int is_unique(int ar[], const int n)
{
    int i, j;
    REP(i, n) {
        for (j = i + 1; j<n; ++j) {
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
    REP(i, n) {
        for (j = i + 1; j<n; ++j) {
            if (ar[i] == ar[j])
                ret = ar[i];

            if (ar[i] > ar[j]) {
                addEdge(ar[i], ar[j]);
            }
            else {
                addEdge(ar[j], ar[i]);
            }
        }
        valid[ar[i]] = 1;
    }
    return ret;
}
void gen(int arr[], const int n)
{
    int is[100] = { 0 };
    int i;
    REP(i, n){
        do{
            arr[i] = rand() % 50;
        } while (is[arr[i]] == 1);
        is[arr[i]] = 1;
        pri(arr[i]);
    }
}
int main(int argc, char *argv[])
{
    int arr[100] = { 3, 1, 4, 7, 10, 11 };
    int n = 6;

    if (argc == 1) {
        prs("Invalid num args\nCommand line input was expected\nRunning with default number\n");
        endl;
        int i;
        REP(i, n)pri(arr[i]); endl;

//      return -1;
    }
    else if (argc == 2) {
        n = atoi(argv[1]);
        prs("In : ");
        gen(arr, n);
        endl;
    }
    else {
        n = atoi(argv[1]);
        int i;
        prs("In : ");
        REP(i, n)
            pri(arr[i] = atoi(argv[i + 2]));
        endl;
    }
    init();
    int x = srt(arr, n) ;
    if (x == -INF){
        prs("No repetitions\n");
    }
    else {
        prs("Repition :");
        pri(x);
        endl;
    }
    prs("Topsort: ");
    topsort();
    endl;
    return 0;
}