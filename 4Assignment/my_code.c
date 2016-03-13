/* Last Man Standing
Name: Shashwat Gupta
Roll: 14IE10028 */
#include <stdio.h>
#include <stdlib.h>
int elimination(int n)
{
    int i;
    if(n==1)
        return 1;
    else if(n%2==0)
    {
        for (i = 2; i <= n; i+=2)
            printf("%d ",i);
        return 2*elimination(n/2)-1;
    }
    else
    {
        return 2*elimination(n/2)+1;
    }
}
int main()
{
    int n;
    printf("Enter number of people(n) : ");
    scanf("%d",&n);
    if(n<=0)
    {
        printf("Incorrect inputs, program terminated\n");
        exit(0);
    }
    printf("\nThe person at position %d survives.\n",elimination(n));
}