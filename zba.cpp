#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct node
{
	int vl, nb;
	node *nx;
};
struct hash_table
{
	node *tb[1048576];
	node t[303030];
	int nt;
	int hash(int a)
	{
		return (a * 37 + (a >> 15) * 73) & 1048575;
	}
	void ins(int v, int n)
	{
		node *nw = &t[nt++];
		nw->vl = v;
		nw->nb = n;
		nw->nx = tb[hash(v)];
		tb[hash(v)] = nw;
	}
	void init()
	{
		memset(tb, 0, sizeof(tb));
		memset(t, 0, sizeof(t));
		nt = 0;
	}
	int get(int v)
	{
		node *nw = tb[hash(v)];
		while (nw)
		{
			if (nw->vl == v)
				return nw->nb;
			nw = nw->nx;
		}
		return -1;
	}
}ht;
int enc(int x, int y)
{
	return (x + 1010) * 2020 + y + 1010;
}
int x[303030], y[303030];
int fa[303030], dep[303030], val[303030], nv;
int gf(int x)
{
	int f = x, v = 0;
	while (f != fa[f])
	{
		v ^= val[f];
		f = fa[f];
	}
	int a = x;
	while (a != f)
	{
		val[a] ^= (v ^= val[a]);
		int o = fa[a];
		fa[a] = f;
		a = o;
	}
	return f;
}
int gc(int a, int b)
{
	int chg = 0;
	if ((x[a] >= 0 && y[a] > 0 && x[b] >= 0 && y[b] == 0) || (x[b] >= 0 && y[b] > 0 && x[a] >= 0 && y[a] == 0))
		chg = 1;
	return chg;
}
void merge(int a, int b)
{
	int faa = gf(a), fab = gf(b);
	if (faa == fab)
		return;
	if (dep[faa] == dep[fab])
		dep[faa]++;
	if (dep[faa] < dep[fab])
		swap(a, b), swap(faa, fab);
	int chg = gc(a, b);
	fa[fab] = faa;
	val[fab] = chg ^ val[b] ^ val[a];
}
int os[6][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 0}, {-1, -1}, {0, -1}};
int allocate(int a, int b)
{
	if (ht.get(enc(a, b)) != -1)
		return 1;
	int t[6] = {0}, nt = 0;
	for (int i = 0; i < 6; i++)
	{
		int dx = a + os[i][0], dy = b + os[i][1];
		int nw = ht.get(enc(dx, dy));
		if (nw != -1)
			t[nt++] = nw;
	}
	int ft[6] = {0};
	for (int i = 0; i < nt; i++)
		ft[i] = gf(t[i]);
	x[nv] = a, y[nv] = b, fa[nv] = nv;
	for (int i = 0; i < nt; i++)
		for (int j = i + 1; j < nt; j++)
			if (ft[i] == ft[j])
				if ((val[i] ^ gc(i, nv)) != (val[j] ^ gc(j, nv)))
					return 0;
	ht.ins(enc(a, b), nv);
	for (int i = 0; i < nt; i++)
		merge(nv, t[i]);
	nv++;
	return 1;
}
void work()
{
	ht.init();
	memset(fa, 0, sizeof(fa));
	memset(val, 0, sizeof(val));
	memset(dep, 0, sizeof(dep));
	nv = 0;
	int n;
	scanf("%d", &n);
	unsigned ans = 0;
	for (int i = 0; i < n; i++)
	{
		int x, y, z, c;
		scanf("%d%d%d%d", &x, &y, &z, &c);
		x -= z, y -= z;
		if (x == 0 && y == 0)
			ans += c;
		else if (!allocate(x, y))
			ans += c;
	}
	printf("%u\n", ans);
}
int main()
{
	freopen("zba.in", "r", stdin);
	freopen("zba.out", "w", stdout);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
}
