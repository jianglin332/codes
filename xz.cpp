#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
long long gcd(long long a, long long b)
{
	if (!b)
		return a;
	return gcd(b, a % b);
}
int nk;
struct sec
{
	int l, r, n, ans;
	bool operator<(const sec &a) const
	{
		if (l / nk == a.l / nk)
			return r < a.r;
		return l < a.l;
	}
}ss[50505];
int c[50505];
int nc[50505];
bool cmp(const sec &a, const sec &b)
{
	return a.n < b.n;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	nk = sqrt(n);
	long long nw = 0;
	for (int i = 1; i <= n; i++)
		scanf("%d", c + i);
	int l = 1, r = 1;
	nc[c[1]]++;
	for (int i = 0; i < m; i++)
		ss[i].n = i, scanf("%d%d", &ss[i].l, &ss[i].r);
	sort(ss, ss + m);
	for (int i = 0; i < m; i++)
	{
		int nl = ss[i].l, nr = ss[i].r;
		while (l > nl)
			nw = nw - nc[c[--l]] * (nc[c[l]] - 1ll) + (++nc[c[l]]) * (nc[c[l]] - 1ll);
		while (r < nr)
			nw = nw - nc[c[++r]] * (nc[c[r]] - 1ll) + (++nc[c[r]]) * (nc[c[r]] - 1ll);
		while (l < nl)
			nw = nw - nc[c[l]] * (nc[c[l]] - 1ll) + (--nc[c[l]]) * (nc[c[l++]] - 1ll);
		while (r > nr)
			nw = nw - nc[c[r]] * (nc[c[r]] - 1ll) + (--nc[c[r]]) * (nc[c[r--]] - 1ll);
		ss[i].ans = nw;
	}
	sort(ss, ss + m, cmp);
	for (int i = 0; i < m; i++)
	{
		if (ss[i].ans == 0)
		{
			printf("0/1\n");
			continue;
		}
		long long t = (ss[i].r - ss[i].l + 1ll) * (ss[i].r - ss[i].l), f = gcd(t, ss[i].ans);
		printf("%lld/%lld\n", ss[i].ans / f, t / f);
	}
}
