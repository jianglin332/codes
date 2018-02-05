#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
#define pi 3.141592653589793
struct cm
{
	double c, s;
	cm(double c = 0, double s = 0):c(c), s(s){}
	cm operator*(const cm &a) const
	{
		return cm(c * a.c - s * a.s, c * a.s + s * a.c);
	}
	cm operator+(const cm &a) const
	{
		return cm(c + a.c, s + a.s);
	}
};
cm w[2][262144];
cm an[262144], ns[262144], a[262144], b[262144], ta[262144], tb[262144];
int t;
void fft(cm *in, int tp)
{
	for (int i = 0, j = 0; i < t; i++)
	{
		if (i > j)
			swap(in[i], in[j]);
		for (int k = (t >> 1); (j ^= k) < k; k >>= 1);
	}
	for (int i = 2; i <= t; i <<= 1)
		for (int j = 0; j < t; j += i)
			for (int k = 0; k < i >> 1; k++)
			{
				cm tmp = w[tp][t / i * k] * in[j + k + (i >> 1)];
				in[j + k + (i >> 1)] = in[j + k] + tmp * (-1);
				in[j + k] = in[j + k] + tmp;
			}
}
void fourier(cm *x)
{
	memcpy(ta, a, sizeof(a));
	memcpy(tb, b, sizeof(b));
	fft(ta, 0), fft(tb, 0);
	for (int i = 0; i < t; i++)
		x[i] = ta[i] * tb[i] * (1. / t);
	fft(x, 1);
}
int main()
{
	freopen("force.in", "r", stdin);
	freopen("force.out", "w", stdout);
	int n;
	scanf("%d", &n);
	t = 1;
	while (t < n)
		t <<= 1;
	t <<= 1;
	for (int i = 0; i < n; i++)
		scanf("%lf", &a[i].c);
	for (int i = 1; i < n; i++)
		b[i].c = 1. / i / i;
	cm g(cos(2 * pi / t), sin(2 * pi / t));
	w[0][0] = w[0][t] = w[1][0] = w[1][t] = cm(1, 0);
	for (int i = 1; i < t; i++)
		w[0][i] = w[1][t - i] = w[0][i - 1] * g;
	fourier(an);
	reverse(&a[0], &a[n]);
	fourier(ns);
	reverse(&ns[0], &ns[n]);
	for (int i = 0; i < n; i++)
		printf("%f\n", an[i].c - ns[i].c);
}
