/*RBT   Shashwat Gupta  14IE10028*/
#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1
typedef struct node
{
    int id,extime,priority,colour;
    struct node *lChild, *rChild, *parent;
}node;
node n={0,10000,0,BLACK,NULL,NULL,NULL};
node nil={0,10000,0,BLACK,&n,&n,&n};
node* leftRotate(node* x, node* root)
{
    node *y = (node*)malloc(sizeof(node));
    y=x->rChild;
    x->rChild=y->lChild;
    if(y->lChild->extime<=1000)
        y->lChild->parent=x;
    y->parent=x->parent;
    if(x->parent->extime>1000)
        root=y;
    else if(x==x->parent->lChild)
        x->parent->lChild=y;
    else
        x->parent->rChild=y;
    y->lChild=x;
    x->parent=y;
    return root;
}
node* rightRotate(node* x, node* root)
{
    node *y = (node*)malloc(sizeof(node));
    y=x->lChild;
    x->lChild=y->rChild;
    if(y->rChild->extime<=1000)
        y->rChild->parent=x;
    y->parent=x->parent;
    if(x->parent->extime>1000)
        root=y;
    else if(x==x->parent->lChild)
        x->parent->lChild=y;
    else
        x->parent->rChild=y;
    y->rChild=x;
    x->parent=y;
    return root;
}
node* insertFix(node* z, node* root)
{
    node *x, *y;
    while(z->parent->colour==RED)
    {
        if(z->parent==z->parent->parent->lChild)
        {
            y=z->parent->parent->rChild;
            if(y->colour==RED)
            {
                z->parent->colour=BLACK;
                y->colour=BLACK;
                z->parent->parent->colour=RED;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->rChild)
                {
                    z=z->parent;
                    root=leftRotate(z,root);
                }
                z->parent->colour=BLACK;
                z->parent->parent->colour=RED;
                root=rightRotate(z->parent->parent,root);
            }
        }
        else
        {
            y=z->parent->parent->lChild;
            if(y->colour==RED)
            {
                z->parent->colour=BLACK;
                y->colour=BLACK;
                z->parent->parent->colour=RED;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->lChild)
                {
                    z=z->parent;
                    root=rightRotate(z,root);
                }
                z->parent->colour=BLACK;
                z->parent->parent->colour=RED;
                root=leftRotate(z->parent->parent,root);
            }
        }
    }
    if(z->parent->extime>1000)
        z->colour=BLACK;
    return root;
}
node* insert(node* z, node* root)
{
    node *x = (node*)malloc(sizeof(node));
    node *y = (node*)malloc(sizeof(node));
    y=root;
    x=root;
    while(x->extime<=1000)
    {
        y=x;
        if(z->extime<x->extime)
            x=x->lChild;
        else
            x=x->rChild;
    }
    z->parent=y;
    if(y->extime>1000)
        root=z;
    else if (z->extime<y->extime)
        y->lChild=z;
    else
        y->rChild=z;
    z->lChild=&nil;
    z->rChild=&nil;
    z->colour=RED;
    root=insertFix(z,root);
    return root;
}
node* treeMin(node* x)
{
    while(x->lChild->extime<=1000)
        x=x->lChild;
    return x;
}
node* treeMax(node* x)
{
    while(x->rChild->extime<=1000)
        x=x->rChild;
    return x;
}
node* treeSuccessor(node* x)
{
    node* y;
    if(x->rChild->extime<=1000)
        return treeMin(x->rChild);
    y=x->parent;
    while(y->extime<=1000 && x==y->rChild)
    {
        x=y;
        y=x->parent;
    }
    return y;
}

node* deleteFix(node *x, node *root)
{
    node *w;
    while((x->extime<=1000)&&(x->colour==BLACK))
    {
        if(x==x->parent->lChild)
        {
            w=x->parent->rChild;
            if(w->colour==RED)
            {
                w->colour=BLACK;
                x->parent->colour=RED;
                root=leftRotate(x->parent,root);
                w=x->parent->rChild;
            }
            if( w->lChild->colour==BLACK&&w->rChild->colour==BLACK)
            {
                w->colour=RED;
                x=x->parent;
            }
            else
            {
                if(w->rChild->colour==BLACK)
                {
                    w->lChild->colour=BLACK;
                    w->colour=RED;
                    root=rightRotate(w,root);
                    w=x->parent->rChild;
                }
                w->colour=x->parent->colour;
                x->parent->colour=BLACK;
                w->rChild->colour=BLACK;
                root=leftRotate(x->parent,root);
                return x;
            }
        }
        else
        {
            w=x->parent->lChild;
            if(w->colour==RED)
            {
                w->colour=BLACK;
                x->parent->colour=RED;
                root=rightRotate(x->parent,root);
                w=x->parent->lChild;
            }
            if( w->rChild->colour==BLACK&&w->lChild->colour==BLACK)
            {
                w->colour=RED;
                x=x->parent;
            }
            else
            {
                if(w->lChild->colour==BLACK)
                {
                    w->rChild->colour=BLACK;
                    w->colour=RED;
                    root=leftRotate(w,root);
                    w=x->parent->lChild;
                }
                w->colour=x->parent->colour;
                x->parent->colour=BLACK;
                w->lChild->colour=BLACK;
                root=rightRotate(x->parent,root);
                return x;
            }
        }
    }
    return root;
}
node* delete(node* z, node* root)
{
    node *x, *y;
    if(z->lChild->extime>1000||z->rChild->extime>1000)
        y=z;
    else
        y=treeSuccessor(z);
    if(y->lChild->extime<=1000)
        x=y->lChild;
    else
        x=y->rChild;
    x->parent=y->parent;
    if(y->parent->extime>1000)
        root=x;
    else if(y==y->parent->lChild)
        y->parent->lChild=x;
    else
        y->parent->rChild=x;
    if(y!=z)
    {
        z->extime=y->extime;
        z->id=y->id;
        z->priority=y->priority;
        z->colour=y->colour;
    }
    if(y->colour==BLACK)
        deleteFix(x,root);
    return y;
}
node* processCreate(int liveproc, node* root)
{
    node *new = (node*)malloc(sizeof(node));
    new->id=liveproc;
    new->extime=rand()%1000+1;
    new->priority=rand()%4+1;
    new->colour=RED;
    new->lChild=&nil;
    new->rChild=&nil;
    new->parent=&nil;
    root=insert(new,root);
    return root;
}
int processSchedule(node *root)
{
    node *x;
    x=treeMin(root);
    delete(x,root);
    if(x->extime>50*x->priority)
    {
        x->extime=x->extime-(50*x->priority);
        insert(x,root);
        return 0;
    }
    return 1;
}
void print_level(node *root, int level)
{
    if(root->extime==nil.extime)
        return;
    if(level==1)
    {
        printf(" %d %d (%d )",root->extime,root->colour,root->parent->extime);
    }
    else if (level>1)
    {
        print_level(root->lChild,level-1);
        print_level(root->rChild,level-1);
    }
}
void print_tree(node *root, int n)
{
    int d=1;
    for (d=1;d<n;d++)
    {
        print_level(root,d);
        printf("\n");
    }
}
void printInsert(node *root, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        root=processCreate(i+1,root);
    }
    print_tree(root,n);
}
int main()
{
    srand(time(NULL));
    node *root = (node*)malloc(sizeof(node));
    root=&nil;
    int N=10,M=5,i,procdone=0,liveproc=0;
    printf("Enter N : ");
    scanf("%d",&N);
    printf("Enter M : ");
    scanf("%d",&M);
    while(procdone<M)
    {
        if(liveproc<N)
        {
            liveproc++;
            root=processCreate(liveproc,root);
        }
        procdone=procdone+processSchedule(root);
    }
}