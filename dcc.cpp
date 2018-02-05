#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>
using namespace std;
struct ed
{
	int to, nx;
}es[202020];
int hd[10101], ne;
void ae(int f, int t)
{
	es[ne].to = t;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
int dfn[10101], low[10101], nfn;
stack<int> st;
int ans;
int dfs(int nw, int ls)
{
	st.push(nw);
	if (!dfn[nw])
		dfn[nw] = low[nw] = ++nfn;
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (!dfn[es[i].to])
			low[nw] = min(dfs(es[i].to, i ^ 1), low[nw]);
		else if (i != ls)
			low[nw] = min(low[nw], dfn[es[i].to]);
	if (dfn[nw] == low[nw])
	{
		while (nw != st.top())
			st.pop();
		st.pop();
		ans++;
	}
	return low[nw];
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
		ae(a, b), ae(b, a);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			dfs(i, -1);
	printf("%d", ans);
}
