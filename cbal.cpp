#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
long long a1[333][333];
long long a2[333][333];
long long a0[333][333];
int val[101010];
int tmp[101010];
long long xx0[333][101010];
long long x0[333][101010];
long long nu[333][101010];
char s[101010];
int bs, nb;
template<typename T>
	void clr(T &a, int b, int c)
{
	for (int i = 0; i <= b; i++)
		for (int j = 0; j <= c; j++)
			a[i][j] = 0;
}
int vs[101010];
int pl[101010];
long long c0[101010], c1[101010], c2[101010];
long long solve(int x, int y, int t)
{
	int bx = (x - 1) / bs + 1;
	int by = (y - 1) / bs + 1;
	long long ans = 0;
	int is0 = t == 0, is1 = t == 1, is2 = t == 2;
#define pl(a, b, c) (is0 ? a : (is1 ? b : c))
	if (bx == by)
	{
		for (int i = x; i <= y; i++)
		{
			int v = val[i];
			ans += pl(c0[v], c0[v] * i - c1[v], c0[v] * i * i - 2 * i * c1[v] + c2[v]);
			v = val[i - 1];
			c0[v]++, c1[v] += i - 1, c2[v] += (i - 1) * (i - 1ll);
		}
		for (int i = x - 1; i < y; i++)
			c0[val[i]] = c1[val[i]] = c2[val[i]] = 0;
		return ans;
	}
	ans = pl(a0[bx + 1][by - 1], a1[bx + 1][by - 1], a2[bx + 1][by - 1]);
	int nv = 0;
	for (int i = x; i <= bx * bs; i++)
		pl[nv] = i, vs[nv++] = val[i];
	for (int i = (by - 1) * bs + 1; i <= y; i++)
		pl[nv] = i, vs[nv++] = val[i];
	for (int j = 0; j < nv; j++)
	{
		int v = vs[j];
		long long i = pl[j];
		ans += pl(c0[v], c0[v] * i - c1[v], c0[v] * i * i - 2 * i * c1[v] + c2[v]);
		v = val[i - 1];
		c0[v]++, c1[v] += i - 1, c2[v] += (i - 1) * (i - 1ll);
	}
	for (int i = 0; i < nv; i++)
		c0[val[pl[i] - 1]] = c1[val[pl[i] - 1]] = c2[val[pl[i] - 1]] = 0;
	if (bx + 1 < by)
	{
		for (int i = x; i <= bx * bs; i++)
		{
			int v = val[i - 1];
			ans += pl(nu[by - 1][v] - nu[bx][v], 
					x0[by - 1][v] - x0[bx][v] - (i - 1) * (nu[by - 1][v] - nu[bx][v]), 
					xx0[by - 1][v] - xx0[bx][v] - 2 * (i - 1) * (x0[by - 1][v] - x0[bx][v]) + (nu[by - 1][v] - nu[bx][v]) * (i - 1) * (i - 1));
		}
		for (int i = (by - 1) * bs + 1; i <= y; i++)
		{
			int v = val[i];
			int s = val[(by - 1) * bs] == v, t = val[bx * bs] == v;
			long long num = nu[by - 1][v] - nu[bx][v] - s + t;
			long long nu1 = x0[by - 1][v] - x0[bx][v] - (s ? (by - 1) * bs : 0) + (t ? bx * bs : 0);
			long long nu2 = xx0[by - 1][v] - xx0[bx][v] - (s ? (by - 1ll) * bs * (by - 1ll) * bs : 0) + (t ? bx * bs * 1ll * bx * bs : 0);
			ans += pl(num, -nu1 + (i + 1) * num, nu2 - 2 * (i + 1) * nu1 + num * (i + 1) * (i + 1));
		}
	}
	return ans;
}
void work()
{
	scanf("%s", s + 1);
	int l = strlen(s + 1);
	bs = sqrt(l) + 1;
	for (int i = 0; i <= l; i++)
		tmp[i] = val[i] = 0;
	for (int i = 1; i <= l; i++)
		tmp[i - 1] = val[i] = val[i - 1] ^ (1 << s[i] - 'a');
	sort(tmp, tmp + l);
	int u = unique(tmp, tmp + l) - tmp;
	nb = (l - 1) / bs + 1;
	clr(a0, nb, nb);
	clr(a1, nb, nb);
	clr(a2, nb, nb);
	clr(xx0, nb, u);
	clr(x0, nb, u);
	clr(nu, nb, u);
	for (int i = 1; i <= l; i++)
		val[i] = lower_bound(tmp, tmp + u, val[i]) - tmp;
	for (int i = 1; i <= nb; i++)
	{
		long long *nn = nu[i], *np = nu[i - 1];
		long long *xn = x0[i], *xp = x0[i - 1];
		long long *xxn = xx0[i], *xxp = xx0[i - 1];
		int lm = min(i * bs, l);
		for (int j = (i - 1) * bs + 1; j <= lm; j++)
		{
			nn[val[j]]++, xn[val[j]] += j, xxn[val[j]] += j * 1ll * j;
		}
		for (int j = 0; j < u; j++)
			nn[j] += np[j], xn[j] += xp[j], xxn[j] += xxp[j];
	}
	for (int i = 1; i <= nb; i++)
	{
		int lm = min(i * bs, l);
		long long &a1i = a1[i][i], &a2i = a2[i][i];
		long long &a0i = a0[i][i];
		for (int j = (i - 1) * bs; j < lm; j++)
			for (int k = j + 2; k <= lm; k++)
				if (val[j] == val[k])
					a0i++, a1i += k - j, a2i += (k - j) * (k - j);
		for (int j = i + 1; j <= nb; j++)
		{
			long long *nn = nu[j], *np = nu[i];
			long long *xn = x0[j], *xp = x0[i];
			long long *xxn = xx0[j], *xxp = xx0[i];
			long long &a1j = a1[i][j], &a2j = a2[i][j];
			long long &a0j = a0[i][j];
			for (long long k = (i - 1) * bs; k < lm; k++)
			{
				int v = val[k];
				long long num = nn[v] - np[v];
				long long x = xn[v] - xp[v];
				a0j += num;
				a1j += x - num * k;
				a2j += xxn[v] - xxp[v] - 2 * x * k + num * k * k;
			}
			a0j += a0i, a1j += a1i, a2j += a2i;
		}
	}
	int a = 0, b = 0;
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int x, y, t;
		scanf("%d%d%d", &x, &y, &t);
		x = (x + a) % l + 1;
		y = (y + b) % l + 1;
		if (x > y)
			swap(x, y);
		long long ans = solve(x, y, t);
		printf("%lld\n", ans);
		a = b;
		b = ans;
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
}
