#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
struct ed
{
	int to, nx, c;
	double ct;
} es[30303];
int mi = 1010101;
int hd[111], head[111], ne;
double dis[111], ans;
int nods = 109, nodt = 110;
queue<int> q;
bool inq[111];
int cv[111];
int nc;
bool spfa()
{
	nc++;
	for (int i = 0; i < 111; i++)
		dis[i] = 1e9;
	q.push(nodt);
	inq[nodt] = 1;
	dis[nodt] = 0;
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		cv[nw] = nc;
		q.pop();
		inq[nw] = 0;
		ret |= (nw == nods);
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (es[i ^ 1].c && dis[es[i].to] > dis[nw] + es[i ^ 1].ct + 1e-10)
			{
				dis[es[i].to] = dis[nw] + es[i ^ 1].ct;
				if (!inq[es[i].to])
					q.push(es[i].to), inq[es[i].to] = 1;
			}
	}
	return ret;
}
int dinic(int nw, int c)
{
	if (nw == nodt)
		return c;
	int fl = c;
	cv[nw] = 0;
	for (int &i = head[nw]; i != -1; i = es[i].nx)
		if (cv[es[i].to] == nc && es[i].c && fabs(dis[es[i].to] + es[i].ct - dis[nw]) < 1e-10)
		{
			int tm = dinic(es[i].to, min(fl, es[i].c));
			es[i].c -= tm;
			es[i ^ 1].c += tm;
			fl -= tm;
			ans += tm * es[i].ct;
			if (!fl)
				return c;
		}
	return c - fl;
}
void addedge(int s, int t, int c, double ct)
{
	es[ne].to = t;
	es[ne].c = c;
	es[ne].ct = ct;
	es[ne].nx = hd[s];
	hd[s] = ne++;
}
int main()
{
	memset(hd, -1, sizeof(hd));
	int n, m;
	scanf("%d%d", &n, &m);
	int tot = 0;
	for (int i = 0; i < n; i++)
	{
		int pi;
		scanf("%d", &pi);
		tot += pi;
		addedge(nods, i, pi, 0);
		addedge(i, nods, 0, 0);
	}
	for (int i = 0; i < m; i++)
	{
		int pi;
		scanf("%d", &pi);
		addedge(i + 51, nodt, pi, 0);
		addedge(nodt, i + 51, 0, 0);
	}
	int nn = ne;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			double t;
			scanf("%lf", &t);
			if (t == -1)
				continue;
			addedge(i, j + 51, mi, t);
			addedge(j + 51, i, 0, -t);
		}
	while (spfa())
	{
		for (int i = 0; i < 111; i++)
			head[i] = hd[i];
		dinic(nods, mi);
	}
	printf("%.2lf", ans);
	for (int i = 0; i < ne; i += 2)
		es[i].c += es[i + 1].c, es[i + 1].c = 0;
	for (int i = nn; i < ne; i += 2)
		es[i].ct = 10 - es[i].ct, es[i + 1].ct = -es[i].ct;
	ans = 0;
	while (spfa())
	{
		for (int i = 0; i < 111; i++)
			head[i] = hd[i];
		dinic(nods, mi);
	}
	printf(" to %.2lf", 10 * tot - ans);
}
