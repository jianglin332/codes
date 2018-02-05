#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <stack>
#include <map>
#include <cctype>
using namespace std;
struct ed
{
	int to, nx;
}es[2010101];
char buf[10101010];
int g()
{
	static char *n = buf;
	int r = 0;
	while (!isdigit(*n))
		n++;
	while (isdigit(*n))
		r = r * 10 + *(n++) - '0';
	return r;
}
int hd[101010], sd[101010], rp[101010], ne, np;
void ae(int a, int b)
{
	es[ne].to = b;
	es[ne].nx = hd[a];
	hd[a] = ne++;
}
void ae2(int a, int b)
{
	es[ne].to = b;
	es[ne].nx = sd[a];
	sd[a] = ne++;
}
int n, m;
int v[101010];
int dfn[101010], low[101010], nfn;
bool out[101010];
int mn[101010], mx[101010];
bool vd[101010];
stack<int> st;
int tarjan(int nw, int pr)
{
	if (dfn[nw])
		return low[nw];
	st.push(nw);
	dfn[nw] = low[nw] = ++nfn;
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (!dfn[es[i].to])
			low[nw] = min(tarjan(es[i].to, nw), low[nw]);
		else if (!out[es[i].to])
			low[nw] = min(dfn[es[i].to], low[nw]);
	if (dfn[nw] == low[nw])
	{
		while (st.top() != nw)
		{
			mn[np] = min(mn[np], v[st.top()]);
			mx[np] = max(mx[np], v[st.top()]);
			rp[st.top()] = np;
			out[st.top()] = 1;
			st.pop();
		}
		mn[np] = min(mn[np], v[st.top()]);
		mx[np] = max(mx[np], v[st.top()]);
		out[st.top()] = 1;
		rp[st.top()] = np;
		st.pop();
		np++;
	}
	return low[nw];
}
set<long long> stt;
void rebuild()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = hd[i]; j != -1; j = es[j].nx)
			if (rp[i] != rp[es[j].to] && !stt.count(rp[i] * 101010ll + rp[es[j].to]))
			{
				stt.insert(rp[i] * 101010ll + rp[es[j].to]);
				ae2(rp[i], rp[es[j].to]);
			}
	}
}
int ans = 0;
int maxx[101010];
bool dfs(int nw, int minn)
{
	if (maxx[nw] != -1)
		return maxx[nw];
	for (int i = sd[nw]; i != -1; i = es[i].nx)
	{
		if (dfs(es[i].to, min(minn, mn[nw])))
			maxx[nw] = max(maxx[nw], maxx[es[i].to]);
	}
	if (maxx[nw] != -1 || nw == rp[n])
		maxx[nw] = max(maxx[nw], mx[nw]);
	ans = max(ans, maxx[nw] - min(minn, mn[nw]));
	if (nw == rp[n])
	{
		return 1;
	}
	return 0;
}
int main()
{
	memset(maxx, -1, sizeof(maxx));
	memset(hd, -1, sizeof(hd));
	memset(sd, -1, sizeof(sd));
	memset(mn, 0x23333333, sizeof(mn));
	fread(buf, 10010101, 1, stdin);
	n = g(), m = g();
	for (int i = 1; i <= n; i++)
		v[i] = g();
	for (int i = 0; i < m; i++)
	{
		int a = g(), b = g(), c = g();
		ae(a, b);
		if (c == 2)
			ae(b, a);
	}
	tarjan(1, 0);
	rebuild();
	dfs(rp[1], mn[rp[1]]);
	printf("%d", ans);
	return 0;
}
