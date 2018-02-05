#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[101010];
int nw[101010];
int q[101010], top = -1;
int l[101010], r[101010];
long long buc[101010];
int n, t;
long long c;
int mx = 0;
bool can(int k)
{
	memset(buc, 0, sizeof(buc));
	nw[0] = nw[n + 1] = 1e9 + 7;
	int mx = 0;
	for (int i = 1; i <= n; i++)
	{
		nw[i] = max(0, a[i] - k);
		mx = max(mx, nw[i]);
	}
	top = -1;
	q[++top] = 0;
	for (int i = 1; i <= n; i++)
	{
		while (nw[i] > nw[q[top]])
			top--;
		l[i] = q[top];
		q[++top] = i;
	}
	top = -1;
	q[++top] = n + 1;
	for (int i = n; i; i--)
	{
		while (nw[i] >= nw[q[top]])
			top--;
		r[i] = q[top];
		q[++top] = i;
	}
	long long cost = mx * 1ll * n;
	for (int i = 1; i <= n; i++)
	{
		if (nw[i] == mx)
			continue;
		if ((l[i] == 0 || r[i] == n + 1))
			cost -= (min(nw[l[i]], nw[r[i]]) - nw[i]) * (r[i] - l[i] - 1ll);
		else
			buc[r[i] - l[i] - 1] += min(nw[l[i]], nw[r[i]]) - nw[i];
	}
	int tm = mx;
	if (tm > t)
		return 0;
	int nl = n;
	while (cost > c && tm < t)
	{
		while (nl && !buc[nl])
			nl--;
		if (!nl)
			return 0;
		long long pl = min(t - tm - 0ll, buc[nl]);
		tm += pl;
		cost -= pl * nl;
		buc[nl] -= pl;
	}
	return cost <= c;
}
int main()
{
	scanf("%d%d%lld", &n, &t, &c);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		mx = max(mx, a[i]);
	}
	a[0] = a[n + 1] = 1e9 + 7;
	int st = 0, ed = mx;
	while (st + 1 < ed)
	{
		int mid = (st + ed) / 2;
		if (can(mid))
			ed = mid;
		else
			st = mid;
	}
	printf("%d", ed);
}
