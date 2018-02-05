#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int g()
{
	int r = 0;
	scanf("%d", &r);
	return r;
}
struct ed
{
	int to, nx, l;
}es[606060];
int hd[303030], ne;
struct mis
{
	int fr, to, d;
	bool operator<(const mis &a) const
	{
		return d < a.d;
	}
}ms[303030];
bool cmp(const mis &a, const mis &b)
{
	return a.fr < b.fr;
}
void ae(int a, int b, int t)
{
	es[ne].to = b;
	es[ne].l = t;
	es[ne].nx = hd[a];
	hd[a] = ne++;
}
vector<int> vs[303030];
int tm[303030];
int stm[303030];
int mx = 0;
int lc = 0;
bool dfs(int nw, int to, int fr)
{
	if (to == nw)
		return 1;
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (es[i].to != fr && dfs(es[i].to, to, nw))
		{
			mx = max(mx, es[i].l);
			lc += es[i].l;
			return 1;
		}
	return 0;
}
int main()
{
	memset(hd, -1, sizeof(hd));
	int n = g(), m = g();
	int flg = 1;
	for (int i = 1; i < n; i++)
	{
		int a = g(), b = g(), t = g();
		if (a - b != 1 && b - a != 1)
			flg = 0;
		if (m == 1)
		{
			ae(a, b, t);
			ae(b, a, t);
		}
		tm[min(a, b)] = t;
	}
	for (int i = 0; i < m; i++)
	{
		int a = g(), b = g();
		ms[i].fr = min(a, b);
		ms[i].to = max(a, b);
	}
	if (m == 1)
	{
		dfs(ms[0].fr, ms[0].to, 0);
		printf("%d", lc - mx);
		return 0;
	}
	for (int i = 1; i <= n; i++)
		stm[i] = stm[i - 1] + tm[i - 1];
	for (int i = 0; i < m; i++)
		ms[i].d = stm[ms[i].to] - stm[ms[i].fr];
	sort(ms, ms + m, cmp);
	priority_queue<mis> q1, q2, q3;
	for (int i = 0; i < m; i++)
		vs[ms[i].to].push_back(i);
	for (int i = 0; i < m; i++)
		q1.push(ms[i]);
	int prev = 0, prev2 = 0, ans = 1000000007;
	for (int i = 1; i < n; i++)
	{
		for (int j = prev; j <= i; j++)
			for (vector<int>::iterator k = vs[j].begin(); k != vs[j].end(); k++)
				q3.push(ms[*k]);
		prev = i;
		while ((!q1.empty()) && q1.top().fr <= i)
			q1.pop();
		for (; prev2 < m && ms[prev2].fr <= i; prev2++)
			q2.push(ms[prev2]);
		while ((!q2.empty()) && q2.top().to <= i)
		{
			q2.pop();
		}
		int mx = -1;
		if (!q1.empty())
			mx = max(mx, q1.top().d);
		if (!q2.empty())
			mx = max(mx, q2.top().d - tm[i]);
		if (!q3.empty())
			mx = max(mx, q3.top().d);
		if (mx != -1)
			ans = min(ans, mx);
	}
	printf("%d", ans);
	return 0;
}
