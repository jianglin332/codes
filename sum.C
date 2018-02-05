#include <cstdio>
const unsigned int mod = 1e9 + 7;
struct nd
{
	unsigned int s, l, r, pl;
	nd *lch, *rch;
	nd()
	{
		lch = rch = 0;
		l = r = s = pl = 0;
	}
	nd(unsigned int _l, unsigned int _r, nd *lc, nd *rc):l(_l), r(_r), s(0), lch(lc), rch(rc), pl(0){}
} *r1, *r2;
nd *mt(unsigned int l, unsigned int r)
{
	if (l == r)
		return new nd(l, r, 0, 0);
	return new nd(l, r, mt(l, (l + r) / 2), mt((l + r) / 2 + 1, r));
}
unsigned int n, m;
unsigned int dx[202020];
unsigned int sx[202020];
inline unsigned long long gx(unsigned int a, unsigned int b)
{
	return (sx[a] - sx[b + 1] + mod) % mod;
}
inline void down(nd *rt)
{
	if ((!rt->pl) || rt->lch == rt->rch)
		return;
	rt->rch->s = ((long long)rt->pl * (rt->rch->r - rt->rch->l + 1) + rt->rch->s) % mod;
	rt->rch->pl = (rt->pl + rt->rch->pl) % mod;
	rt->lch->s = ((long long)rt->pl * (rt->lch->r - rt->lch->l + 1) + rt->lch->s) % mod;
	rt->lch->pl = (rt->pl + rt->lch->pl) % mod;
	rt->pl = 0;
}
inline void down2(nd *rt)
{
	if ((!rt->pl) ||rt->lch == rt->rch)
		return;
	rt->rch->s = ((long long)rt->pl * gx(rt->rch->l, rt->rch->r) + rt->rch->s) % mod;
	rt->rch->pl = (rt->pl + rt->rch->pl) % mod;
	rt->lch->s = ((long long)rt->pl * gx(rt->lch->l, rt->lch->r) + rt->lch->s) % mod;
	rt->lch->pl = (rt->pl + rt->lch->pl) % mod;
	rt->pl = 0;
}
inline void up(nd *rt)
{
	if (rt->lch == rt->rch)
		return;
	rt->s = (rt->lch->s + rt->rch->s) % mod;
}
unsigned int sc(nd *rt, unsigned int f, unsigned int t)
{
	if (f > t)
		return 0;
	if (rt->l >= f && rt->r <= t)
		return rt->s;
	down(rt);
	unsigned int ans = 0;
	if (rt->lch->r >= f)
		ans += sc(rt->lch, f, t);
	if (rt->rch->l <= t)
		ans += sc(rt->rch, f, t);
	return ans % mod;
}
void srch(unsigned int f, unsigned int t)
{
	unsigned int sa = sc(r1, f, t);
	unsigned int sb = ((long long)sc(r2, f + 1, t) + (long long)(t - f) * sc(r1, 1, f) - (long long)(dx[t + 1]) * sc(r1, f + 1, t)) % mod;
	printf("%u %u\n", sa, sb);
}
void add1(nd *rt, unsigned int f, unsigned int t, unsigned int d)
{
	if (rt->l >= f && rt->r <= t)
	{
		rt->s = ((long long)d * (rt->r - rt->l + 1) + rt->s) % mod;
		rt->pl = (d + rt->pl) % mod;
		return;
	}
	down(rt);
	if (t >= rt->rch->l)
		add1(rt->rch, f, t, d);
	if (f <= rt->lch->r)
		add1(rt->lch, f, t, d);
	up(rt);
}
void add2(nd *rt, unsigned int f, unsigned int t, unsigned int d)
{
	if (rt->l >= f && rt->r <= t)
	{
		rt->s = ((long long)d * gx(rt->l, rt->r) + rt->s) % mod;
		rt->pl = (rt->pl + d) % mod;
		return;
	}
	down2(rt);
	if (t >= rt->rch->l)
		add2(rt->rch, f, t, d);
	if (f <= rt->lch->r)
		add2(rt->lch, f, t, d);
	up(rt);
}
void add(unsigned int f, unsigned int t, unsigned int d)
{
	add1(r1, f, t, d);
	add2(r2, f, t, d);
}
void init()
{
	scanf("%u%u", &n, &m);
	r1 = mt(1, n);
	r2 = mt(1, n);
	for (unsigned int i = n, j = 1; i > 0; i--, j++)
	{
		dx[i] = j;
		sx[i] = (sx[i + 1] + j) % mod;
	}
}
void work()
{
	for (unsigned int i = 0; i < m; i++)
	{
		char q;
		unsigned int f, t, d;
		scanf("\n%c", &q);
		if (q == 'Q')
		{
			scanf("%u%u", &f, &t);
			srch(f, t);
		}
		else if (q == 'C')
		{
			scanf("%u%u%u", &f, &t, &d);
			add(f, t, d);
		}
	}
}
main()
{
	init();
	work();
}
