#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define FOR(i,a,b) for(i=a; i<b; ++i)
#include<string.h>
#include<stdlib.h>
#define REP(i,n) for(i=0; i<n; ++i)
#ifndef M_PI
#define M_PI 3.14159265359
#endif
#define MAX 10099
const long double delta = 1e-8;

#define real long double
#define ll long long
struct complx {
	long double r;
	long double im;
};
void prin(struct complx a)
{
	printf("%f + I%f\n", (float)a.r, (float)a.im);
}

struct complx add(struct complx a, struct complx b)
{
	struct complx t;
	t.r = a.r + b.r;
	t.im = a.im + b.im;
	return t;
}
struct complx div_num(struct complx a, real n)
{
	struct complx t = a;
	t.r /= n;
	t.im /= n;
	return t;
}
struct complx sub(struct complx a, struct complx b)
{
	struct complx t;
	t.r = a.r - b.r;
	t.im = a.im - b.im;
	return t;
}
struct complx mul(struct complx a, struct complx b)
{
	struct complx t;
	t.r = a.r*b.r - a.im*b.im;
	t.im = a.im*b.r + a.r*b.im;
	return t;
}
struct complx a_conj(struct complx a)
{
	struct complx t = a;
	t.im = -t.im;
	return t;
}
void fft(const int n, struct complx *A, struct complx *F, int is_fft)
{
	if (n == 1) {
		F[0] = A[0];
		return;
	}
	struct complx *e = (struct complx*)malloc((n / 2 + 1)*sizeof(struct complx));
	struct complx *o = (struct complx*)malloc((n / 2 + 1)*sizeof(struct complx));
	struct complx *ef = (struct complx*)malloc((n / 2 + 1)*sizeof(struct complx));
	struct complx *of = (struct complx*)malloc((n / 2 + 1)*sizeof(struct complx));
	int i, k;
	for (k = 0; k<n; k += 2) {
		e[k / 2] = A[k];
		o[k / 2] = A[k + 1];
	}
	fft(n / 2, e, ef, is_fft);
	fft(n / 2, o, of, is_fft);
	for (i = 0; i<n; ++i) {
		F[i].r = 0; F[i].im = 0;
	}
	for (k = 0; k < n / 2; ++k) {
		struct complx omegak, tmp;
		omegak.r = cos(2.0*M_PI*k / (n));	//using euler's method 
		omegak.im = is_fft*sin(2.0*M_PI*k / (n));
		tmp = mul(omegak, of[k]);
		F[k] = add(ef[k], tmp);
		F[k + n / 2] = sub(ef[k], tmp);
	}

	free(e); free(ef); free(o); free(of);
}

void printer(struct complx* a, int n)
{
	putchar('\n');
	int i;
	REP(i, n) {
		prin(a[i]);
	}
	putchar('\n');
}

struct complx* init(struct complx *a, int n, int sz)
{

	int i = 0;
	a = (struct complx*)malloc((sz+5)*sizeof(struct complx));
	if (a == 0)printf("NO memory\n");
	memset(a, 0, sizeof(struct complx)*(sz + 2));
	while (i<n) {
		a[i].im = 0;
		a[i++].r = rand() % 10;
	}
	a[0].r = 1+rand() % 8;
	return a;
}
void print_complx(struct complx *a, int n)
{
	int i;
	REP(i, n)
		printf("%d", (int)a[i].r); putchar('\n');
}
void dig_prin(struct complx* a, int n) //n = _N_/2
{
	int i = 0, k = 0;
	int arr[3 * MAX] = { 0 };
	REP(i, n) {
		arr[i] = (int)(a[i].r + delta);
	}
	int res[10000] = { 0 };
	k = 3 * MAX - 2;
	for (i = n - 1; i > -1; --i) {
		res[k] += arr[i] % 10;
		res[k - 1] = arr[i] / 10;
		--k;
	}
	k = 3 * MAX - 2;
	for (i = n - 1; i > -1; --i) {
		res[k - 1] += res[k] / 10;
		res[k] = res[k] % 10;
		--k;
	}
	while (1) {
		if (res[k] == 0)
			break;
		res[k - 1] += res[k] / 10;
		res[k] = res[k] % 10;
		--k;
	}
	for (i = k + 1; i <= 3 * MAX - 2; ++i)
		printf("%d", res[i]);
	putchar('\n');
}
int get_n(int sz)
{
	int x = 1;
	while (x <= sz)
		x *= 2;
	return x;
}
int main()
{
	int i; srand(time(0));
	struct complx *a = NULL, *b = NULL;
	printf("Enter size of nums:\n");
	scanf("%d", &i);
	const int siz_a = i, siz_b = i;
	int _N_ = 0;
	_N_ = get_n(2 * siz_a); // 2x (siz_a, siz_b)
	a = init(a, siz_a, _N_);
	b = init(b, siz_b, _N_);
	printf("NUM1 = \n");
	print_complx(a, siz_a);
	printf("NUM2 = \n");
	print_complx(b, siz_b);
	struct complx res1[MAX], res2[MAX], res3[MAX], res4[MAX];
	fft(_N_, a, res1, 1);
	fft(_N_, b, res2, 1);
	REP(i, _N_) {
		res3[i] = mul(res1[i], res2[i]);
	}
	fft(_N_, res3, res4, -1);
	REP(i, _N_) {
		res4[i] = div_num(res4[i], (long double)_N_);
	}
	struct complx* x = res4 + 1;
	int xx = _N_ - 1;
	while ((int)(res4[xx].r + delta) == 0)
		--xx;
	const int x_c = xx;
	printf("NUM2 x NUM1 = \n");
	//	dig_prin(res4, x_c + 1);
	dig_prin(res4, 2 * siz_a - 1);
	return 0;
}