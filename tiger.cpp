#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
#define inf 1000000007
	struct sol
	{
		queue<int> q;
		int *in;
		int *is;
		int n, m, *l, k, *p;
		typedef int rtype[2];
		rtype *r;
		struct ed
		{
			int to, nx, l;
		} *es;
		int *hd, ne;
		void ae(int f, int t, int l)
		{
			es[ne].to = t;
			es[ne].l = l;
			es[ne].nx = hd[f];
			hd[f] = ne++;
		}
		struct tp
		{
			int fi, se;
			int fs, ss;
			int n;
			void init(int a, int t)
			{
				fs = ss = -1;
				fi = se = t ? 0 : inf;
				n = a;
			}
		} *d;
		void upd(tp &a, int t, int f)
		{
			int ps = a.se;
			if (a.fs == f)
				a.fi = t;
			else if (a.ss == f)
			{
				a.se = t;
				if (a.fi > a.se)
					swap(a.fi, a.se), swap(a.fs, a.ss);
			}
			else if (t < a.fi)
			{
				a.se = a.fi, a.ss = a.fs;
				a.fi = t, a.fs = f;
			}
			else if (t < a.se)
			{
				a.se = t, a.ss = f;
			}
			if (a.se != ps && !in[a.n])
				q.push(a.n), in[a.n] = 1;
		}
		sol(int n, int m, rtype *r, int *l, int k, int *p)
			:n(n), m(m), r(r), l(l), k(k), p(p)
		{
			in = new int[101010], is = new int[101010];
			memset(in, 0, sizeof(int) * 101010);
			memset(is, 0, sizeof(int) * 101010);
			d = new tp[101010];
			memset(d, 0, sizeof(tp) * 101010);
			es = new ed[2020202];
			memset(es, 0, sizeof(ed) * 202020);
			hd = new int[101010];
			memset(hd, -1, sizeof(int) * 101010);
			ne = 0;
		}
		int solve()
		{
			for (int i = 0; i < k; i++)
				is[p[i]] = 1;
			for (int i = 0; i < n; i++)
				d[i].init(i, is[i]);
			for (int i = 0; i < m; i++)
			{
				ae(r[i][0], r[i][1], l[i]);
				ae(r[i][1], r[i][0], l[i]);
			}
			for (int i = 0; i < k; i++)
				q.push(p[i]), in[p[i]] = 1;
			while (!q.empty())
			{
				int nw = q.front();
				in[nw] = 0;
				q.pop();
				for (int i = hd[nw]; i != -1; i = es[i].nx)
					upd(d[es[i].to], d[nw].se + es[i].l, nw);
			}
			return d[0].se;
		}
	}sl(N, M, R, L, K, P);
	return sl.solve();
}
int r[111][2], l[111], p[111];
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++)
		scanf("%d%d", &r[i][0], &r[i][1]);
	for (int i = 0; i < m; i++)
		scanf("%d", l + i);
	for (int i = 0; i < k; i++)
		scanf("%d", p + i);
	printf("%d", travel_plan(n, m, r, l, k, p));
}
