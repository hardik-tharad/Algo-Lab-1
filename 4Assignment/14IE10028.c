/* Last Man Standing
Name: Shashwat Gupta
Roll: 14IE10028 */
#include <stdio.h>
#include <stdlib.h>
void elimin_solve(int start, int n, int step)
{
    int printer,i;
    if(n==1)
    {
        printf("\nThe survivor is : %d",start);
        return;
    }
    printer=start+step/2;
    for(i=1;i<=n/2;i++,printer+=step)
        printf("%d\t",printer);
    if(n%2==0)
        elimin_solve(start,n/2,step*2);
    else
    {
        printf("%d\t",start);
        elimin_solve(start+step,n/2,step*2);
    }
}
int func_solve(int n)
{
    int i;
    if(n==1)
        return 1;
    else if(n%2==0)
        return 2*func_solve(n/2)-1;
    else
        return 2*func_solve(n/2)+1;
}
int check_print(int n)
{
    int m=1;
    while(n>=m)
        m=m*2;
    m/=2;
    return(2*(n-m)+1);
}
int main()
{
    int n;
    printf("Enter the number of people (n) : ");
    scanf("%d",&n);
    if(n<=0)
    {
        printf("Incorrect inputs, program terminated\n");
        exit(0);
    }
    elimin_solve(1,n,2);
    printf("\nFinal Survivor from recursive function: %d\n",func_solve(n));
    printf("Final Survivor using \"V(2m+l)=2l+1\" : %d\n",check_print(n));
}