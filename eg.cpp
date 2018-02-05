#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int fa[202020], rd[202020], cl[202020], bl[202020], wt[202020], ib[202020], iw[202020];
int main()
{
	freopen("gametree.in", "r", stdin);
	freopen("gametree.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
		scanf("%d", fa + i);
	for (int i = 2; i <= n; i++)
		cl[i] = cl[fa[i]] ^ 1, rd[fa[i]]++;
	for (int i = 1; i <= n; i++)
		if (cl[i])
			wt[i] = 222222, bl[i] = 0;
		else
			wt[i] = 0, bl[i] = 222222;
	for (int i = n; i >= 2; i--)
	{
		if (!rd[i])
			bl[i] = wt[i] = 1;
		if (cl[i])
			bl[fa[i]] = min(bl[fa[i]], bl[i]), wt[fa[i]] += wt[i];
		else
			wt[fa[i]] = min(wt[fa[i]], wt[i]), bl[fa[i]] += bl[i];
	}
	ib[1] = iw[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (cl[i])
			iw[i] = iw[fa[i]], ib[i] = (ib[fa[i]] && bl[i] == bl[fa[i]]);
		else
			ib[i] = ib[fa[i]], iw[i] = (iw[fa[i]] && wt[i] == wt[fa[i]]);
	}
	int a = 222222, b = 0, c = 0;
	for (int i = 1; i <= n; i++)
		if (!rd[i] && iw[i] && ib[i])
			a = min(i, a), b++, c ^= i;
	printf("%d %d %d", a, b, c);
	return 0;
}
