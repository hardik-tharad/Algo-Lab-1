// Returns solution to the knapsack problem with item repetition
#include <stdlib.h>
#include <stdio.h>
#define N 50
int main()
{
    int i,j,capacity,n;
    printf("Enter capacity of knapsack : ");
    scanf("%d",&capacity);
    printf("Enter number of items : ");
    scanf("%d",&n);
    int val[N];
    int size[N];
    for (i = 0; i < n; ++i)
    {
        printf("Value for item %d = ",i+1);
        scanf("%d",&val[i]);
        printf("Weight for item %d = ",i+1);
        scanf("%d",&size[i]);
    }
    int K[capacity+1];
    K[0] = 0;
    for (i = 1; i <= capacity; ++i)
    {
        K[i]=K[i-1];
        for (j = 0; j < n; ++j)
        {
            if((i-size[j])>=0 && K[i]<(K[i-size[j]]+val[j]))
                K[i]=K[i-size[j]]+val[j];
        }
    }
    printf("Maximum Value = %d\n", K[capacity]);
    return 0;
}