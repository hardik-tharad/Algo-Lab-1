#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct complex {
    float r;
    float im;
}complex;

complex add(complex x,complex y);
complex sub(complex x,complex y);
complex multiply(complex x,complex y);
complex print_comp(complex x);

complex multiply(complex x,complex y)
{
    complex z;
    z.r = x.r*y.r - x.im*y.im;
    z.im = x.r*y.im + x.im*y.r;
    return z;
}

complex add(complex x,complex y)
{
    complex z;
    z.r = x.r + y.r;
    z.im = x.im + y.im;
    return z;
}

complex sub(complex x,complex y)
{
    complex z;
    z.r = x.r - y.r;
    z.im = x.im - y.im;
    return z;
}

complex print_comp(complex x)
{
    printf("%f + i %f \n",x.r,x.im);
}

void fft(int n, complex *a, complex *f)
{
    int k;
    complex omega, omegak;
    if (n==1)
    {
        f[0]=a[0];    
        return;
    }
    complex *e = (complex*)malloc((n/2+2)*sizeof(complex));
    complex *o = (complex*)malloc((n/2+2)*sizeof(complex));
    complex *ef = (complex*)malloc((n/2+2)*sizeof(complex));
    complex *of = (complex*)malloc((n/2+2)*sizeof(complex));
    for (k=0; k<n; k+=2)
    {
        e[k/2]=a[k];
        o[k/2]=a[k+1];
    }
    fft(n/2, e, ef);
    fft(n/2, o, of);

    omega.r=cos(2*M_PI/n);
    omegak.r=cos(2*M_PI/n);
    omega.im=sin(2*M_PI/n);
    omegak.im=sin(2*M_PI/n);
    
    for (k=0;k<n/2;k++,omegak=multiply(omegak,omega))
    {
        f[k]=add(ef[k],multiply(omegak,of[k]));
        f[k+n/2]=sub(ef[k],multiply(omegak,of[k]));
    }
}

int main()
{
    int i;
    complex *f = (complex*)malloc(3*sizeof(complex));
    complex a[]={{1,0},{-2,0},{1,0}};
    fft(3,a,f);
    for(i=0;i<3;i++)
    {
        print_comp(f[i]);
    }
}

