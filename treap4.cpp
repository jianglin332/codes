#include <stdio.h>
#include <string.h>
const int mod = 10301;
struct mat
{
	int v[3][3];
	mat()
	{
		memset(v, 0, sizeof(v));
	}
	mat operator * (const mat &a) const
	{
		mat ret;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				int &mt = ret.v[i][j];
				for (int k = 0; k < 3; k++)
					mt = (mt + v[k][j] * a.v[i][k]) % mod;
			}
		return ret;
	}
	mat operator + (const mat &a) const
	{
		mat ret;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				ret.v[i][j] = (v[i][j] + a.v[i][j]) % mod;
		return ret;
	}
}ml, mr, one;
struct node
{
	int l, r;
	node *lch, *rch;
	mat m;
	mat lazy;
	void down()
	{
		if (!lch)
			return;
		rch->m = rch->m * lazy;
		rch->lazy = rch->lazy * lazy;
		lch->m = lch->m * lazy;
		lch->lazy = lch->lazy * lazy;
		lazy = one;
	}
	void upd()
	{
		if (!lch)
			return;
		m = rch->m + lch->m;
	}
} *root;
void init()
{
	one.v[0][0] = one.v[1][1] = one.v[2][2] = 1;
	ml = mr = one;
	ml.v[0][1] = 1;
	ml.v[0][2] = 2;
	ml.v[2][1] = 1;
	mr.v[1][0] = 1;
	mr.v[1][2] = 2;
	mr.v[2][0] = 1;
}
int a[101010];
int b[101010];
void maketree(int l, int r, node *&rt = root)
{
	rt = new node;
	rt->lazy = one;
	if (l == r)
	{
		rt->l = rt->r = l;
		rt->m.v[0][0] = (a[l] * a[l]) % mod;
		rt->m.v[1][0] = (b[l] * b[l]) % mod;
		rt->m.v[2][0] = (a[l] * b[l]) % mod;
		rt->lch = rt->rch = 0;
		return;
	}
	rt->l = l;
	rt->r = r;
	maketree(l, (l + r) / 2, rt->lch);
	maketree((l + r) / 2 + 1, r, rt->rch);
	rt->upd();
}
void mul(int l, int r, mat &m, node *rt = root)
{
	if (rt->l >= l && rt->r <= r)
	{
		rt->m = rt->m * m;
		rt->lazy = rt->lazy * m;
		return;
	}
	if (rt->l > r || rt->r < l)
		return;
	rt->down();
	if (rt->lch->r >= l)
		mul(l, r, m, rt->lch);
	if (rt->rch->l <= r)
		mul(l, r, m, rt->rch);
	rt->upd();
}
int cnt(int l, int r, node *rt = root)
{
	if (rt->l >= l && rt->r <= r)
	{
		return rt->m.v[2][0];
	}
	if (rt->l > r || rt->r < l)
		return 0;
	rt->down();
	int ret = 0;
	if (rt->lch->r >= l)
		ret += cnt(l, r, rt->lch);
	if (rt->rch->l <= r)
		ret += cnt(l, r, rt->rch);
	return ret % mod;
}
int main()
{
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", a + i, b + i);
	maketree(1, n);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1)
			mul(b, c, ml);
		if (a == 2)
			mul(b, c, mr);
		if (a == 3)
			printf("%d\n", cnt(b, c));
	}
	return 0;
}
