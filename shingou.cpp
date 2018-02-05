#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
int inf = 2000000;
struct pt
{
	int x, y;
	pt(int x, int y):x(x), y(y){}
	pt operator+(int a)
	{
		return pt(x + a, y + a);
	}
};
vector<pt> usr[101010];
int r[101010];
struct range
{
	pt l, r;
	range(pt l = pt(-inf, -inf), pt r = pt(inf, inf)):l(l), r(r){}
	void upd(range a)
	{
		l.x = max(l.x, a.l.x);
		l.y = max(l.y, a.l.y);
		r.x = min(r.x, a.r.x);
		r.y = min(r.y, a.r.y);
	}
	range operator+(int a)
	{
		return range(l + -a, r + a);
	}
	pt p()
	{
		if (l.x + l.y & 1)
			l.x++;
		return l;
	}
} rg[101010];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", r + i);
	for (int i = 0; i < m; i++)
	{
		int u, a, b;
		scanf("%d%d%d", &u, &a, &b);
		usr[u].push_back(pt(a + b, b - a));
	}
	for (int i = n; i; i--)
	{
		vector<pt> &nw = usr[i];
		for (int j = 0; j < nw.size(); j++)
			rg[i].upd(range(nw[j] + -r[i], nw[j] + r[i]));
		if (i != n)
			rg[i].upd(rg[i + 1] + (r[i + 1] - r[i]));
	}
	for (int i = 1; i <= n; i++)
	{
		pt p = rg[i].p();
		printf("%d %d\n", (p.x - p.y) / 2, (p.x + p.y) / 2);
		if (i < n)
			rg[i + 1].upd(rg[i] + (r[i + 1] - r[i]));
	}
	return 0;
}
