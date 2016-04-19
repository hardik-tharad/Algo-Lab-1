#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 100
int check[2*N+1];
int partition(int arr[], int l, int r, int k);
int comp(const void *a,const void *b)
{
    return (*(int *)a > *(int*)b);
}
int min(int a,int b)
{
    return (a<b)?a:b;
}
int max(int a,int b)
{
    return (a>b)?a:b;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printMatrix(int A[], int n)
{
    int i,j;
    for (i = 0; i < n; ++i)
        printf("%d\t", A[i]);
    printf("\n");
}
void generate(int A[], int n)
{
    int i,k;
    for (i = 0; i < n; ++i)
    {
        k=rand()%(2*N)+1;
        while(check[k]==1)
            k=rand()%(2*N)+1;
        check[k]=1;
        A[i]=k;
    }
}
int create(int A[], int B[], int n)
{
    generate(A,n);
    generate(B,n);
    printf("The two lists are:\n");
    printMatrix(A,n);
    printMatrix(B,n);
    return n;
}
int giveMedian(int arr[], int n)
{
    qsort(arr,n,sizeof(int),comp);
    return arr[n/2];
}
int find_k_func(int arr1[], int arr2[], int n1, int n2, int k)
{
    int k2 = max(1, (k - 1) / 2);
    int a = sendKthSmallest(arr1, 0, n1 - 1, min(k2,n1));
    int b = sendKthSmallest(arr2, 0, n2 - 1, min(k2,n2));
    if (k < 2)
        return min(a, b);
    int last1 = min(n1, n1 );
    if (arr1[last1] == -10000 || arr1[last1] >(1 << 15));
    int last2 = min(n2, n2 );
    if (arr2[last2] == -10000 || arr2[last2] > (1 << 15));
    if (b == a)
        return find_k_func(arr1 + min(k2, n1), arr2 + min(k2, n2), n1 - min(k2, n1), n2 - min(k2, n2), k - k2 * 2);
    else if (b < a)
        return find_k_func(arr1, arr2 + min(k2, n2), last1, n2 - min(k2, n2), k - k2);
    else
        return find_k_func(arr1+min(k2, n1), arr2 , n1-min(k2, n1), last2, k - k2);
}
int sendKthSmallest(int arr[], int l, int r, int k)
{
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1;
        int i, median[(n+4)/5];
        for (i=0; i<n/5; i++)
            median[i] = giveMedian(arr+l+i*5, 5);
        if (i*5 < n)
        {
            median[i] = giveMedian(arr+l+i*5, n%5);
            i++;
        }
        int mainMed = (i == 1)? median[i-1]:
        sendKthSmallest(median, 0, i-1, i/2);
        int pos = partition(arr, l, r, mainMed);
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)
            return sendKthSmallest(arr, l, pos-1, k);
        return sendKthSmallest(arr, pos+1, r, k-pos+l-1);
    }
    return 10000;
}
int partition(int arr[], int l, int r, int x)
{
    int i,j;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);
    i = l;
    for (j = l; j < r; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int small,n,a[N],b[N];
    if(argc==2)
        n=atoi(argv[1]);
    else 
        return 0;
    create(a,b,n);
    int k=rand()%(n-2)+1;
    printf("Value of k is : %d\n",k);
    small=find_k_func(a,b,n,n,k);
    printf("kth smallest element is : %d\n",small);
    return 0;
}