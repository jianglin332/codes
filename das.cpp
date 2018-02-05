#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct pt
{
	long long x, y;
	bool operator<(const pt &a) const
	{
		if (x == a.x)
			return y > a.y;
		return x < a.x;
	}
}ps[101010];
int np;
long long f[101010];
int main()
{
	int n;
	scanf("%d", &n);
	long long a, b, c, d;
	scanf("%lld/%lld %lld/%lld", &a, &b, &c, &d);
	for (int i = 0; i < n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		ps[np].y = -(x * a - y * b);
		ps[np].x = x * c - y * d;
		if (ps[np].x > 0 && ps[np].y > 0)
			np++;
	}
	sort(ps, ps + np);
	f[0] = 0;
	int ans = 0;
	for (int i = 1; i <= np; i++)
		f[i] = 1e15;
	for (int i = 0; i < np; i++)
	{
		int st = 0, ed = ans + 1;
		while (st + 1 < ed)
		{
			int mid = (st + ed) / 2;
			if (ps[i].y > f[mid])
				st = mid;
			else
				ed = mid;
		}
		if (ps[i].y > f[ans])
			ans++;
		st++;
		if (f[st] > ps[i].y)
			f[st] = ps[i].y;
	}
	printf("%d", ans);
}
