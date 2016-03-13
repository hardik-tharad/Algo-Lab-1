/* Each building is rectangular in shape and has a flat roof.
A building B is represented by a triple (l,r,h)
l and r represent the leftmost and rightmost x-coordinates, h represents the height.
The input is a list of triples - one per building.
The output is a list of x-coordinate and height arranged in ascending order of x representing the skyline. */
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int size=0;
typedef struct _triple{
    int l,r,h;
}triple;
typedef struct _point{
    int l,h;
}point;
triple building[MAX];
point skyline[MAX*2];

int max(int a, int b) {return (a > b) ? a : b; } 

void make_points()
{
    int i;
    for (i = 0; i < size; i++)
    {
        skyline[2*i].l=building[i].l;
        skyline[2*i].h=building[i].h;
        skyline[2*i+1].l=building[i].r;
        skyline[2*i+1].h=0;
    }
}
void prin_buildings()
{
    printf("printing building triplets: \n");
    int i;
    printf("left\tright\theight\n");
    for (i = 0; i < size; ++i)
        printf("%d\t%d\t%d\n",building[i].l,building[i].r,building[i].h);
}
void prin_points()
{
    printf("printing points: \n");
    int i;
    for (i = 0; i < size*2; i+=2)
        printf("(%d, %d)\t(%d, %d)\n",skyline[i].l,skyline[i].h,skyline[i+1].l,skyline[i+1].h);
}
point* merge(point* left, point* right)
{
    int n1 = sizeof(left)/sizeof(left[0]);
    int n2 = sizeof(right)/sizeof(right[0]);
    point *res = (point *)malloc(sizeof(point) * (n1 + n2));
 
    // To store current heights of two skylines
    int h1 = 0, h2 = 0;
 
    // Indexes of strips in two skylines
    int i = 0, j = 0;
    int c = 0;
    while (i < n1 && j < n2)
    {
        // Compare x coordinates of left sides of two
        // skylines and put the smaller one in result
        if (left[i].l < right[j].l)
        {
            int x1 = left[i].l;
            h1 = left[i].h;
 
            // Choose height as max of two heights
            int maxh = max(h1, h2);
            point p; p.l = x1; p.h = maxh;
            res[c] = p;
            c++;
            i++;
        }
        else
        {
            int x2 = right[j].l;
            h2 = right[j].h;
            int maxh = max(h1, h2);
            point p; p.l = x2; p.h = maxh;
            res[c] = p;
            c++;
            j++;
        }
    }
 
    // If there are strips left in this skyline or other
    // skyline
    while (i < n1)
    {
        res[c] = left[i];
        c++;
        i++;
    }
    while (j < n2)
    {
        res[c] = right[j];
        c++;
        j++;
    }
    return res;
}
point* mergeSort_skyline(triple arr[], int lo, int hi)
{
    int m=0;
    if (lo == hi) {
        point *sky = (point *)malloc(sizeof(point) * 2);
        point p1;
        p1.l = arr[lo].l; p1.h = arr[lo].h;
        point p2;
        p2.l = arr[lo].r; p2.h = 0;
        sky[0] = p1;
        sky[1] = p2;
        return sky;
    }
    m = (lo + hi)/2;
    point* leftsky = mergeSort_skyline(arr, lo, m);
    point* rightsky = mergeSort_skyline(arr, m+1, hi);
    point *sky = merge(leftsky, rightsky);
    return sky;
}

int main()
{
    size=5;
    building[0].h=4;
    building[0].l=0;
    building[0].r=3;
    building[1].h=6;
    building[1].l=11;
    building[1].r=13;
    building[2].h=5;
    building[2].l=4;
    building[2].r=8;
    building[3].h=3;
    building[3].l=7;
    building[3].r=10;
    building[4].h=7;
    building[4].l=2;
    building[4].r=5;    
    prin_buildings();
    make_points();
    prin_points();
    point *sky = mergeSort_skyline(building,0,9);
    int i;
    for (i = 0 ; i < (int)(sizeof(sky)/sizeof(sky[0])); i++) {
        printf("%d, %d\n", sky[i].l, sky[i].h);
    }
    //prin_buildings();
    //prin_skyline();
}

/*int main()
{
    srand(time(NULL));
    int i,x1,x2;
    if(x2<x1)
    {
        printf("Incorrect inputs, program terminate\n");
        exit(0);
    }
    printf("Enter nubmer of buildings : (maximum 100)\n");
    printf("Enter left limit : ");
    scanf("%d",&x1);
    printf("Enter right limit : ");
    scanf("%d",&x2);
    printf("Enter number of buildings : ");
    scanf("%d",&size);
    for(i=0;i<size;i++)
    {
        building[i].l=(rand()%(x2-x1))+x1;
        building[i].r=(rand()%(x2-building[i].l))+building[i].l+1;
        building[i].h=(rand()%10)+1;
    }
    prin_buildings();
    //rec_fill();
    //prin_skyline();
}*/