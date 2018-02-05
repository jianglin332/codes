#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
long long fc[111];
long long uf[111];
const int mod = 1e9 + 7;
long long pow(long long a, int t)
{
	if (!t)
		return 1;
	long long f = pow(a, t / 2);
	f = f * f % mod;
	if (t & 1)
		f = f * a % mod;
	return f;
}
long long c(int a, int b)
{
	if (a < b)
		return 0;
	return fc[a] * uf[b] % mod * uf[a - b] % mod;
}
int n, m, k;
int u[111], r[111];
long long x[111], g[111], up[111];
int main()
{
	freopen("mark.in", "r", stdin);
	freopen("mark.out", "w", stdout);
	fc[0] = uf[0] = 1;
	for (int i = 1; i < 111; i++)
		fc[i] = fc[i - 1] * i % mod, uf[i] = pow(fc[i], mod - 2);
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++)
		scanf("%d", u + i);
	int mk = n;
	for (int i = 0; i < m; i++)
		scanf("%d", r + i), mk = min(mk, n - r[i]);
	for (int i = mk; i >= k; i--)
	{
		x[i] = c(n - 1, i);
		for (int j = 0; j < m; j++)
			x[i] = x[i] * c(n - 1 - i, r[j] - 1) % mod;
		for (int j = mk; j > i; j--)
			x[i] = (x[i] + mod - c(j, i) * x[j] % mod) % mod;
	}
	long long f = 1;
	for (int i = 0; i < m; i++)
	{
		long long t = 0;
		g[0] = u[i];
		up[0] = 1;
		for (int j = 1; j <= n; j++)
		{
			up[j] = up[j - 1] * u[i] % mod;
			g[j] = pow(u[i] + 1, j + 1) + mod - 1;
			for (int k = 0; k < j; k++)
				g[j] = (g[j] + mod - g[k] * c(j + 1, k) % mod) % mod;
			g[j] = g[j] * pow(j + 1, mod - 2) % mod;
		}
		for (int j = 0; j < r[i]; j++)
			if ((r[i] - 1 - j) & 1)
				t = t + mod - g[n - 1 - j] * c(r[i] - 1, j) % mod * up[j] % mod;
			else
				t = t + g[n - 1 - j] * c(r[i] - 1, j) % mod * up[j] % mod;
		t %= mod;
		f = f * t % mod;
	}
	printf("%lld\n", f * x[k] % mod);
	return 0;
}
