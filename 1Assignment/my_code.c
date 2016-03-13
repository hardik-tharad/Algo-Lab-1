#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max 5000

typedef struct my_complex {
	double r;
	double im;
} my_complex;

my_complex add_complex(my_complex a, my_complex b)
{
	my_complex x;
	x.r = a.r + b.r;
	x.im = a.im + b.im;
	return x;
}

my_complex sub_complex(my_complex a, my_complex b)
{
	my_complex x;
	x.r = a.r - b.r;
	x.im = a.im - b.im;
	return x;
}

my_complex mul_complex(my_complex a, my_complex b)
{
	my_complex x;
	x.r = a.r*b.r - a.im*b.im;
	x.im = a.im*b.r + a.r*b.im;
	return x;
}

my_complex div_complex(my_complex a, double n)
{
	my_complex x;
	x.r = a.r/n;
	x.im = a.im/n;
	return x;
}

my_complex* create(my_complex *a, int n, int size)
{
	int i;
	a = (my_complex*)malloc((size+2)*sizeof(my_complex));
	for (i=0; i<n; i++)
	{
		a[i].im=0;
		a[i].r=rand()%10;
	}
	a[0].r = 1+rand() % 8;
	return a;
}

void fft(int n, my_complex *a, my_complex *f)
{
	int k;
	my_complex omegak;
	if (n == 1)
	{
		f[0]=a[0];
		return;
	}
	for (k=0; k<n; k++)
	{
		f[k].r = 0;
		f[k].im = 0;
	}
	my_complex *e = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	my_complex *o = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	my_complex *ef = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	my_complex *of = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	for (k=0; k<n; k+=2)
	{
		e[k/2] = a[k];
		o[k/2] = a[k+1];
	}
	fft(n/2, e, ef);
	fft(n/2, o, of);
	for (k=0; k<n/2; k++)
	{
		omegak.r = cos(2.0*M_PI*k/n);
		omegak.im = sin(2.0*M_PI*k/n);
		f[k] = add_complex(ef[k], mul_complex(omegak, of[k]));
		f[k+n/2] = sub_complex(ef[k], mul_complex(omegak, of[k]));
	}
	free(e);
	free(o);
	free(ef);
	free(of);
}

void ifft(int n, my_complex *a, my_complex *f)
{
	int k;
	my_complex omegak;
	if (n == 1)
	{
		f[0]=a[0];
		return;
	}
	for (k=0; k<n; k++)
	{
		f[k].r = 0;
		f[k].im = 0;
	}
	my_complex *e = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	my_complex *o = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	my_complex *ef = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	my_complex *of = (my_complex*)malloc((n/2 + 2)*sizeof(my_complex));
	for (k=0; k<n; k+=2)
	{
		e[k/2] = a[k];
		o[k/2] = a[k+1];
	}
	ifft(n/2, e, ef);
	ifft(n/2, o, of);
	for (k=0; k<n/2; k++)
	{
		omegak.r = cos(2.0*M_PI*k/n);
		omegak.im = -1*sin(2.0*M_PI*k/n);
		f[k] = add_complex(ef[k], mul_complex(omegak, of[k]));
		f[k+n/2] = sub_complex(ef[k], mul_complex(omegak, of[k]));
	}
	free(e);
	free(o);
	free(ef);
	free(of);
}

void print_complex(my_complex *a, int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%d", (int)a[i].r);
	printf("\n");
}

int main()
{
	int i,j=1,k=0;
	srand(time(0));
	my_complex *a = NULL, *b = NULL;
	printf("Enter size of nums:\n");
	scanf("%d", &i);
	int size_a = i, size_b = i;
	int size_c = 0;
	while(j<=2*i)
		j*=2;
	size_c=j;
	a = create(a, size_a, size_c);
	b = create(b, size_b, size_c);
	printf("First Number = \n");
	print_complex(a, size_a);
	printf("Second Number = \n");
	print_complex(b, size_b);
	my_complex r1[max], r2[max], r3[max], r4[max];
	fft(size_c, a, r1);
	fft(size_c, b, r2);

	for(i=0; i<size_c; ++i)
		r3[i] = mul_complex(r1[i], r2[i]);

	ifft(size_c, r3, r4);
	
	for(i=0; i<size_c; ++i)
	{
		r4[i].r = r4[i].r/size_c;
		r4[i].im = r4[i].im/size_c;
	}
	printf("Product = \n");

	i=0;k=max-2;
	int tmp1[max] = { 0 };
	int tmp2[max] = { 0 };
	for(i=0; i<2*size_a-1; ++i)
		tmp1[i] = (int)(r4[i].r + 0.000001);
	for(i=2*size_a-2; i>-1; --i)
	{
		tmp2[k] += tmp1[i] % 10;
		tmp2[k - 1] = tmp1[i] / 10;
		--k;
	}
	k=max-2;
	for (i=2*size_a-2; i>-1; --i)
	{
		tmp2[k - 1] += tmp2[k] / 10;
		tmp2[k] = tmp2[k] % 10;
		--k;
	}
	while (1)
	{
		if (tmp2[k] == 0)
			break;
		tmp2[k - 1] += tmp2[k] / 10;
		tmp2[k] = tmp2[k] % 10;
		--k;
	}
	for (i = k + 1; i <= max - 2; ++i)
		printf("%d", tmp2[i]);
	printf("\n");
	return 0;
}

