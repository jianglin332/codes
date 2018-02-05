#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef int arr[101010];
arr a, b, d, h, s, e, q;
long long c[101010];
const long long inf = 1e18;
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i), a[i] -= i;
	for (int i = 1; i <= n; i++)
		scanf("%d", b + i);
	memset(d, 0x23, sizeof(d));
	d[0] = 0;
	int mx = 0;
	a[++n] = 1e8 + 1;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < 0)
			continue;
		int l = 0, r = mx + 1;
		while (l + 1 < r)
		{
			int m = (l + r) / 2;
			if (d[m] <= a[i])
				l = m;
			else
				r = m;
		}
		mx = max(h[i] = l + 1, mx);
		d[l + 1] = min(d[l + 1], a[i]);
		s[l + 2]++;
	}
	printf("%d ", mx - 1);
	s[1] = 1;
	for (int i = 2; i <= n; i++)
		s[i] += s[i - 1], e[i] = s[i] - 1;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < 0)
			continue;
		long long t = inf;
		for (int j = s[h[i] - 1]; j <= e[h[i] - 1]; j++)
			if (a[q[j]] <= a[i])
				t = min(t, c[q[j]] + (a[q[j]] * 2 + q[j] * 2 + i - q[j]) * (i - q[j] - 1ll) / 2 + a[i] + i + b[i]);
		c[i] = t;
		q[++e[h[i]]] = i;
	}
	printf("%lld", c[n] - a[n] - n);
	return 0;
}
