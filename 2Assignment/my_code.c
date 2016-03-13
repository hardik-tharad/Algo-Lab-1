#define NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define MAX 100
#define delta 1e-8
typedef struct{
    float x, y;
}point;
point arr[MAX];
float _min(float a, float b)
{
    if (a > b)
        return b;
    return a;
}
float _dist_(point x, point y)
{
    return sqrt((x.x - y.x)*(x.x - y.x) + (x.y - y.y)*(x.y - y.y));
}
void gen_rand(int n)
{
    int i;
    srand(time(NULL));
    for(i=0;i<n;++i)
    {
        arr[i].x = (rand()%100)/4.0 - 4.2;
        arr[i].y = (rand()%100)/7.0 - 4.2;
        printf("%f %f\n",arr[i].x,arr[i].y);
    }
}
int chk(float a)
{
    if(a==0.0)
        return 0;
    if(a<0.0f)
        return -1;
    return 1;
 
}
int cmpX(const void* a, const void* b)
{
    point xx = *(point*)a,yy = *(point*)b;
    if (xx.x != yy.x) {
        return chk(xx.x - yy.x);
    }
    return chk(xx.y - yy.y);
}
int cmpN(const void* a, const void* b)
{
    return (int*)a - (int*)b;
}
 
int get_id_low(int low, int mid ,int high, float c)
{
    assert(high >= low);
    assert(mid >= low);
    assert(high >= mid);
 
    int i;
    for (i = mid; i >= low; --i) {
        if (arr[i].x < c)
            return i;
    }
    assert(0);
    return 0;
}
#define INF 9999999.0
 
float _do(int low, int high)
{
    if (high - low == 1) {
        return _dist_(arr[low], arr[high]);
    }
    if (high - low < 1) {
        return INF;
    }
 
    int mid = (low + high) / 2;
    float a = _do(low, mid);
    float b = _do(mid, high);
 
    float c = _min(a, b);
    assert(c>-1e-8);
    float midx = arr[mid].x;
    int low_id = get_id_low(low, mid, high, midx - c);
    int i, j;
    float min_v = c;
    for (i = low_id; i < mid; ++i) {
        for (j = mid; j <= high; ++j) {
            assert(_dist_(arr[i], arr[j]) > 0.0f);
            min_v = _min(min_v, _dist_(arr[i], arr[j]));
        }
    }
 
    return min_v;
 
}
int main()
{
    printf("Enter n\n");
    int n, i;
    scanf("%d", &n);
    printf("type 0 to generate points randomly else type otherwise");
    scanf("%d", &i);
    if(i == 0) {
        gen_rand(n);
    }
    else {
        printf("Enter all points (x y)\n"); 
        for(i=0;i<n;++i)
            scanf("%f%f", &arr[i].x, &arr[i].y);
    }
    qsort(arr, n, sizeof(point), cmpX);
    printf("Minimum distance is:\n%f\n", _do(0, n - 1));
    return 0;
}