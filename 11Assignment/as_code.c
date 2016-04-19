#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
int partition(int arr[], int l, int r, int k);

int comp(const void *a,const void *b)
{
    return (*(int *)a > *(int*)b);
}

int min(int a,int b)
{
    if(a<b)
        return a;
    else 
        return b;
}

int max(int a,int b)
{
    if(a>b)
        return a;
    else 
        return b;
} 
// A simple function to find median of arr[].  This is called
// only for an array of size 5 in this program.
int findMedian(int arr[], int n)
{
    qsort(arr,n,sizeof(int),comp);
    //sort(arr, arr+n);  // Sort the array
    return arr[n/2];   // Return middle element
}

// int recur_kelement(int a[],int b[],int size1,int size2,int k)
// {
//     int k1=kthSmallest(a,0,n-1,k/2);
//     int k2=kthSmallest(b,0,n-1,k/2);


// }

int k_botharr(int arr1[], int arr2[], const int n1, const int n2, const int k)
{
/*  if (n1 <= 1) {
        return max(*kthSmallest(arr2, 0, n2 - 1, k - n1), n1 == 0 ? INT_MIN : arr1[0]);
    } else if (n2 <= 1) {
        return max(*kthSmallest(arr1, 0, n1 - 1, k - n2), n2 == 0 ? INT_MIN : arr2[0]);
    }*/
    int k2 = max(1, (k - 1) / 2);
    int src[2] = { min(k2, n1), min(k2, n2) };
    int a = kthSmallest(arr1, 0, n1 - 1, src[0]);// -arr1;
    int b = kthSmallest(arr2, 0, n2 - 1, src[1]);// -arr2;
//  int a = arr1[ida], b = arr2[idb];
/*  pri(a); pri(b); pri(k);endl
    pr_arr(arr1, n1);
    pr_arr(arr2, n2);
    endl;*/
    if (k < 2)
        return min(a, b);
//  else if (k == 2)
//      return max(a, b);
    int last1 = min(n1, n1 );
    if (arr1[last1] == -999 || arr1[last1] >(1 << 15));
//      last1--;
    int last2 = min(n2, n2 );
    if (arr2[last2] == -999 || arr2[last2] > (1 << 15));
///     last2--;
    if (b == a) {
        return k_botharr(arr1 + src[0], arr2 + src[1], n1 - src[0], n2 - src[1], k - k2 * 2); // ?
    }
    else if (b < a) {
        return k_botharr(arr1, arr2 + src[1], last1, n2 - src[1], k - k2);
    }
    else {
        return k_botharr(arr1+src[0], arr2 , n1-src[0], last2, k - k2);
    }
}
 
// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; // Number of elements in arr[l..r]
 
        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr+l+i*5, n%5); 
            i++;
        }    
 
        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);
 
        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);
 
        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);
 
        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }
 
    // If k is more than number of elements in array
    return 999999;
}
 
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// It searches for x in arr[l..r], and partitions the array 
// around x.
int partition(int arr[], int l, int r, int x)
{
    // Search for x in arr[l..r] and move it to end
    int i,j;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);
 
    // Standard partition algorithm
    i = l;
    for (j = l; j <= r - 1; j++)
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
 
// Driver program to test above methods
int main(int argc, char *argv[])
{   srand(time(NULL));
    int small,n,k;
    int a[100];
    int b[100];
    if(argc==2)
        n=atoi(argv[1]);
    else 
        return 0;
    
    int done[1000] = { 0 },i;

    for(i=0;i<n;i++) {
        do{
            a[i] = rand() % 100;
        } while (done[a[i]] == 1);
        done[a[i]] = 1;
    }
    for(i=0;i<n;i++) {
        do{
            b[i] = rand() % 100;
        } while (done[b[i]] == 1);
        done[b[i]] = 1;
    }
    printf("array a   ");

    for(i=0;i<n;i++)
    {
        printf("%d    ",a[i]);

    }
    
    printf("\n\n\n\n");
    printf("array b   ");
    for(i=0;i<n;i++)
    {
        printf("%d   ",b[i]);
        
    }
    

    k=rand()%(n-2)+1;
    printf("\nvalue of k is %d\n",k);

    small=k_botharr(a,b,n,n,k );
    printf("\nkth smallest element is %d\n",small);
    return 0;
}