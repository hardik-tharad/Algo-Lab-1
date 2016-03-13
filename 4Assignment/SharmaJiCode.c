#include <stdio.h>

void elimination(int start, int n, int k)
{
    int key,i;
if(n==1)
{
    return;
}


if(n%2==0)
{
    key=start+k/2;
    i=1;
    while(i<=n/2)
        {

            printf("  %d", key);
            key=key+k;
            i++;
        }

    k=k*2;
    n=n/2;
    elimination(start,n,k);

}

else
{
    key=start+k/2;
    i=1;
    while(i<=n/2)
        {

            printf("  %d",  key);
            key=key+k;
            i++;
        }
        printf("  %d",  start);

    start+=k;
    k=k*2;
    n=n/2;
    elimination(start,n,k);
}

}

void print(int n)
{
    int m=1;
  while(n>=m)
{
  m=m*2 ;
}
m=m/2;
printf("\nfinal survivor=%d",2*(n-m)+1);
}


int main()
{
int n;
printf("enter the value of n\n");
scanf("%d",&n);
elimination(1,n,2);
print(n);

}
