/*Fibonacci Heaps   Shashwat Gupta  14IE10028 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
typedef struct _node
{
    struct _node *parent,*left,*right,*child;
    int key,degree;
    bool mark;
}node;
int b[10001];
typedef struct _heap
{
    node *root,*min;
    int n;
}heap;
heap* initHeap()
{
    heap* h = (heap *)malloc(sizeof(heap));
    h->root=NULL;
    h->min=NULL;
    h->n=0;
    return h;
}
node* initNode(int n)
{
    node *N = (node *)malloc(sizeof(node));
    N->parent=NULL;
    N->left=NULL;
    N->right=NULL;
    N->child=NULL;
    N->key=n;
    N->degree=0;
    N->mark=0;
    return N;
}
heap* insertToHeap(heap *h,node *n)
{
    if(h->root==NULL)
    {
        h->root=n;
        h->root->left=NULL;
        h->root->right=NULL;
        h->root->parent=NULL;
        h->min=n;
        h->n++;
        return h;
    }
    if(h->min->key>n->key)
        h->min=n;
    node *temp;
    temp=h->root;
    while(temp->right!=NULL)
        temp=temp->right;
    temp->right=n;
    n->left=temp;
    n->right=NULL;
    n->parent=NULL;
    h->n++;
    return h;
}
heap* merge2Heaps(heap *h1, heap *h2)
{
    heap* h = (heap *)malloc(sizeof(heap));
    h->root=h1->root;
    h->n=h1->n+h2->n;
    h->min=(h1->min->key<h2->min->key)?(h1->min):(h2->min);
    node *temp = (node *)malloc(sizeof(node));
    temp=h1->root;
    while(temp->right!=NULL)
        temp=temp->right;
    temp->right=h2->root;
    h2->root->left=temp;
    return h;
}
node* extractMin(heap *h)
{
    node* oldMin=h->min;
    if(h->min==h->root)
    {
        if(h->root->right==NULL)
        {
            h->root=h->root->child;
            h->min=h->root;
            h->root->parent=NULL;
        }
        else
        {
            h->root=h->root->right;
            h->root->left=NULL;
            h->min=h->root;
        }
    }
    else if(h->min->right==NULL)
    {
        h->min->left->right=NULL;
        h->min=h->min->left;
    }
    else
    {
        h->min->left->right=h->min->right;
        h->min->right->left=h->min->left;
        h->min=h->min->right;
    }
    oldMin->left=NULL;
    oldMin->right=NULL;
    h->n--;
    if(oldMin->child==NULL)
        return oldMin;
    node *temp;
    temp=oldMin->child;
    node* A[h->n];
    int i;
    for (i = 0; i < h->n; i++)
        A[i] = NULL;
    i =0;
    while(temp!=NULL)
    {
        A[i]=temp;
        temp=temp->right;
        i++;
    }
    for(i=0;i<h->n;i++)
    {
        if(A[i]!=NULL)
        {
            h=insertToHeap(h,A[i]);
            h->n--;
        }
    }
    return oldMin;
}
node* linkHeap(heap* H,node* y, node* z)
{
    node* temp;
    if(y->left==NULL)
    {
        H->root=y->right;
        H->root->left=NULL;
    }
    else if(y->right==NULL)
        y->left->right=NULL;
    else
    {
        y->left->right = y->right;
        y->right->left = y->left;
    }
    if(z->child==NULL)
    {
        z->child=y;
        y->parent=z;
        y->left=NULL;
        y->right=NULL;
        y->mark=false;
    }
    else
    {
        temp = z->child;
        while(temp->right!=NULL)
            temp=temp->right;
        temp->right=y;
        y->left=temp;
        y->right=NULL;
        y->parent=z;
        y->mark=false;
    }
    z->degree++;
    return z;
}
heap* consolidateHeap(heap *H)
{
    if(H->root==NULL)
        return;
    int i,d;
    node* A[H->n];
    for (i = 0; i < H->n; i++)
        A[i] = NULL;
    node *z,*y,*x;
    x = H->root;
    while(x!=NULL)
    {
        d = x->degree;
        while(A[d]!=NULL)
        {
            y = A[d];
            if (x->key > y->key)
            {
                z = x;
                x = y;
                y = z;
            }
            x=linkHeap(H, y, x);
            A[d] = NULL;
            d = d + 1;
        }
        A[d] = x;
        x = x-> right;
    }
    H->min=NULL;
    H->root=NULL;
    for(i=0;i<H->n;i++)
    {
        if(A[i]!=NULL)
        {
            H=insertToHeap(H,A[i]);
            H->n--;
        }
    }
    return H;
}
heap* cut(heap *h, node* x, node* y)
{
    if(x==y->child)
    {
        if(x->right!=NULL)
        {
            y->child=x->right;
            x->right->left=NULL;
            x->right=NULL;
        }
        else
            y->child=NULL;
    }
    else
    {
        if(x->right!=NULL)
        {
            x->left->right=x->right;
            x->right->left=x->left;
            x->left=NULL;
            x->right=NULL;
        }
        else
        {
            x->left->right=NULL;
            x->left=NULL;
        }
    }
    h=insertToHeap(h,x);
    h->n--;
    x->parent=NULL;
    x->mark=0;
    return h;
}
heap* cascadingCut(heap *h, node* y)
{
    node *z=y->parent;
    if(z!=NULL)
    {
        if(y->mark==0)
            y->mark=1;
        else
        {
            h=cut(h,y,z);
            h=cascadingCut(h,z);
        }
    }
    return h;
}
heap* decKey(heap *h, node* x, int k)
{
    if(k>x->key)
    {
        printf("Error, key is greater than original\n");
        return h;
    }
    x->key=k;
    node *y=x->parent;
    if(y!=NULL && x->key < y->key)
    {
        h=cut(h,x,y);
        h=cascadingCut(h,y);
    }
    if(x->key < h->min->key)
        h->min=x;
    return h;
}
heap* removeFromHeap(heap *h, node *x)
{
    h=decKey(h,x,-10000);
    extractMin(h);
    h=consolidateHeap(h);
    return h;
}
void printHeap(heap *h)
{
    if(h->root==NULL)
        return;
    printf("Root = %d, Min = %d, Nodes = %d\n",h->root->key,h->min->key,h->n);
    node *temp = (node *)malloc(sizeof(node));
    temp=h->root;
    while(temp!=NULL)
    {
        printf("key = %d, degree = %d\n",temp->key,temp->degree);
        temp=temp->right;
    }
    printf("\n");
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    /* create temp arrays */
    int L[n1], R[n2]; 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r);
    }
}
void printArray(int A[], int size)
{
    printf("Printing list :\n");
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
heap* createHeap(int m)
{
    int a[m];
    heap *h;
    h=initHeap();
    int i,flag,d=0;
    for(i=1;i<=m;i++)
    {
        flag=0;
        while(flag==0)
        {
            d=rand()%10000+1;
            if(b[d]==0)
            {
                b[d]=1;
                flag=1;
            }
        }
        a[i-1]=d;
    }
    mergeSort(a,0,m-1);
    for (i = 0; i < m; ++i)
    {
        printf("%d ",a[i]);
        h=insertToHeap(h,initNode(a[i]));
    }
    printf("\n");
    return h;
}
int main()
{
    
    int m,k;
    k=3;
    m=4;
    heap *h;
    h=createHeap(m);
    int i,j;
    for (i = 1; i < k; i++)
    {
        heap *nh;
        nh = createHeap(m);
        node* temp = nh -> root;
        while(temp->right!=NULL)
            temp=temp->right;
        if(temp->key>h->min->key)
            nh=decKey(nh,temp,h->min->key-1);
        h=merge2Heaps(h,nh);
    }
    printf("Final Merged Heap :\n");
    h=consolidateHeap(h);
    printHeap(h);
    for (i = 0; i < k-1; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            printf("%d ",extractMin(h)->key);
            h=consolidateHeap(h);
        }
        printf("\n");
    }
    printHeap(h);
    printf("%d \n",extractMin(h)->key);
    h=consolidateHeap(h);
    printHeap(h);
    printf("%d \n",extractMin(h)->key);
    h=consolidateHeap(h);
    return 0;
}