#include <stdio.h>
#include <algorithm>
using namespace std;
struct node
{
	node *lch, *rch;
	int s;
} *rs[202020], cc[202020 * 22];
int nc = 0;
node *Newnode(int l, int r)
{
	node *nw = &cc[nc++];
	if (l != r)
		nw->lch = Newnode(l, (l + r) / 2), nw->rch = Newnode((l + r) / 2 + 1, r);
	return nw;
}
node *Newnode(node *a)
{
	node *nw = &cc[nc++];
	nw->s = a->s;
	nw->lch = a->lch;
	nw->rch = a->rch;
	return nw;
}
node *add(node *a, int p, int v, int l, int r)
{
	a = Newnode(a);
	a->s += v;
	if (l == r);
	else if (p <= (l + r) / 2)
		a->lch = add(a->lch, p, v, l, (l + r) / 2);
	else
		a->rch = add(a->rch, p, v, (l + r) / 2 + 1, r);
	return a;
}
int qry(node *a, int ll, int rr, int l, int r)
{
	if (ll > rr)
		return 0;
	if (ll <= l && r <= rr)
		return a->s;
	int t = 0;
	if (ll <= (l + r) / 2)
		t += qry(a->lch, ll, rr, l, (l + r) / 2);
	if (rr > (l + r) / 2)
		t += qry(a->rch, ll, rr, (l + r) / 2 + 1, r);
	return t;
}
int rx[404040], nx;
int x[101010], y[101010], qx[101010], qy[101010];
int l[404040], r[404040];
int rk[101010];
bool cmp(int a, int b)
{
	return x[a] < x[b];
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d%d", x + i, y + i), rx[nx++] = x[i], rx[nx++] = y[i];
	for (int i = 0; i < m; i++)
		scanf("%d%d", qx + i, qy + i), rx[nx++] = qx[i], rx[nx++] = qy[i];
	sort(rx, rx + nx);
	nx = unique(rx, rx + nx) - rx;
	for (int i = 0; i < n; i++)
	{
		x[i] = lower_bound(rx, rx + nx, x[i]) - rx + 1;
		y[i] = lower_bound(rx, rx + nx, y[i]) - rx + 1;
		r[x[i]]++;
		rk[i] = i;
	}
	for (int i = nx - 2; i >= 0; i--)
		r[i] += r[i + 1];
	for (int i = 0; i < m; i++)
	{
		qx[i] = lower_bound(rx, rx + nx, qx[i]) - rx + 1;
		qy[i] = lower_bound(rx, rx + nx, qy[i]) - rx + 1;
	}
	sort(rk, rk + n, cmp);
	int nw = 0;
	rs[0] = Newnode(0, nx);
	for (int i = 1; i <= nx; i++)
	{
		rs[i] = rs[i - 1];
		while (nw < n && x[rk[nw]] <= i)
			rs[i] = add(rs[i], y[rk[nw++]], 1, 0, nx);
	}
	for (int i = 0; i < m; i++)
	{
		int a1 = qry(rs[qx[i] - 1], qx[i] + 1, qy[i] - 1, 0, nx);
		int a2 = qry(rs[nx], qy[i] + 1, nx, 0, nx) - qry(rs[qx[i]], qy[i] + 1, nx, 0, nx) - r[qy[i]];
		int a3 = qry(rs[nx], 0, qy[i], 0, nx) - qry(rs[qx[i] - 1], 0, qy[i], 0, nx);
		int a4 = qry(rs[qx[i]], qy[i], nx, 0, nx);
		printf("%d %d %d %d\n", a1, a2, a3, a4);
	}
	return 0;
}
