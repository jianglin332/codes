#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int _2[20] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288};
struct nd
{
	int s, l, r;
	nd *lch, *rch;
	nd(int a, int b)
	{
		l = a, r = b;
		s = 0;
		lch = rch = 0;
	}
	nd(int a, int b, nd *lh, nd *rh)
	{
		l = a, r = b, s = 0;
		lch = lh, rch = rh;
		s = lch->s + rch->s;
	}
}*root[101010];
int tm[101010], nr = 0, n, ne = 0, king;
int f[101010][20];
int dep[101010];
int head[101010], sr[101010];
struct ed
{
	int to, nx;
}es[101010];
int tf[101010], nt = 0, tn = 0, in[101010], out[101010];
void dfs(int a)
{
	in[a] = nt++;
	int i = 0;
	while (tn - _2[++i] >= 0)
		f[a][i] = tf[tn - _2[i]];
	tf[tn++] = a;
	dep[a] = tn;
	for (int i = head[a]; i != -1; i = es[i].nx)
		dfs(es[i].to);
	out[a] = nt++;
	tn--;
}
void convert()
{
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++)
	{
		if (!f[i][0])
		{
			king = i;
			continue;
		}
		es[ne].to = i;
		es[ne].nx = head[f[i][0]];
		head[f[i][0]] = ne++;
	}   
}
void maketree(int a, int b, nd *&d)
{
	d = new nd(a, b);
	if (a == b)
	{
		d->s = sr[a];
		return;
	}
	maketree(a, ((a + b) >> 1), d->lch);
	maketree(((a + b) >> 1) + 1, b, d->rch);
	d->s = d->lch->s + d->rch->s;
}
nd *ins(int d, nd *nod)
{
	if (nod->r == nod->l)
		return new nd(nod->l, nod->r);
	else if (nod->lch->r >= d)
		return new nd(nod->l, nod->r, ins(d, nod->lch), nod->rch);
	else
		return new nd(nod->l, nod->r, nod->lch, ins(d, nod->rch));
}
int lca(int a, int b)
{
	if (dep[a] < dep[b])
		swap(a, b);
	int d = dep[a] - dep[b];
	for (int i = 0; i < 19; i++)
		if (d & (1 << i))
			a = f[a][i];
	int ans;
	if (a == b)
		return a;
	for (int i = 18; i >= 0; i--)
		if (f[a][i] && f[a][i] != f[b][i])
		{
			a = f[a][i];
			b = f[b][i];
		}
	return f[a][0];
}
int qry(int a, int b, nd *rt)
{
	if (a > b)
		return 0;
	if (rt->l >= a && rt->r <= b)
	{
		return rt->s;
	}
	int ans = 0;
	if (rt->lch->r >= a)
		ans += qry(a, b, rt->lch);
	if (rt->rch->l <= b)
		ans += qry(a, b, rt->rch);
	return ans;
}
void init()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &f[i][0]);
	convert();
	dfs(king);
	for (int i = 1; i <= n; i++)
	{
		sr[in[i]] = 1;
		sr[out[i]] = -1;
	}
	maketree(0, nt - 1, root[0]);
}
int d1(int a, int b, int y)
{
	return dep[b] - dep[a] + qry(in[a], in[b] - 1, root[nr]) - qry(in[a], in[b] - 1, root[y]);
}
int d2(int a, int b, int y)
{
	return dep[b] - dep[a] + qry(in[a] + 1, in[b], root[nr]) - qry(in[a] + 1, in[b], root[y]);
}
int bi1(int fr, int to, int k, int y)
{
	int mid, t, st = fr, ed = to;
	for (int i = 18; i >= 0; i--)
		if (dep[f[st][i]] > dep[ed])
		{
			mid = f[st][i];
			t = d1(mid, st, y);
			if (t < k)
			{
				k -= t;
				ed = mid;
			}
			else
			{
				st = mid;
			}
		}
	return st;
}
int bi2(int fr, int to, int k, int y)
{
	int mid, t, st = to, ed = fr;
	for (int i = 18; i >= 0; i--)
		if (dep[f[st][i]] > dep[ed])
		{
			mid = f[st][i];
			t = d2(ed, mid, y);
			if (t >= k)
				st = mid;
			else
			{
				k -= t;
				ed = mid;
			}
		}
	return st;
}
int gt(int fr, int to, int k, int y)
{
	int lc = lca(fr, to);
	int al = d1(lc, fr, y);
	int all = al + d1(lc, to, y) - 1 + qry(in[lc], in[lc], root[y]) - qry(in[lc], in[lc], root[nr]);
	if (k > all)
		return -1;
	else if (k <= al)
		return bi1(fr, lc, k, y);
	else
		return bi2(lc, f[to][0], k - al, y);
}
void work()
{
	int m, t;
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &t);
		if (t == 1)
		{
			int c;
			scanf("%d", &c);
			nd *tm = ins(in[c], root[nr]);
			root[++nr] = ins(out[c], tm);
		}
		else if (t == 2)
		{
			root[nr + 1] = root[nr];
			nr++;
			int a, b, k, y;
			scanf("%d%d%d%d", &a, &b, &k, &y);
			printf("%d\n", gt(a, b, k, y));
		}
	}
}
int main()
{
	init();
	work();
}

