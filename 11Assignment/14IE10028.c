#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define N 100
int check[2*N+1];
void printMatrix(int A[], int n)
{
    int i,j;
    for (i = 0; i < n; ++i)
        printf("%d ", A[i]);
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
void quickSort(int x[],int first,int last)
{
    int pivot,j,temp,i;
    if(first<last)
    {
        pivot=first;
        i=first;
        j=last;
        while(i<j)
        {
            while(x[i]<=x[pivot]&&i<last)
            i++;
            while(x[j]>x[pivot])
            j--;
            if(i<j)
            {
                temp=x[i];
                x[i]=x[j];
                x[j]=temp;
            }
        }
        temp=x[pivot];
        x[pivot]=x[j];
        x[j]=temp;
        quickSort(x,first,j-1);
        quickSort(x,j+1,last);
    }
}
int getAnswer(int A[], int B[], int n, int k)
{
    int i,C[N*2];
    for (i = 0; i < n; ++i)
    {
        C[i]=A[i];
        C[n+i]=B[i];
    }
    quickSort(C,0,2*n-1);
    return C[6];
}
/*
void pivotFunc(int A[], int left, int right, int k)
{
    if(right-left<k)
        return partition(A,left,right)
}

    function pivot(list, left, right)
     // for 5 or less elements just get median
     if right - left < 5:
         return partition5(list, left, right)
     // otherwise move the medians of five-element subgroups to the first n/5 positions
     for i from left to right in steps of 5
         // get the median of the i'th five-element subgroup
         subRight := i + 4
         if subRight > right:
             subRight := right

         median5 := partition5(list, i, subRight)
         swap list[median5] and list[left + floor((i - left)/5)]

     // compute the median of the n/5 medians-of-five
     return select(list, left, left + ceil((right - left) / 5) - 1, left + (right - left)/10)


int partition(int A[], int left, int right, int p)
{
    int pv=A[p];
    int i,k=A[right];
    A[right]=A[p];
    A[p]=k;
    int store=left;
    for (i = left; i < right; ++i)
    {
        if(A[i]<pv)
        {
            k=A[store];
            A[store]=A[i];
            A[i]=k;
            store++;
        }
    }
    k=A[right];
    A[right]=A[store];
    A[store]=k;
    return store;
}
int quickSelect(int A[], int left, int right, int n)
{
    int i;
    if(left==right)
        return left;
    for (i = 0; i < n; ++i)
    {
        p=pivotFunc(A,left,right);
        p=partition(A,left,right,p);
        if(n==p)
            return n;
        else if(n<p)
            right=p-1
        else
            left=p+1;
    }
} */
void groupWiseSort(int A[], int n, int k)
{
    int i=0;
    while(i<n)
    {
        int j=i+k-1;
        if(j>=n)
            j=n-1;
        quickSort(A,i,j);
        i=j+1;
    }
    printMatrix(A,n);
}
void medianArray(int A[], int mA[], int n, int k)
{
    int i;
    for (i = k-1; i < n; i+=k)
        mA[(i+1)/k-1]=A[i-k/2];
    if(i-n!=k-1)
        mA[(i+1)/k-1]=A[(i+n-k)/2];
    printMatrix(mA,(n+k-1)/k);
}
int main (int argc, char** argv)
{
    srand(time(NULL));
    int n,A[N],B[N];
    if(argc==2)
        n=atoi(argv[1]);
    else
        return 0;
    create(A,B,n);
    printf("Answer = %d\n",getAnswer(A,B,n,7));
    int k=5;
    printf("Group wise sorted lists are:\n");
    groupWiseSort(A,n,k);
    groupWiseSort(B,n,k);
    int mn = (n+k-1)/k, mA[N/k], mB[N/k];
    medianArray(A,mA,n,k);
    medianArray(B,mB,n,k);
    return 0;
}