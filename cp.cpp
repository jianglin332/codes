#include <stdio.h>
#include <string.h>
#include <stack>
#include <algorithm>
using namespace std;
struct ed
{
	int to, nx;
}es[202020];
int hd[10101], ne;
void ae(int fr, int to)
{
	es[ne].to = to;
	es[ne].nx = hd[fr];
	hd[fr] = ne++;
}
int dfn[10101], low[10101], out[10101], nfn, ans;
stack<int> st;
int dfs(int a, int t)
{
	dfn[a] = low[a] = ++nfn;
	st.push(a);
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if ((t >> 1) == i);
		else if (dfn[es[i].to])
			low[a] = min(low[a], dfn[es[i].to]);
		else
			low[a] = min(low[a], dfs(es[i].to, i >> 1));
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if ((t >> 1) == i);
		else if (low[es[i].to] > dfn[a])
		{
			while (st.top() != a)
				st.pop();
			ans++;
		}
	return low[a];
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	memset(hd, -1, sizeof(hd));
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ae(a, b);
		ae(b, a);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			dfs(i, -1);
	printf("%d", ans + 1);
	return 0;
}
