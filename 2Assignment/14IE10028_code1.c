#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define m 150
int arr[m][m];
int printer=1;
typedef struct _point
{
	int x;
	int y;
}point;
int check_defect_zone(point centre, point defect)
{
	if(defect.x>centre.x)
	{
		if(defect.y>centre.y)
			return 3;
		else
			return 2;
	}
	else
	{
		if(defect.y>centre.y)
			return 4;
		else
			return 1;
	}
}
void fill_4_operation(point a, int z)
{
	if(z==1)
	{
		arr[a.x+1][a.y+1]=printer;
		arr[a.x][a.y+1]=printer;
		arr[a.x+1][a.y]=printer;
	}
	else if(z==2)
	{
		arr[a.x][a.y]=printer;
		arr[a.x][a.y+1]=printer;
		arr[a.x+1][a.y+1]=printer;
	}
	else if(z==3)
	{
		arr[a.x][a.y]=printer;
		arr[a.x+1][a.y]=printer;
		arr[a.x][a.y+1]=printer;
	}
	else
	{
		arr[a.x][a.y]=printer;
		arr[a.x+1][a.y]=printer;
		arr[a.x+1][a.y+1]=printer;
	}
	printer++;
}
void rec_fill(point start, int size, point defect)
{
	point centre,start_copy,defect_copy;
	centre.x=start.x+size/2-1;
	centre.y=start.y+size/2-1;
	int z=check_defect_zone(centre,defect);
	fill_4_operation(centre,z);
	if(size==2)
		return;
	if(z==1)
	{
		start_copy.x=start.x;
		start_copy.y=start.y;
		defect_copy.x=defect.x;
		defect_copy.y=defect.y;
		rec_fill(start_copy,size/2,defect_copy); //1st subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y;
		defect_copy.x=start.x+size/2;
		defect_copy.y=start.y+size/2-1;
		rec_fill(start_copy,size/2,defect_copy); //2nd subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y+size/2;
		defect_copy.x=start.x+size/2;
		defect_copy.y=start.y+size/2;
		rec_fill(start_copy,size/2,defect_copy); //3rd subblock
		start_copy.x=start.x;
		start_copy.y=start.y+size/2;
		defect_copy.x=start.x+size/2-1;
		defect_copy.y=start.y+size/2;
		rec_fill(start_copy,size/2,defect_copy); //4th subblock
	}
	else if(z==2)
	{
		start_copy.x=start.x;
		start_copy.y=start.y;
		defect_copy.x=start.x+size/2-1;
		defect_copy.y=start.y+size/2-1;
		rec_fill(start_copy,size/2,defect_copy); //1st subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y;
		defect_copy.x=defect.x;
		defect_copy.y=defect.y;
		rec_fill(start_copy,size/2,defect_copy); //2nd subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y+size/2;
		defect_copy.x=start.x+size/2;
		defect_copy.y=start.y+size/2;
		rec_fill(start_copy,size/2,defect_copy); //3rd subblock
		start_copy.x=start.x;
		start_copy.y=start.y+size/2;
		defect_copy.x=start.x+size/2-1;
		defect_copy.y=start.y+size/2;
		rec_fill(start_copy,size/2,defect_copy); //4th subblock
	}
	else if(z==3)
	{
		start_copy.x=start.x;
		start_copy.y=start.y;
		defect_copy.x=start.x+size/2-1;
		defect_copy.y=start.y+size/2-1;
		rec_fill(start_copy,size/2,defect_copy); //1st subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y;
		defect_copy.x=start.x+size/2;
		defect_copy.y=start.y+size/2-1;
		rec_fill(start_copy,size/2,defect_copy); //2nd subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y+size/2;
		defect_copy.x=defect.x;
		defect_copy.y=defect.y;
		rec_fill(start_copy,size/2,defect_copy); //3rd subblock
		start_copy.x=start.x;
		start_copy.y=start.y+size/2;
		defect_copy.x=start.x+size/2-1;
		defect_copy.y=start.y+size/2;
		rec_fill(start_copy,size/2,defect_copy); //4th subblock
	}
	else
	{
		start_copy.x=start.x;
		start_copy.y=start.y;
		defect_copy.x=start.x+size/2-1;
		defect_copy.y=start.y+size/2-1;
		rec_fill(start_copy,size/2,defect_copy); //1st subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y;
		defect_copy.x=start.x+size/2;
		defect_copy.y=start.y+size/2-1;
		rec_fill(start_copy,size/2,defect_copy); //2nd subblock
		start_copy.x=start.x+size/2;
		start_copy.y=start.y+size/2;
		defect_copy.x=start.x+size/2;
		defect_copy.y=start.y+size/2;
		rec_fill(start_copy,size/2,defect_copy); //3rd subblock
		start_copy.x=start.x;
		start_copy.y=start.y+size/2;
		defect_copy.x=defect.x;
		defect_copy.y=defect.y;
		rec_fill(start_copy,size/2,defect_copy); //4th subblock
	}
}

void print_array(int size)
{
	printf("printing board: \n");
	int i,j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		printf("%d\t",arr[i][j]);
		printf("\n");
	}
}

int main()
{
	int i,n=0,z=0;
	printf("Enter n : ");
	scanf("%d",&n);
	int size=1;
	for (i = 1; i <= n; ++i)
		size*=2;
	printf("board generated of %dx%d dimension\n",size,size);
	print_array(size);
	printf("Enter the coordinates of the defective point (The smallest coordinate is (1,1))\n");
	point defect,start;
	start.x=0;	start.y=0;
	printf("x coordinate : ");
	scanf("%d",&defect.x);
	printf("y coordinate : ");
	scanf("%d",&defect.y);
	defect.x--;	defect.y--;
	if(defect.x>=size||defect.y>=size)
	{
		printf("Invalid coordinates entered. Code terminated\n");
		exit(0);
	}
	arr[defect.x][defect.y]=-1;
	rec_fill(start, size, defect);
	print_array(size);
}

/*
zones:
1 	4
2 	3
*/