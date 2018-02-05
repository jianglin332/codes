#include <cstdio>
#include <algorithm>
using namespace std;
struct pt
{
	int l, w;
	bool operator<(const pt &a) const
	{
		if (w == a.w)
			return l > a.l;
		return w > a.w;
	}
} ps[50505];
long long l[50505], w[50505], np;
long long f[50505];
int q[50505], st, ed;
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d", &ps[i].l, &ps[i].w);
	sort(ps, ps + n);
	long long nw = 0;
	for (int i = 0; i < n; i++)
		if (ps[i].l > nw)
			l[++np] = ps[i].l, w[np] = ps[i].w, nw = ps[i].l;
	f[0] = 0;
	q[0] = 1;
	for (int i = 1; i <= np; i++)
	{
		while (st < ed && f[q[st + 1] - 1] - f[q[st] - 1] < l[i] * (w[q[st]] - w[q[st + 1]]))
			st++;
		f[i] = f[q[st] - 1] + l[i] * w[q[st]];
		while (st < ed && (f[i] - f[q[ed] - 1]) * (w[q[ed - 1]] - w[q[ed]])< (f[q[ed] - 1] - f[q[ed - 1] - 1])* (w[q[ed]] - w[i + 1]))
			ed--;
		q[++ed] = i + 1;
	}
	printf("%lld", f[np]);
}
