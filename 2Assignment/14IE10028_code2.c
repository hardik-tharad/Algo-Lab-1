#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define m 150
typedef struct _point
{
    int x;
    int y;
}point;
point a[m];
int n;
void fill_coordinates()
{
    srand(time(NULL));
    int i;
    printf("Enter number of points : ");
    scanf("%d",&n);
    for (i = 0; i < n; ++i)
    {
        a[i].x=rand()%100;
        a[i].y=rand()%100;
    }
}
void print_array()
{
    int i;
    for (i = 0; i < n; ++i)
        printf("(%d,%d) ",a[i].x,a[i].y);
    printf("\n");
}
float give_distance(point a, point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
float brute_force()
{
    int i,j;
    float min=give_distance(a[0],a[1]);
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(give_distance(a[i],a[j])<min)
                min=give_distance(a[i],a[j]);
        }
    }
    return min;
}
int main()
{
    fill_coordinates();
    print_array();
    printf("The smallest distance is : %f\n",brute_force()); 
}