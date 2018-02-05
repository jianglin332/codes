#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int x[15], y[15], r[22], w[22];
int f[4096];
double dis(double x1, double y1, double x2, double y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int main()
{
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d%d", x + i, y + i);
	for (int i = 0; i < k; i++)
	{
		scanf("%d%d", r + i, w + i);
		r[i] *= r[i];
	}
	memset(f, 0x33, sizeof(f));
	f[0] = 0;
	for (int i = 1; i < (1 << n); i++)
	{
		int tx[15] = {0}, nt = 0;
		for (int j = 0; j < n; j++)
			if (i & (1 << j))
				tx[nt++] = j;
		double md = 1e9;
		if (nt == 1)
			md = 0;
		else if (nt == 2)
			md = dis(x[tx[0]], y[tx[0]], x[tx[1]], y[tx[1]]) / 4;
		else
			for (int tt = 0; tt < nt; tt++)
				for (int uu = tt + 1; uu < nt; uu++)
				{
					double xx = (x[tx[tt]] + x[tx[uu]]) / 2.;
					double yy = (y[tx[tt]] + y[tx[uu]]) / 2.;
					double r = dis(xx, yy, x[tx[tt]], y[tx[tt]]);
					if (r + 1e-9 > md)
						continue;
					int flg = 1;
					for (int j = 0; j < nt; j++)
					{
						if (dis(xx, yy, x[tx[j]], y[tx[j]]) - 1e-5 > r)
						{
							flg = 0;
							break;
						}
					}
					if (flg)
						md = r;
					else
						for (int vv = uu + 1; vv < nt; vv++)
						{
							int t = tx[tt];
							int u = tx[uu];
							int v = tx[vv];
							double xx = (x[t] * x[t] * (y[u] - y[v]) + x[u] * x[u] * (y[v] - y[t]) + x[v] * x[v] * (y[t] - y[u]) - (y[t] - y[u]) * (y[u] - y[v]) * (y[v] - y[t])) /
								(2. * (x[t] * (y[u] - y[v]) + x[u] * (y[v] - y[t]) + x[v] * (y[t] - y[u])));
							double yy = (y[t] * y[t] * (x[u] - x[v]) + y[u] * y[u] * (x[v] - x[t]) + y[v] * y[v] * (x[t] - x[u]) - (x[t] - x[u]) * (x[u] - x[v]) * (x[v] - x[t])) /
								(-2. * (x[t] * (y[u] - y[v]) + x[u] * (y[v] - y[t]) + x[v] * (y[t] - y[u])));
							double r = dis(xx, yy, x[t], y[t]);
							if (r + 1e-9 > md)
								continue;
							int flg = 1;
							for (int j = 0; j < nt; j++)
							{
								if (dis(xx, yy, x[tx[j]], y[tx[j]]) - 1e-5 > r)
								{
									flg = 0;
									break;
								}
							}
							if (flg)
								md = r;
						}
				}
		for (int j = 0; j < k; j++)
			if (md - 1e-5 < r[j])
				f[i] = min(f[i], w[j]);
	}
	for (int i = 0; i < (1 << n); i++)
		for (int j = 0; j < (1 << n); j++)
			f[i | j] = min(f[i | j], f[i] + f[j]);
	printf("%d", f[(1 << n) - 1]);
}
