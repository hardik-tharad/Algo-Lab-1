/*Binary Trees
Shashwat Gupta
14IE10028 */
#include <stdio.h>
#include <stdlib.h>
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
typedef struct node
{
    int data;
    struct node *lChild, *rChild;
}node;
int a[100];
int k=0;
node* create(int n, node *pointer)
{
    if(n==0)
        return pointer;
    int d,parity;
    float p;
    d=rand()%101;
    parity=rand()%2;
    if(parity==1)
    d=d*-1;
    node *temp = (node*)malloc(sizeof(node));
    temp->data=d;
    if(n==1)
    {
        temp->lChild=NULL;
        temp->rChild=NULL;
        pointer=temp;
        return pointer;
    }
    p=0.4+(rand()%21)/100.0;
    int m=p*n;
    temp->lChild=create(m, temp->lChild);
    temp->rChild=create(n-m-1, temp->rChild);
    pointer=temp;
    return pointer;
}
void preorder(node *t)
{
    if(t==NULL)
        return;
    printf("%d ",t->data);
    preorder(t->lChild);
    preorder(t->rChild);
}
void inorder(node *t)
{
    if(t==NULL)
        return;
    inorder(t->lChild);
    printf("%d ",t->data);
    inorder(t->rChild);
}
void postorder(node *t)
{
    if(t==NULL)
        return;
    postorder(t->lChild);
    postorder(t->rChild);
    printf("%d ",t->data);
}
int revPrint(node *root, node *point)
{
    if (root == NULL)
        return 0;
    if (root==point || revPrint(root->lChild, point)==1 || revPrint(root->rChild, point)==1)
    {
        a[k]=root->data;
        k++;
        return 1;
    }
    return 0;
}
int printPath (node *root, node *point)
{
    if (root == NULL)
        return 0;
    if (root==point || printPath(root->lChild, point)==1 || printPath(root->rChild, point)==1)
    {
        printf("%d ", root->data);
        return 1;
    }
    return 0;
}
void Final (node *t, int *max, int sum, node **point_node)
{
    if (t == NULL)
        return;
    sum = sum + t->data;
    if (t->lChild == NULL && t->rChild == NULL)
    {
        if (sum > *max)
        {
            *max = sum;
            *point_node = t;
        }
    }
    Final (t->lChild, max, sum, point_node);
    Final (t->rChild, max, sum, point_node);
}
int maxSumPathRoot (node *t)
{
    if (t == NULL)
        return 0;
    node *point_node;
    int max_sum = -100;
    Final (t, &max_sum, 0, &point_node);
    printPath (t, point_node); 
    return max_sum;
}
int revmaxSumPathRoot (node *t)
{
    if (t == NULL)
        return 0;
    node *point_node;
    int max_sum = -100;
    Final (t, &max_sum, 0, &point_node);
    revPrint (t, point_node); 
    return max_sum;
}
int maxSumFunc(node *root, int *final, node **nodeBothChild)
{
    if (root == NULL)
        return 0;
    int l = maxSumFunc(root->lChild,final,nodeBothChild);
    int r = maxSumFunc(root->rChild,final,nodeBothChild);
    int max_single = MAX(MAX(l, r) + root->data, root->data);
    int maxBothChild = MAX(max_single, l + r + root->data);
    if(maxBothChild>*final)
    {
        *final=maxBothChild;
        *nodeBothChild=root;
    }
    return max_single;
}
int main()
{
    int i;
    srand(time(NULL));
    node *root = (node*)malloc(sizeof(node));
    node *nodeBothChild = (node*)malloc(sizeof(node));
    root = create(100, root);
    preorder(root);
    printf("\n\n");
    inorder(root);
    printf("\n\n");
    postorder(root);
    printf("\n\n");
    int sum = revmaxSumPathRoot(root);
    for(i=k-1;i>=0;i--)
        printf("%d ",a[i]);
    printf("\n\n");
    k=0;
    sum = -100;
    i=maxSumFunc(root, &sum, &nodeBothChild);
    maxSumPathRoot(nodeBothChild->lChild);
    printf("%d ", nodeBothChild->data);
    revmaxSumPathRoot(nodeBothChild->rChild);
    for(i=k-1;i>=0;i--)
        printf("%d ",a[i]);
    printf("\n\n");
}