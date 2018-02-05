#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
long long t[1010101];
long long f[1010101];
long long x[1010101], nx;
int nw, wn;
int inf = 2e9;
int main()
{
	freopen("freight.in", "r", stdin);
	freopen("freight.out", "w", stdout);
	int n, s;
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++)
		scanf("%lld", t + i), t[i] = max(t[i - 1] + 1, t[i]);
	for (int i = 1; i <= n; i++)
	{
		while (wn < i && t[i] > f[wn] + i - wn - 1)
			wn++;
		wn--;
		while (nw <= nx && t[i] > f[x[nw]] + i - x[nw] - 1)
			nw++;
		f[i] = min(wn ? t[i] - i - wn: inf, nw != nx ? f[x[nw]] - 2 * x[nw] - 1 : inf) + s + s + i + i - 1;
		while (nx >= nw && f[i] - 2 * i - 1 < f[x[nx]] - 2 * x[nx] - 1)
			nx--;
		x[++nx] = i;
	}
	printf("%lld", f[n]);
	return 0;
}

