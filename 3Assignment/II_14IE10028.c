/* Each building is rectangular in shape and has a flat roof.
A building B is represented by a triple (l,r,h)
l and r represent the leftmost and rightmost x-coordinates, h represents the height.
The input is a list of triples - one per building.
The output is a list of x-coordinate and height arranged in ascending order of x representing the skyline.

Name: Shashwat Gupta
Roll: 14IE10028 */
#include <stdio.h>
#include <stdlib.h>
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
typedef struct quad{
    int l,lh,r,rh;
}quad;
typedef struct _point{
    int l,h;
}point;
void prin_buildings(quad *building, int size)
{
    printf("printing building quadruples: \n");
    int i;
    printf("left\th-l\tright\th-r\n");
    for (i = 0; i < size; ++i)
        printf("%d\t%d\t%d\t%d\n",building[i].l,building[i].lh,building[i].r,building[i].rh);
}
void prin_points(point *skyline, int n)
{
    printf("printing critical point(s): \n");
    int i;
    for (i = 0; i < n; i++)
    {
        if(i!=0&&skyline[i].l==0&&skyline[i-1].l>0)
          break;
        printf("(%d, %d)\n",skyline[i].l,skyline[i].h);
    }
}
float slope(int x1,int x2,int y1,int y2)
{
    return((y2-y1)/(x2-x1));
}
point* merge(point *L, int n1, point *R, int n2)
{
    int i, j, k, h1=0, h2=0;;
    point *final = (point *)malloc(sizeof(point)*(n1+n2+2));
    i = 0;
    j = 0;
    k = 0;
    while (i < n1 && j < n2)
    {
        if (L[i].l < R[j].l)
        {
            if(k!=0&&MAX(L[i].h,h2)==final[k-1].h)
            {
                h1=L[i].h;
                i++;
                continue;         
            }
            final[k].h = MAX(L[i].h,h2);
            final[k].l = L[i].l;
            h1=L[i].h;
            i++;
        }
        else if (L[i].l > R[j].l)
        {
            if(k!=0&&MAX(R[j].h,h1)==final[k-1].h)
            {
                h2=R[j].h;
                j++;
                continue;
            }
            final[k].h = MAX(R[j].h,h1);
            final[k].l = R[j].l;
            h2=R[j].h;
            j++;
        }
        else
        {
            if(k!=0&&MAX(R[j].h,L[i].h)==final[k-1].h)
            {
                h1=L[i].h;
                h2=R[j].h;
                i++;
                j++;
                continue;
            }
            final[k].l=L[i].l;
            final[k].h=MAX(L[i].h,R[j].h);
            h1=L[i].h;
            h2=R[j].h;
            i++;
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        final[k].h = MAX(L[i].h,h2);
        final[k].l = L[i].l;
        i++;
        k++;
    }
    while (j < n2)
    {
        final[k].h = MAX(R[j].h,h1);
        final[k].l = R[j].l;
        j++;
        k++;
    }
    return final;
}
point* mergeSort_skyline(quad *building, int l, int r)
{
    int m;
    if (l == r)
    {
        point *sky = (point *)malloc(sizeof(point)*3);
        point p1;
        p1.l = building[l].l; p1.h = building[l].lh;
        point p2;
        p2.l = building[l].r; p2.h = building[l].rh;
        point p3;
        p3.l = building[l].r; p3.h = 0;
        sky[0] = p1;
        sky[1] = p2;
        sky[2] = p3;
        return sky;
    }
    m = (l + r)/2;
    point* leftsky = mergeSort_skyline(building, l, m);
    point* rightsky = mergeSort_skyline(building, m+1, r);
    return merge(leftsky, (m-l+1)*3, rightsky, (r-m)*3);
}
int main()
{
    srand(time(NULL));
    int size,i,x1,x2,hh;
    printf("Enter number of buildings : ");
    scanf("%d",&size);
    printf("Enter left limit : ");
    scanf("%d",&x1);
    printf("Enter right limit : ");
    scanf("%d",&x2);
    printf("Enter height limit : ");
    scanf("%d",&hh);
    if(x2<x1||size<=0||hh<=0)
    {
        printf("Incorrect inputs, program terminated\n");
        exit(0);
    }
    quad *building = (quad *)malloc(sizeof(quad)*size);
    for(i=0;i<size;i++)
    {
        building[i].l=(rand()%(x2-x1))+x1;
        building[i].r=(rand()%(x2-building[i].l))+building[i].l+1;
        building[i].lh=(rand()%hh)+1;
        building[i].rh=(rand()%hh)+1;
    }
    prin_buildings(building,size);
    point* a=mergeSort_skyline(building,0,size-1);
    prin_points(a,size*2);
}