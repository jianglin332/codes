#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int f[50505];
int g[50505];
int e[2010], sf[2010], st[2010], c[2010], nf, nt;
void work()
{
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	nf = nt = 0;
	for (int i = 0; i < n; i++)
	{
		int t, u, v;
		scanf("%d%d%d", &t, &u, &v);
		int k = 1;
		while (v >= k)
		{
			e[nf] = t * k;
			sf[nf++] = u * k;
			v -= k;
			k *= 2;
		}
		if (v)
		{
			e[nf] = t * v;
			sf[nf++] = u * v;
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		int k = 1;
		while (z >= k)
		{
			st[nt] = x * k;
			c[nt++] = y * k;
			z -= k;
			k *= 2;
		}
		if (z)
		{
			st[nt] = x * z;
			c[nt++] = y * z;
		}
	}
	for (int i = 0; i < nf; i++)
		for (int j = 50000; j >= sf[i]; j--)
			f[j] = max(f[j], f[j - sf[i]] + e[i]);
	int ts = -1;
	for (int i = 0; i <= 50000; i++)
		if (f[i] >= p)
		{
			ts = i;
			break;
		}
	if (ts == -1)
	{
		printf("TAT\n");
		return;
	}
	for (int i = 0; i < nt; i++)
		for (int j = 50000; j >= c[i]; j--)
			g[j] = max(g[j], g[j - c[i]] + st[i]);
	for (int i = 0; i <= 50000; i++)
		if (g[i] >= ts)
		{
			printf("%d\n", i);
			return;
		}
	printf("TAT\n");
	return;
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
}
