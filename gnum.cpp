#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;
struct ed
{
	int to, c, nx;
	ed(int t, int c, int n):to(t), c(c), nx(n){}
};
vector<ed> es;
int ne;
int hd[1606060], head[1606060], d[1606060];
int nn;
map<int, int> num;
int S, T;
bool bfs()
{
	queue<int> q;
	q.push(S);
	for (int i = 0; i <= nn; i++)
		d[i] = 0;
	d[S] = 1;
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		ret |= nw == T;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (es[i].c && !d[es[i].to])
				d[es[i].to] = d[nw] + 1, q.push(es[i].to);
	}
	for (int i = 0; i <= nn; i++)
		head[i] = hd[i];
	return ret;
}
int dinic(int nw, int c)
{
	if (nw == T)
		return c;
	int cc = c;
	for (int &i = head[nw]; i != -1; i = es[i].nx)
		if (es[i].c && d[es[i].to] > d[nw])
		{
			int t = dinic(es[i].to, min(c, es[i].c));
			if (t)
			{
				es[i].c -= t;
				es[i ^ 1].c += t;
				c -= t;
			}
			if (!c)
				return cc;
		}
	return cc - c;
}
int pr[101010], np;
bool ntp[101010];
void genp()
{
	for (int i = 2; i <= 32768; i++)
	{
		if (!ntp[i])
			pr[np++] = i;
		for (int j = 0; j < np && pr[j] * i <= 32768; j++)
		{
			ntp[pr[j] * i] = 1;
			if (i % pr[j] == 0)
				break;
		}
	}
}
int gcd(int a, int b)
{
	if (!b)
		return a;
	return gcd(b, a % b);
}
int u[160606], v[160606];
int us[160606], vs[160606];
int un[160606], vn[160606];
int a[444], b[444];
int nu, nv, su, sv;
#define ms(x) memset(x, 0, sizeof(x))
void ae(int f, int t, int c)
{
	es.push_back(ed(t, c, hd[f]));
	hd[f] = ne++;
	es.push_back(ed(f, 0, hd[t]));
	hd[t] = ne++;
}
void work()
{
	ms(u), ms(v), ms(us), ms(vs), ms(un), ms(vn);
	memset(hd, -1, sizeof(hd));
	vector<ed> zz;
	es.swap(zz);
	map<int, int> xx;
	num.swap(xx);
	nu = nv = su = sv = ne = 0;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	for (int i = 0; i < n; i++)
		scanf("%d", b + i);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int t = gcd(a[i], b[j]);
			if (t == 1)
				continue;
			if (a[i] > b[j])
				u[nu++] = t;
			if (a[i] < b[j])
				v[nv++] = t;
		}
	sort(u, u + nu), sort(v, v + nv);
	int t = 1;
	for (int i = 0; i < nu; i++)
		if (u[i] == u[i + 1])
			t++;
		else
			us[su] = u[i], un[su++] = t, t = 1;
	t = 1;
	for (int i = 0; i < nv; i++)
		if (v[i] == v[i + 1])
			t++;
		else
			vs[sv] = v[i], vn[sv++] = t, t = 1;
	nn = su + sv - 1;
	S = ++nn;
	T = ++nn;
	for (int i = 0; i < su; i++)
	{
		ae(S, i, un[i]);
		int t = us[i];
		for (int j = 0; j < np && pr[j] * pr[j] <= t; j++)
			if (t % pr[j] == 0)
			{
				int x = num[pr[j]];
				if (!x)
					x = num[pr[j]] = ++nn;
				ae(i, x, un[i]);
				while (t % pr[j] == 0)
					t /= pr[j];
			}
		if (t > 1)
		{
			if (!num[t])
				num[t] = ++nn;
			ae(i, num[t], un[i]);
		}
	}
	for (int i = 0; i < sv; i++)
	{
		ae(i + su, T, vn[i]);
		int t = vs[i];
		for (int j = 0; j < np && pr[j] * pr[j] <= t; j++)
			if (t % pr[j] == 0)
			{
				int x = num[pr[j]];
				if (!x)
					x = num[pr[j]] = ++nn;
				ae(x, i + su, vn[i]);
				while (t % pr[j] == 0)
					t /= pr[j];
			}
		if (t > 1)
		{
			if (!num[t])
				num[t] = ++nn;
			ae(num[t], i + su, vn[i]);
		}
	}
	int ans = 0;
	while (bfs())
		ans += dinic(S, 160606);
	printf("%d\n", ans);
}
int main()
{
	genp();
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
	return 0;
}
