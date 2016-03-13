/*Interval Trees
Shashwat Gupta
14IE10028
I am taking left side closed and right side closed []*/
#include <stdio.h>
#include <stdlib.h>
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
typedef struct _list
{
    int data;
    struct _list *next;
}list;
typedef struct node
{
    int lower,upper;
    list *listptr;
    struct node *lChild, *rChild;
}node;
int interval;
node* CREATE_INTERVAL_TREE(int l, int u, int n) //working correctly
{
    if(n==0)
        return NULL;
    if(n==1)
    {
        node *temp = (node*)malloc(sizeof(node));
        temp->lower=l;
        temp->upper=u;
        list *templist = (list*)malloc(sizeof(list));
        templist->next=NULL;
        templist->data=0;
        temp->listptr=templist;
        temp->lChild=NULL;
        temp->rChild=NULL;
        return temp;
    }
    int nn=n/2+1; //median interval number
    int rem=(u-l+1)%n;
    node *temp = (node*)malloc(sizeof(node));
    temp->lower=(nn-1)*interval+l+rem/2;
    temp->upper=nn*interval+l-1+rem-rem/2;
    list *templist = (list*)malloc(sizeof(list));
    templist->next=NULL;
    templist->data=0;
    temp->listptr=templist;
    temp->lChild=CREATE_INTERVAL_TREE(l,temp->lower-1,nn-1);
    temp->rChild=CREATE_INTERVAL_TREE(temp->upper+1,u,n-nn);
    return temp;
}
void INSERT(node *root, int i)//working correctly
{
    if(root==NULL)
        return;
    if(i<root->lower)
        INSERT(root->lChild,i);
    else if(i>root->upper)
        INSERT(root->rChild,i);
    else
    {
        list *templist = (list*)malloc(sizeof(list));
        templist=root->listptr;
        while(templist->next!=NULL&&templist->data<=i)
            templist=templist->next;
        if(templist->next!=NULL)//sorting needed
        {
            int j,k,shifts=1;
            list *tempsort = (list*)malloc(sizeof(list));
            tempsort=templist->next;
            while(tempsort->next!=NULL)//count shifts
            {
                tempsort=tempsort->next;
                shifts++;
            }
            for (j=shifts;j>0;j--)
            {
                tempsort=templist;
                for (k=1;k<j;++k)
                    tempsort=tempsort->next;
                tempsort->next->data=tempsort->data;
            }
        }
        templist->data=i;
        list *newnode = (list*)malloc(sizeof(list));
        newnode->next=NULL;
        while(templist->next!=NULL)
            templist=templist->next;
        templist->next=newnode;
    }
}
void eat(node* T, node* N, int check, int flag)
{
    if (T==NULL)
        return;
    if(T->lower>=N->lower&&T->upper<=N->upper)
    {
        list *listdata = (list*)malloc(sizeof(list));
        listdata=T->listptr;
        while(listdata->next!=NULL&&listdata->data!=0)
        {
            INSERT(N,listdata->data);
            listdata=listdata->next;
        }
        eat(T->lChild,N,0,0);
        eat(T->rChild,N,1,0);
        return;
    }
    else if(check==0&&N->lower>T->upper)
    {
        eat(T->rChild,N,1,1);
        if(T->rChild!=NULL&&T->rChild->lower>=N->lower&&T->rChild->upper<=N->upper)
            T->rChild=NULL;
        if(flag==0)
            N->lChild=T;
    }
    else if(check==1&&T->lower>N->upper)
    {
        eat(T->lChild,N,0,1);
        if(T->lChild!=NULL&&T->lChild->lower>=N->lower&&T->lChild->upper<=N->upper)
            T->lChild=NULL;
        if(flag==0)
            N->rChild=T;
    }
    else if(check==0&&flag==0)
        N->lChild=T;
    else if(check==1&&flag==0)
        N->rChild=T;
}
node* MERGE(node *T,int l,int u)
{
    if(T==NULL)
        return NULL;
    if(T->lower>u)
    {
        T->lChild=MERGE(T->lChild,l,u);
        return T;
    }
    if(T->upper<l)
    {
        T->rChild=MERGE(T->rChild,l,u);
        return T;
    }
    node *N = (node*)malloc(sizeof(node));
    N->lower=l;
    N->upper=u;
    list *templist = (list*)malloc(sizeof(list));
    templist->next=NULL;
    templist->data=0;
    N->listptr=templist;
    N->lChild=NULL;
    N->rChild=NULL;
    eat(T,N,2,0);
    return N;
}
void PRETTY_PRINT(node *root, int k) //working correctly
{
    int i;
    if(root==NULL)
        return;
    PRETTY_PRINT(root->lChild,k-1);
    for(i=1;i<=k;i++)
        printf("\t");
    printf("[%d, %d]",root->lower,root->upper);
    list *templist = (list*)malloc(sizeof(list));
    templist=root->listptr;
    while(templist!=NULL&&templist->data!=0)
    {
        printf(" %d",templist->data);
        templist=templist->next;
    }
    printf("\n");
    PRETTY_PRINT(root->rChild,k-1);
}
int maxDepth(node* root) 
{
    if (root==NULL) 
       return -1;
    else
    {
        int lDepth = maxDepth(root->lChild);
        int rDepth = maxDepth(root->rChild);
        if (lDepth > rDepth)
            return(lDepth+1);
        else
            return(rDepth+1);
    }
}
int main()
{
    srand(time(NULL));
    int l,u,n,i,loop;
    l=1;u=100;n=15;i=30;
    /*
    printf("Enter l : ");
    scanf("%d",&l);
    printf("Enter u : ");
    scanf("%d",&u);
    printf("Enter n : ");
    scanf("%d",&n);
    printf("Enter i : ");
    scanf("%d",&i);
    */
    interval=(u-l+1)/n;
    node *root = (node*)malloc(sizeof(node));
    root = CREATE_INTERVAL_TREE(l, u, n);
    for(loop=1;loop<=i;loop++)
    {
        int k=l+rand()%(u-l+1);
        INSERT(root,k);
    }
    PRETTY_PRINT(root, maxDepth(root));
    printf("\n");
    MERGE(root,2,10);
    PRETTY_PRINT(root, maxDepth(root));
    printf("\n");
}
