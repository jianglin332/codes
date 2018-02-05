#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define lb(x) ((x) & -(x))
struct bit
{
	int v[202020], n;
	void add(int p, int x)
	{
		while (p <= n)
			v[p] += x, p += lb(p);
	}
	int qry(int p)
	{
		int r = 0;
		while (p)
			r += v[p], p -= lb(p);
		return r;
	}
} b, xl, xr, yl, yr;
struct ev
{
	int tp, x1, y1, x2, y2;
} vs[101010];
struct e
{
	int tp, x, y;
} es[101010], tmp[101010];
int xs[202020], nx;
int ys[202020], ny;
int x1[101010], y1[101010], x2[101010], y2[101010], ni;
int ans[101010];
char bf[5];
int nq;
void work(int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) / 2;
	work(l, mid);
	work(mid + 1, r);
	int to = l;
	for (int i = mid + 1; i <= r; i++)
		if (es[i].tp > 0)
		{
			for (; to <= mid && es[to].x < es[i].x; to++)
				if (es[to].tp <= 0)
					b.add(es[to].y, es[to].tp == 0 ? 1 : -1);
			ans[es[i].tp] += b.qry(es[i].y - 1);
		}
	while (--to >= l)
		if (es[to].tp <= 0)
			b.add(es[to].y, es[to].tp == 0 ? -1 : 1);
	int n1 = l, n2 = mid + 1;
	while (n1 <= mid || n2 <= r)
		if (n2 == r + 1 || (n1 <= mid && es[n1].x < es[n2].x))
			tmp[++to] = es[n1++];
		else
			tmp[++to] = es[n2++];
	for (int i = l; i <= r; i++)
		es[i] = tmp[i];
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", bf);
		if (bf[0] == 'I')
		{
			vs[i].tp = 0;
			scanf("%d%d%d%d", &vs[i].x1, &vs[i].y1, &vs[i].x2, &vs[i].y2);
			xs[++nx] = vs[i].x1;
			ys[++ny] = vs[i].y1;
			xs[++nx] = vs[i].x2;
			ys[++ny] = vs[i].y2;
		}
		else if (bf[0] == 'D')
		{
			scanf("%d", &vs[i].tp);
			vs[i].tp *= -1;
		}
		else if (bf[0] == 'Q')
		{
			vs[i].tp = ++nq;
			scanf("%d%d%d%d", &vs[i].x1, &vs[i].y1, &vs[i].x2, &vs[i].y2);
		}
	}
	sort(xs + 1, xs + nx + 1), sort(ys + 1, ys + ny + 1);
	xl.n = xr.n = nx = unique(xs + 1, xs + nx + 1) - xs - 1;
	b.n = yl.n = yr.n = ny = unique(ys + 1, ys + ny + 1) - ys - 1;
	int ns = 0;
	for (int i = 1; i <= n; i++)
		if (vs[i].tp == 0)
		{
			x1[++ni] = vs[i].x1 = lower_bound(xs + 1, xs + nx + 1, vs[i].x1) - xs;
			y1[ni] = vs[i].y1 = lower_bound(ys + 1, ys + ny + 1, vs[i].y1) - ys;
			x2[ni] = vs[i].x2 = lower_bound(xs + 1, xs + nx + 1, vs[i].x2) - xs;
			y2[ni] = vs[i].y2 = lower_bound(ys + 1, ys + ny + 1, vs[i].y2) - ys;
			xl.add(x2[ni], 1);
			yl.add(y2[ni], 1);
			xr.add(nx - x1[ni] + 1, 1);
			yr.add(ny - y1[ni] + 1, 1);
			ns++;
		}
		else if (vs[i].tp < 0)
		{
			int t = -vs[i].tp;
			vs[i].x1 = x1[t];
			vs[i].y1 = y1[t];
			vs[i].x2 = x2[t];
			vs[i].y2 = y2[t];
			xl.add(x2[t], -1);
			yl.add(y2[t], -1);
			xr.add(nx - x1[t] + 1, -1);
			yr.add(ny - y1[t] + 1, -1);
			ns--;
		}
		else
		{
			vs[i].x1 = lower_bound(xs + 1, xs + nx + 1, vs[i].x1) - xs;
			vs[i].y1 = lower_bound(ys + 1, ys + ny + 1, vs[i].y1) - ys;
			vs[i].x2 = upper_bound(xs + 1, xs + nx + 1, vs[i].x2) - xs - 1;
			vs[i].y2 = upper_bound(ys + 1, ys + ny + 1, vs[i].y2) - ys - 1;
			ans[vs[i].tp] = ns - xl.qry(vs[i].x1 - 1) - xr.qry(nx - vs[i].x2) - yl.qry(vs[i].y1 - 1) - yr.qry(ny - vs[i].y2);
		}
#define rp(a, b, c, d) \
	for (int i = 1; i <= n; i++)\
		if (vs[i].tp <= 0)\
			es[i].tp = vs[i].tp, es[i].x = a, es[i].y = b;\
		else\
			es[i].tp = vs[i].tp, es[i].x = c, es[i].y = d;\
	work(1, n);
	rp(vs[i].x2, vs[i].y2, vs[i].x1, vs[i].y1);
	rp(vs[i].x2, ny - vs[i].y1 + 1, vs[i].x1, ny - vs[i].y2 + 1);
	rp(nx - vs[i].x1 + 1, vs[i].y2, nx - vs[i].x2 + 1, vs[i].y1);
	rp(nx - vs[i].x1 + 1, ny - vs[i].y1 + 1, nx - vs[i].x2 + 1, ny - vs[i].y2 + 1);
	for (int i = 1; i <= nq; i++)
		printf("%d\n", ans[i]);
}
