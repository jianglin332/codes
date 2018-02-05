#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
struct panel
{
	int l, r, h, n;
	bool operator<(const panel &a) const
	{
		if (h == a.h)
			return n < a.n;
		return h > a.h;
	}
}ps[101010];
struct ed
{
	int fr, to;
	ed(int f, int t)
	{
		fr = f;
		to = t;
	}
	bool operator<(const ed &a) const
	{
		if (ps[fr].h == ps[a.fr].h)
		{
			if (fr == a.fr)
				return to < a.to;
			return fr < a.fr;
		}
		return ps[fr].h > ps[a.fr].h;
	}
};
bool cmp(const panel &a, const panel &b)
{
	return a.l < b.l;
}
set<panel> sp;
set<ed> se;
int np;
int f[101010];
int main()
{
	int n, t;
	scanf("%d%d", &n, &t);
	ps[np].l = -(ps[np].r = 1e9 + 7);
	ps[np].h = t;
	ps[np].n = np++;
	ps[np].l = -(ps[np].r = 1e9 + 7);
	ps[np].h = 0;
	ps[np].n = np++;
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d", &ps[np].h, &ps[np].l, &ps[np].r);
		np++;
	}
	sort(ps + 2, ps + np, cmp);
	sp.insert(ps[0]);
	sp.insert(ps[1]);
	for (int i = 2; i < np; i++)
	{
		ps[i].n = i;
		set<panel>::iterator nw = sp.insert(ps[i]).first, fr = nw, bk = nw;
		fr--, bk++;
		while (fr->r <= ps[i].l)
		{
			set<panel>::iterator nf = fr;
			nf--;
			sp.erase(fr);
			fr = nf;
		}
		while (bk->r <= ps[i].l)
		{
			set<panel>::iterator nb = bk;
			nb++;
			sp.erase(bk);
			bk = nb;
		}
		se.erase(ed(fr->n, bk->n));
		se.insert(ed(fr->n, nw->n));
		se.insert(ed(nw->n, bk->n));
	}
	f[0] = 2e9 + 14;
	for (set<ed>::iterator i = se.begin(); i != se.end(); i++)
	{
		f[i->to] = max(f[i->to], min(f[i->fr], min(ps[i->fr].r, ps[i->to].r) - max(ps[i->fr].l, ps[i->to].l)));
	}
	printf("%d", f[1]);
}
